/*****************************************************************************
 *	FILENAME:	factory.hpp            AUTHOR: Liad Oz	     LAB: RD100	     *
 *																			 *
 *	VERSION:	4															 *
 *																			 *
 *	PURPOSE:   API for factory lib.							                 *
 *																			 *
 *****************************************************************************/

#ifndef __ILRD_RD100_FACTORY_HPP__
#define __ILRD_RD100_FACTORY_HPP__

#include <boost/core/noncopyable.hpp> // noncopyable
#include <boost/unordered_map.hpp> // unordered_map
/*****************************************************************************/
namespace ilrd_rd100
{

template <class KEY ,class T, class PARAM>
class Factory : private boost::noncopyable
{
public:
    typedef T (*factory_func_t)(PARAM);

    void Add(const KEY &key, factory_func_t factory_func);
    T Create(const KEY &key, const PARAM &param) const;

private:
    boost::unordered_map<KEY, factory_func_t> m_creators;
}; // class Factory

template <class KEY ,class T, class PARAM>
void Factory<KEY ,T, PARAM>::Add(const KEY &key, factory_func_t factory_func)
{
    m_creators[key] = factory_func;
}

template <class KEY ,class T, class PARAM>
T Factory<KEY ,T, PARAM>::Create(const KEY &key, const PARAM &param) const
{
    return m_creators.at(key)(param);
}



} // namespace ilrd_rd100
/*****************************************************************************/
#endif // __ILRD_RD100_FACTORY_HPP__