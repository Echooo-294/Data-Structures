#pragma once

#include "bp.hpp"
#include <algorithm>

// Implementation for leaf node
template <typename key_t, typename record_t>
class bp_leaf : public bp_node<key_t, record_t> {
    using bp_node_t = bp_node<key_t, record_t>;
    using bp_leaf_t = bp_leaf<key_t, record_t>;
   public:
    bp_leaf() {}  // constructor
    bp_leaf(const key_t* key_arr,const record_t* record_arr,int size):size_(size){
        //LOG("creat leaf by arr\n");
        std::copy(key_arr,(key_arr)+(size),keys_);
        std::copy(record_arr,(record_arr)+(size),records_);
    }
    bool is_leaf() const { return true; }
    bool is_full() const { return (size_ == LEAF_MAXN); }
    int size() const { return size_; }
    int max_size() const {return LEAF_MAXN;}
    int min_size() const {return LEAF_MINN;}
    key_t* keys() { return keys_; }
    record_t records(int pos) const { return records_[pos]; }
    record_t* p_records() { return records_; }

    bp_node_t* remove(int pos) {
        std::rotate(keys_+pos,keys_+pos+1,keys_+size_);
        std::rotate(records_+pos,records_+pos+1,records_+size_);
        size_--;
        return this;
    }
    /**
     * @brief add a key-record pair in this bp_leaf node
     * 
     * @param key the key
     * @param record the record
     * @return bp_node_t* if need to split, return the p_new_leaf_node;
     * otherwise return this
     */
    bp_node_t* add(const key_t& key, const record_t& record) {
        // key_t take;
        auto pos = std::lower_bound(keys_, keys_ + size_, key) - keys_;
        const record_t* p_new_record = &record;
        if (!is_full()) {
            //LOG("in leaf.add(), leaf isnt full\n");
            for (int i = size_; i > pos; i--) {
                keys_[i] = keys_[i - 1];
                records_[i] = records_[i - 1];
            }
            keys_[pos] = key;
            records_[pos] = record;
            size_++;
            return this;
        } else {
            //LOG("in leaf.add(), leaf is full\n");
            size_ = LEAF_MID_POS;
            bp_leaf_t* new_leaf_node;
            key_t new_key_arr[LEAF_MAXN];
            record_t new_record_arr[LEAF_MAXN];
            if(pos == LEAF_MID_POS){
                // Well Done
                // take = key;
                // 左节点，不用动
                // 右节点，头一个就是它
                *new_key_arr = key;
                *new_record_arr = record;
                // 右节点剩下的，是[mid_pos:]
				std::copy(keys_+LEAF_MID_POS,(keys_+LEAF_MID_POS)+(LEAF_MAXN-LEAF_MID_POS),new_key_arr+1);
				std::copy(records_+LEAF_MID_POS,(records_+LEAF_MID_POS)+(LEAF_MAXN-LEAF_MID_POS),new_record_arr+1);
            }else if(pos < LEAF_MID_POS){
                // Well Done
                // take = keys_[LEAF_MID_POS-1];
                // 先把[mid_pos-1:]拷走
				std::copy(keys_+LEAF_MID_POS-1,(keys_+LEAF_MID_POS-1)+(LEAF_MAXN-LEAF_MID_POS+1),new_key_arr);
				std::copy(records_+LEAF_MID_POS-1,(records_+LEAF_MID_POS-1)+(LEAF_MAXN-LEAF_MID_POS+1),new_record_arr);
                // 再把[pos:midpos-2]的统一向后搬
                std::rotate(keys_+pos,keys_+LEAF_MID_POS-1,keys_+LEAF_MID_POS);
                std::rotate(records_+pos,records_+LEAF_MID_POS-1,records_+LEAF_MID_POS);
                // 再把东西放在[pos]上
                keys_[pos] = key;
                records_[pos] = record;
            }else{
                // Well Done
                // take = keys_[LEAF_MID_POS];
                // [mid_pos,pos]
				std::copy(keys_+LEAF_MID_POS,(keys_+LEAF_MID_POS)+(pos-LEAF_MID_POS),new_key_arr);
				std::copy(records_+LEAF_MID_POS,(records_+LEAF_MID_POS)+(pos-LEAF_MID_POS),new_record_arr);
                // 把东西放在此处
                new_key_arr[pos-LEAF_MID_POS] = key;
                new_record_arr[pos-LEAF_MID_POS] = record;
                // [pos:]
				std::copy(keys_+pos,(keys_+pos)+(LEAF_MAXN-pos),new_key_arr+pos-LEAF_MID_POS+1);
				std::copy(records_+pos,(records_+pos)+(LEAF_MAXN-pos),new_record_arr+pos-LEAF_MID_POS+1);
            }
            new_leaf_node = new bp_leaf_t(new_key_arr,new_record_arr,LEAF_MAXN-LEAF_MID_POS+1);
            // 左右连接起来
            this->r_ptr = new_leaf_node;
            new_leaf_node->l_ptr = this;
            return new_leaf_node;
        }
    }

    bool underflow() { return (size_ < (LEAF_MAXN + 1) / 2); }

   public:
    key_t keys_[LEAF_MAXN];
    record_t records_[LEAF_MAXN];
    int size_ = 0;  // The number of records_ now
};
