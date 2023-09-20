#pragma once

#include <algorithm>
#include "./detail/node/node.hpp"


namespace ds{   namespace index{

template <typename Key, typename Record, typename Allocator = std::allocator<std::pair<Key,Record>>>
class btree {
    using key_type          = Key;
    using record_type       = Record;
    using node_type         = Node<Key, Record>;
    using allocator_type    = Allocator;

    struct members_holder:
        : public detail::btree::allocators<Allocator>
    {
        using key_type                  = Key;
        using record_type               = Record;
        using node_type                 = Node<Key, Record>;
        using allocators_type           = typename detail::btree::allocators<Allocator>;
        using node_pointer              = typename allocators_type::node_pointer;
        using allocator_traits_type     = std::allocator_traits<Allocator>;

        node_pointer root = nullptr;
        int size_;

        members_holder(int size):size_(size){}
    };
   public:
    btree() = default;

    btree(btree const&);

    void insert(Key const& key, Record const& record) {
    }

    Record remove(Key const& key) {
    }

    Record find(Key const& key) const {
    }

    int size() { return size_; }

   private:
    members_holder m_members;
};

}}