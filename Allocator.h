#pragma once
#include <cstddef>
#include <type_traits>
#include <MemoryPool.h>


// template <typename T>
typedef int T;
struct Allocator{
public:
    typedef void _Not_user_specialized;
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type &const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;
    pointer address(reference _Val) const noexcept;
    const_pointer address(const_reference _Val) const noexcept;
    void deallocate(pointer _Ptr, size_type _Count);
    pointer allocate(size_type _Count);
    template <class _Uty>
    void destroy(_Uty *_Ptr);
    template <class _Objty, class Tpes>
    void construct(_Objty *_Ptr, Tpes &&... _Args);
private:
    static MemoryPool pool;
};