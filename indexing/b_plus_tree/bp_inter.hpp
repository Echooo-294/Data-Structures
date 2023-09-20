#pragma once

#include <algorithm>
#include "bp.hpp"

// Implementation for leaf node
template <typename key_t, typename record_t>
class bp_inter : public bp_node<key_t, record_t> {
    using bp_node_t = bp_node<key_t, record_t>;
    using bp_inter_t = bp_inter<key_t, record_t>;

   public:
    bp_inter() {}  // constructor
    bp_inter(key_t* key_arr,bp_node_t* ptr_arr[],int size):size_(size){
        LOG("create inter(",get_nick(this),") by arr -> <",key_arr[0],"> -> <",get_nick(ptr_arr[0]),",",get_nick(ptr_arr[1]),">\n");
		std::copy(key_arr,key_arr+size-1,keys_);
		std::copy(ptr_arr,ptr_arr+size,ptrs_);
        keys_[INTER_MAXN-1] = key_arr[INTER_MAXN-1];
    }
    bool is_leaf() const { return false; }
    bool is_full() const { return (size_ == INTER_MAXN); }
    int size() const { return size_; }
    int max_size() const {return INTER_MAXN;}
    int min_size() const {return INTER_MINN;}
    key_t* keys() { return keys_; }
    bp_node_t* get_node_ptr(int pos) const { return ptrs_[pos]; }
    bp_node_t** ptrs() { return ptrs_; }

    bp_node_t* remove(int pos) {
        std::rotate(keys_+pos,keys_+pos+1,keys_+size_);
        std::rotate(ptrs_+pos,ptrs_+pos+1,ptrs_+size_);
        size_--;
        return this;
    }
    bp_node_t* remove_l(int pos) {
        //this->remove(pos);
        std::rotate(keys_+pos,keys_+pos+1,keys_+size_);
        std::rotate(ptrs_+pos,ptrs_+pos+1,ptrs_+size_);
        return this;
    }
    bp_node_t* remove_r(int pos) {
        std::rotate(keys_+pos,keys_+pos+1,keys_+size_);
        std::rotate(ptrs_+pos+1,ptrs_+pos+2,ptrs_+size_);
        size_--;
        return this;
    }

    /**
     * @brief add a key-ptr pair in this bp_inter node
     * 
     * @param key the key
     * @param ptr the pointer
     * @return bp_inter_t* if need to split, return the p_new_inter_node; otherwise return this
     */
    bp_inter_t* add(key_t key, bp_node_t* ptr) {
        LOG("bp_inter(",get_nick(this),") where size_ = ",size_,", keys_ = ",arr_to_str(keys_)," and ptrs_ = ",arr_to_str(ptrs_)," add <",key,",",get_nick(ptr),">\n");
        auto pos = std::lower_bound(keys_, keys_ + size_ - 1, key) - keys_;
        auto new_ptr = &ptr;
        if(!is_full()){
            for (int i = size_ - 1; i > pos; i--) {
                keys_[i] = keys_[i-1];
                ptrs_[i+1] = ptrs_[i];
            }
            keys_[pos] = key;
            ptrs_[pos+1] = ptr;
            size_++;
            return this;
        }else{
            key_t take;
            size_ = INTER_MID_POS + 1;
            bp_inter_t* new_inter_node;
            key_t new_key_arr[INTER_MAXN];
            bp_node_t* new_ptr_arr[INTER_MAXN];
            if(pos == INTER_MID_POS){
                PRINT("[in inter.add(",key,",",get_nick(ptr),"): pos(",pos,") = mid]\n");
                take = key;
                // 放好这个
                *new_ptr_arr = ptr;
                // 对于key，拷走[mid_pos:]；对于ptr，拷走[mid_pos+1:]
				std::copy(keys_+INTER_MID_POS,keys_+INTER_MAXN-1,new_key_arr);
				std::copy(ptrs_+INTER_MID_POS+1,ptrs_+INTER_MAXN,new_ptr_arr+1);
            }else if(pos < INTER_MID_POS){
                PRINT("[in inter.add(",key,",",get_nick(ptr),"): pos(",pos,") < mid]\n");
                take = keys_[INTER_MID_POS-1];
                // 对于key，拷走[mid_pos:]；对于ptr，拷走[mid_pos:]
				std::copy(keys_+INTER_MID_POS,keys_+INTER_MAXN-1,new_key_arr);
				std::copy(ptrs_+INTER_MID_POS,ptrs_+INTER_MAXN,new_ptr_arr);
                // 往后搬
                std::rotate(keys_+pos,keys_+INTER_MID_POS-1,keys_+INTER_MID_POS);
                std::rotate(ptrs_+pos+1,ptrs_+INTER_MID_POS,ptrs_+INTER_MID_POS+1);
                // 放好
                keys_[pos] = key;
                ptrs_[pos+1] = ptr;
            }else{
                PRINT("[in inter.add(",key,",",get_nick(ptr),"): pos(",pos,") > mid]\n");
                take = keys_[INTER_MID_POS];
                // keys_[mid_pos+1:pos] ptrs_[mid_pos+1:pos+1]
				std::copy(keys_+INTER_MID_POS+1,keys_+pos,new_key_arr);
				std::copy(ptrs_+INTER_MID_POS+1,ptrs_+pos+1,new_ptr_arr);
                // 放好key和ptr
                new_key_arr[pos-INTER_MID_POS-1] = key;
                new_ptr_arr[pos-INTER_MID_POS] = ptr;
                // keys_[pos:] ptrs_[pos+1:]
				std::copy(keys_+pos,keys_+INTER_MAXN-1,new_key_arr+pos-INTER_MID_POS);
				std::copy(ptrs_+pos,ptrs_+INTER_MAXN-1,new_ptr_arr+pos-INTER_MID_POS+1);
            }
            new_key_arr[INTER_MAXN-1] = take;
            new_inter_node = new bp_inter_t(new_key_arr,new_ptr_arr,INTER_MAXN-INTER_MID_POS);
            return new_inter_node;
        }
    }
    void fast_append_r(key_t key,bp_inter_t* ptr){
        keys_[size_-1] = key;
        ptrs_[size_] = ptr;
        size_++;
    }
    void fast_append_l(key_t key,bp_inter_t* ptr){
        keys_[size_-1] = key;
        ptrs_[size_] = ptr;
        std::rotate(keys_,keys_+size_-1,keys_+size_);
        std::rotate(ptrs_,ptrs_+size_,ptrs_+size_+1);
    }

    bool underflow() { return (size_ < (INTER_MAXN + 1) / 2); }

   private:
    key_t keys_[INTER_MAXN];
    bp_node_t* ptrs_[INTER_MAXN];
    int size_ = 0;  // The number of records_ now
};
