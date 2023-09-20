#pragma once

#include "bp_node.hpp"
#include <algorithm>

template <typename key_t, typename record_t>
class bp_tree {
    using bp_node_t = bp_node<key_t, record_t>;
    using bp_inter_t = bp_inter<key_t, record_t>;
    using bp_leaf_t = bp_leaf<key_t, record_t>;

   public:
    bp_tree() = default;

    void insert(const key_t& key, const record_t& record) {
        //LOG("insert\n");
        if(root == nullptr){
            LOG("add root\n");
            root = new bp_leaf_t(&key,&record,1);
        // }else if (root->is_leaf()){
        //     LOG("root is leaf\n");
        //     if(root != ((bp_leaf_t*)root)->add(key,record)){
        //         // todo xxx
        //     }
        }else{
            LOG("root(",get_nick(root),") call insert__ for help\n");
            bp_node_t* ret = insert__(root, key, record);
            if(ret!=root && ret->is_leaf()){
                bp_leaf_t* ret_casted = ((bp_leaf_t*)ret);
                key_t new_keys[]{ret_casted->keys()[0]};
                bp_node_t* new_ptrs[]{root,ret};
                root = new bp_inter_t(new_keys,new_ptrs,2);
            }else if(ret!=root && !ret->is_leaf()){
                bp_inter_t* ret_casted = ((bp_inter_t*)ret);
                key_t new_keys[]{ret_casted->keys()[INTER_MAXN-1]};
                bp_node_t* new_ptrs[]{root,ret};
                root = new bp_inter_t(new_keys,new_ptrs,2);
            }
        }
        size_++;
        return;
    }

    record_t remove(const key_t& key) {
        record_t ret = find__(root, key);
        if (ret == nullptr) return nullptr;
        LOG("removing ",key,"\n");
        LOG("call remove__ ->");
        if (remove__(root, key) && (root->size() == 1))  // Collapse root
            if (!root->is_leaf()) root = ((bp_inter_t*)root)->get_node_ptr(0);
        size_--;

        return ret;
    }

    // record_t remove_any() { return nullptr; }

    record_t find(const key_t& key) const { return find__(root, key); }

    int size() { return size_; }

   private:
    record_t find__(bp_node_t* p_root, const key_t& key) const {
        int pos;
        if (p_root->is_leaf()) {
            pos = find_key_lower(p_root->keys(), p_root->size(), key);
            return ((((bp_leaf_t*)p_root)->keys())[pos] == key)
                       ? ((bp_leaf_t*)p_root)->records(pos)
                       : nullptr;
        }
        pos = find_key_lower(p_root->keys(), p_root->size() - 1, key);
        if(p_root->keys()[pos]==key) pos++;
        return find__(((bp_inter_t*)p_root)->get_node_ptr(pos), key);
    }

    bp_node_t* insert__(bp_node_t* p_root, const key_t& key, const record_t& record) {
        LOG("in insert__(",get_nick(p_root),",",key,/*",",record,*/") -> ");
        if (p_root->is_leaf()){
            PRINT("(",get_nick(p_root),")","is leaf where keys_ = ",arr_to_str(((bp_leaf_t*)p_root)->keys_,p_root->size()),/*" and records_ = ",arr_to_str(((bp_leaf_t*)p_root)->records_,p_root->size()),*/" -> ");
            bp_node_t* ret = ((bp_leaf_t*)p_root)->add(key, record);
            PRINT(arr_to_str(((bp_leaf_t*)p_root)->keys_,p_root->size())," -> ");
            PRINT("return (",get_nick(ret),") where keys_ = ",arr_to_str(ret->keys(),ret->size()),"\n");
            return ret;
        }
        int pos = find_key_lower(p_root->keys(),p_root->size() - 1,key);
        if ((p_root->keys())[pos] == key) throw "key duplicated";
        bp_node_t* p_sub_root = (((bp_inter_t*)p_root)->get_node_ptr(pos));
        PRINT("(",get_nick(p_root),")","is not leaf, pos = ",pos,"\n");
        bp_node_t* ret = insert__(p_sub_root, key, record);
        if (ret != p_sub_root) {
            if(ret->is_leaf()){
                return ((bp_inter_t*)p_root)->add(ret->keys()[0],ret);
            }else{
                return ((bp_inter_t*)p_root)->add(ret->keys()[INTER_MAXN-1],ret);
            }
        } else {
            return p_root;
        }
    }

