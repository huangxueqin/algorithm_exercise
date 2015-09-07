#ifndef __INDEXED_PRIORITY_QUEUE__
#define __INDEXED_PRIORITY_QUEUE__

#include <functional>
#include <memory>
#include <cstddef>
#include <cstring>
#include <map>

namespace ipq {

    template <class Key, class T, class TCompare = std::less<T>, class TAlloc = std::allocator<T> >
    class indexed_priority_queue {

    public:
        typedef Key key_type;
        typedef T value_type;
        typedef TCompare value_compare;
        typedef TAlloc allocator_type;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef size_t size_type;
        typedef std::ptrdiff_t difference_type;

    private:
        std::map<key_type, size_type> key_to_index;
        std::map<size_type, key_type> index_to_key;
        pointer heap;
        size_type alloc_size;
        size_type size;
        value_compare comp;
        allocator_type alloc;

    public:
        // constructors and destructor
        explicit indexed_priority_queue(const value_compare &comp = value_compare(), 
                const allocator_type& alloc = allocator_type());
        explicit indexed_priority_queue(const allocator_type &alloc);
        ~indexed_priority_queue();

        void reserve(size_type n);
        void insert(const key_type &key, const value_type &value);
        void erase(const key_type &key);
        void modify(const key_type &key, const value_type &new_value);


    };
}

#endif
