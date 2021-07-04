/****************************************************************************
* FILE: shared_ptr.hpp		            PURPOSE: API for SharedPtr Class.
*
* DEVELOPER: DanielZ
*
* REVIEWER:  Liad OZ	                STATUS: 
*
* VERSION: 1
*
****************************************************************************/
#ifndef __ILRD_SHARED_PTR_HPP__
#define __ILRD_SHARED_PTR_HPP__

#include <cstddef> /* size_t */

namespace ilrd_rd100
{   
/*****************************************************************************/
/*****************************************************************************/ 
template <class T>
class SharedPtr
{
public:
    //Ctor, CCtor, Dtor
    explicit SharedPtr(T *ptr = NULL);
    ~SharedPtr();

    template <class S>
    SharedPtr(SharedPtr<S> &other); 

    //Member functions
    T *Get() const;

    //Operators

    template <class S>
    SharedPtr<T> &operator=(const SharedPtr<S> &other);

    //forcing default operator= to call templated operator=
    SharedPtr<T> &operator=(const SharedPtr<T> &other);

    T &operator*() const;
    T *operator->() const;

private:

    //makes all sharedptr instances friends
    template <class S> 
    friend class SharedPtr<T>;

    template <class S>
    void ShallowCopy(const SharedPtr<S> &other);

    bool IsShared() const;
    void DeleteFields();

    size_t *m_ref;
    T *m_ptr;
};
/*****************************************************************************/
template <class T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &other)
{
    return SharedPtr::operator=<T>(other);
}
/*****************************************************************************/
template <class T>
SharedPtr<T>::SharedPtr(T *ptr) : m_ref(new size_t(1)), m_ptr(ptr)
{
    /*EMPTY*/
}
/*****************************************************************************/
template <class T>
template <class S>
SharedPtr<T>::SharedPtr(SharedPtr<S> &other)
{
    ShallowCopy(other);
    ++(*m_ref);
}
/*****************************************************************************/
template <class T>
T *SharedPtr<T>::Get() const
{
    return m_ptr;
}
/*****************************************************************************/
template <class T>
template <class S>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<S> &other)
{
    if(m_ptr != other.m_ptr)
    {
        if(!IsShared())
        {
            DeleteFields();
        }
        else
        {
            --(*m_ref);
        }

        ShallowCopy(other);
        ++(*m_ref);
    }
    return *this;
}
/*****************************************************************************/

/*****************************************************************************/
template <class T>
T &SharedPtr<T>::operator*() const
{
    return *m_ptr;
}
/*****************************************************************************/
template <class T>
T *SharedPtr<T>::operator->() const
{
    return m_ptr;
}
/*****************************************************************************/
template <class T>
SharedPtr<T>::~SharedPtr()
{
   if(!IsShared())
   {
       DeleteFields();
       return;
   }
   --(*m_ref);
}
/*****************************************************************************/
template <class T>
bool SharedPtr<T>::IsShared() const
{
    return (1 < *m_ref) ? true : false;
}
/*****************************************************************************/
template <class T>
void SharedPtr<T>::DeleteFields()
{
    delete m_ref; m_ref = NULL;
    delete m_ptr; m_ptr = NULL;
}
/*****************************************************************************/
template <class T>
template <class S>
void SharedPtr<T>::ShallowCopy(const SharedPtr<S> &other)
{   
    m_ref = other.m_ref;
    m_ptr = other.m_ptr;
}
/*****************************************************************************/
}// end ilrd_rd100
#endif /*__ILRD_RCSTRING_HPP__*/