    /**
     * @brief Delete record of given value
     * 
     * @param p_root the tree
     * @param key the key
     * @return return true if root underflow
     */
    bp_node_t* remove__(bp_node_t* p_root, const key_t& key){
        PRINT("remove__(",get_nick(p_root),",",key,") -> ");
        using bp_node_t = bp_node<key_t, record_t>;
        using bp_inter_t = bp_inter<key_t, record_t>;
        using bp_leaf_t = bp_leaf<key_t, record_t>;
        int pos = find_key_lower(p_root->keys(), p_root->size() - 1, key);
        if (p_root->is_leaf()){
            PRINT("is leaf\n");
            return (((bp_leaf_t*)p_root)->keys()[pos] == key)
                ? (((bp_leaf_t*)p_root)->remove(pos))
                : nullptr;
        }
        bp_node_t* p_sub_root = ((bp_inter_t*)p_root)->get_node_ptr(pos);
        bp_node_t* ret = remove__(p_sub_root, key);
        if(!ret) return nullptr;
        if(!((bp_inter_t*)p_sub_root)->underflow()) return nullptr;
        // handle merge
        /* 分类讨论：
        叶子、非叶子
        合并与直接拿
        是不是最左边那个
         */
        bp_inter_t* p_root_casted = ((bp_inter_t*)p_root);
        key_t* cur_keys = ((bp_inter_t*)p_root)->keys();
        bp_node_t** cur_ptrs = ((bp_inter_t*)p_root)->ptrs();
        // 叶子
        if(p_sub_root->is_leaf()){
            bp_leaf_t* p_sub_root_casted = (bp_leaf_t*)p_sub_root;
            bp_leaf_t* p_good_friend = (bp_leaf_t*)(cur_ptrs[((pos==0)?1:(pos-1))]);
            // 够，拿一个过来
            if((p_good_friend->size()) - 1 > p_sub_root->min_size()){
                // 是最左边那个
                if(pos==0){
                    // 把这层相应的key换掉
                    cur_keys[pos] = p_good_friend->keys()[1];
                    // 拿过来
                    p_sub_root_casted->add(p_good_friend->keys()[0],p_good_friend->p_records()[0]);
                    // 删掉那个
                    p_good_friend->remove(0);
                // 不是最左边那个
                }else{
                    bp_leaf_t* p_good_friend = (bp_leaf_t*)cur_ptrs[pos-1];
                    // 把这层相应的key换掉
                    cur_keys[pos] = p_good_friend->keys()[p_good_friend->size()-1];
                    // 拿过来
                    p_sub_root_casted->add(p_good_friend->keys()[p_good_friend->size()-1],p_good_friend->p_records()[p_good_friend->size()-1]);
                    // 删掉那个
                    p_good_friend->remove(p_good_friend->size()-1);
                }
            // 不够，合并
            }else{
                // 是最左边那个
                if(pos==0){
                    // 把这层相应的key和它的右儿子删掉
                    p_root_casted->remove_r(pos);
                    // 把它的好兄弟并过来
                    std::copy(p_good_friend->keys(),p_good_friend->keys()+p_good_friend->size(),p_sub_root_casted->keys()+p_sub_root_casted->size());
                    std::copy(p_good_friend->p_records(),p_good_friend->p_records()+p_good_friend->size(),p_sub_root_casted->p_records()+p_sub_root_casted->size());
                // 不是最左边那个
                }else{
                    // 把这层相应的key和它的右儿子(也就是sub_root自己)删掉
                    p_root_casted->remove_r(pos);
                    // 把它并到它的好兄弟那里去
                    std::copy(p_sub_root_casted->keys(),p_sub_root_casted->keys()+p_sub_root_casted->size(),p_good_friend->keys()+p_good_friend->size());
                    std::copy(p_sub_root_casted->p_records(),p_sub_root_casted->p_records()+p_sub_root_casted->size(),p_good_friend->p_records()+p_good_friend->size());
                }
            }
        // 非叶子
        }else{
            bp_inter_t* p_sub_root_casted = (bp_inter_t*)p_sub_root;
            bp_inter_t* p_good_friend = (bp_inter_t*)cur_ptrs[((pos==0)?1:(pos-1))];
            // 够，左旋或者右旋
            if((p_good_friend->size()) - 1 > p_sub_root->min_size()){
                // 是最左边那个，左旋
                if(pos==0){
                    // 把key左推
                    p_sub_root_casted->fast_append_r(cur_keys[pos],(bp_inter_t*)p_good_friend->ptrs()[0]);
                    // 把好朋友的头一个拿过来当中间节点
                    cur_keys[pos] = p_good_friend->keys()[0];
                    // 删掉那个
                    p_good_friend->remove_l(0);
                // 不是最左边那个，右旋
                }else{
                    // 把key右推
                    p_sub_root_casted->fast_append_l(cur_keys[pos],(bp_inter_t*)p_good_friend->ptrs()[size_-1]);
                    // 把好朋友的末一个拿过来当中间节点
                    cur_keys[pos] = p_good_friend->keys()[size_-2];
                    // 删掉那个
                    p_good_friend->remove_r(size_-2);
                }

            // 不够，合并到左边那个节点
            }else{
                // 是最左边那个
                if(pos==0){
                    // 中间那个变成了左边的末尾
                    p_sub_root_casted->fast_append_r(cur_keys[pos],(bp_inter_t*)p_good_friend->ptrs()[0]);
                    // 把全部key和那些东西拷过去
                    std::copy(p_good_friend->keys(),p_good_friend->keys()+p_good_friend->size()-1,p_sub_root_casted->keys()+size_-1);
                    std::copy(p_good_friend->ptrs()+1,p_good_friend->ptrs()+p_good_friend->size(),p_sub_root_casted->ptrs()+size_);
                // 不是最左边那个
                }else{
                    // 中间那个变成了左边的末尾
                    p_good_friend->fast_append_r(cur_keys[pos],(bp_inter_t*)p_sub_root_casted->ptrs()[0]);
                    // 把全部key和那些东西拷过去
                    std::copy(p_sub_root_casted->keys(),p_sub_root_casted->keys()+p_sub_root_casted->size()-1,p_good_friend->keys()+size_-1);
                    std::copy(p_sub_root_casted->ptrs()+1,p_sub_root_casted->ptrs()+p_sub_root_casted->size(),p_good_friend->ptrs()+size_);
                }
            }
        }
        // ...


        return p_root;
    }

    /**
     * @brief find key position using binary search
     * 
     * @param keys begin of key_arr
     * @param cnt length of key_arr
     * @param key the key to search
     * @return int the first position where key greater equal than it
     */
    int find_key_lower(key_t keys[], int cnt, const key_t key) const {
        return std::lower_bound(keys,keys+cnt,key) - keys;
    }

    bp_node_t* root = nullptr;
    int size_ = 0;
};