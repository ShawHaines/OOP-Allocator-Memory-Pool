#pragma once
#include <cstddef>
#include <type_traits>
#include "MemoryPool_Alloc.h"

template <typename T>
class Allocator{
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

    /*obtains the address of an object, even if operator& is overloaded. */
    pointer address(reference _Val) const noexcept;
    const_pointer address(const_reference _Val) const noexcept;
    /**allocates uninitialized storage.
     * _Count is the count of objects(not bytes).
     *  Default count is 1.*/
    pointer allocate(size_type _Count=1);
    /*deallocates storage. Returns 0 if success.*/
    int deallocate(pointer _Ptr, size_type _Count=1);
    /*constructs an object in allocated storage. */
    template <class _Objty, class Tpes>
    void construct(_Objty *_Ptr, Tpes &&... _Args);
    /*destructs an object in allocated storage */
    template <class _Uty>
    void destroy(_Uty *_Ptr);

private:
    static MemoryPool_Alloc pool;
};
/**TODO:
 * solve the case that the operator& is overloaded.
 */
template <typename T>
T* Allocator<T>::address(T& _Val) const noexcept{
    return (&_Val);
}
template <typename T>
const T* Allocator<T>::address(const T& _Val) const noexcept{
    return (&_Val);
}
template <typename T>
T* Allocator<T>::allocate(std::size_t count){
    return static_cast<T* >(pool.allocate(sizeof(T)*count));
}
template <typename T>
int Allocator<T>::deallocate(T* p,std::size_t count){
    return pool.deallocate(static_cast<void* >(p),sizeof(T)*count);
}
/*...Args是模板参数包, Template parameter pack. */
template <typename T>
template <typename ObjectType,typename ArgType>
void Allocator<T>::construct(ObjectType* p,ArgType&&... args){
    new(p) ObjectType(std::forward<ArgType>(args)...);
    return;
}
template <typename T>
template<typename ObjectType>
void Allocator<T>::destroy(ObjectType* p){
    p->~ObjectType();//mind-broadening usage.
    return;
}
