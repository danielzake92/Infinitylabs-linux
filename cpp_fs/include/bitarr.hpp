/****************************************************************************
* FILE: bitarr.hpp		            Purpose: API for BitArr Class.
*
* DEVELOPER: Elizabeta
*
* REVIEWER:  			                STATUS: 
*
* VERSION: 5
*
****************************************************************************/
#ifndef __ILRD_RD100_BITARR_HPP__
#define __ILRD_RD100_BITARR_HPP__

#include <cstddef>  //size_t
#include <string> //std::string
#include <cstring> //memset
#include <climits> //CHAR_BIT
#include <algorithm> //stl alogs
#include <iostream>

namespace ilrd_rd100
{

const size_t NUM_BITS = CHAR_BIT * sizeof(unsigned int);

class BitArrLut
{
private:
    static const unsigned char g_count_lut[256];       
};
/*****************************************************************************/

template <size_t N>
class BitArr : private BitArrLut
{ //BitArr start
class BitProxy;
public:
    explicit BitArr();

    bool operator[](size_t idx) const;
    BitProxy operator[](size_t idx);

    bool operator==(const BitArr<N> &other) const;
    bool operator!=(const BitArr<N> &other) const;

    BitArr<N> &operator^=(const BitArr<N> &other);
    BitArr<N> &operator&=(const BitArr<N> &other);
    BitArr<N> &operator|=(const BitArr<N> &other);

    BitArr<N> &Set(size_t idx);
    BitArr<N> &SetAll();
    bool Get(size_t index) const;

    BitArr<N> &Flip(size_t idx);
    BitArr<N> &FlipAll();
    size_t Count() const;
    std::string ToString() const;

private:
    static const size_t s_size =  (N / NUM_BITS) +
                                  !!(N % (NUM_BITS) );
    unsigned int arr[s_size];
  
/*****************************************************************************/
/* util methods */
    void GetIndexes(size_t idx, size_t *block_idx, size_t *bit_num) const;
/*****************************************************************************/
    class BitProxy
    {
    public:
        explicit BitProxy(BitArr<N> &bit_arr_obj, size_t idx);

        operator bool();
        BitProxy &operator=(const BitProxy &other);
        
        BitProxy &operator=(bool other);
    private:
        BitArr<N> &m_arr;
        const size_t m_idx;
    };
/*****************************************************************************/
    class Counter
    {
    public:
        Counter(size_t *ptr_counter) : m_ptr(ptr_counter){}
        void operator()(unsigned int arr_val) const
        {
            while(arr_val)
            {
                *m_ptr += g_count_lut[arr_val & 0xFF];
                arr_val >>= CHAR_BIT;
            }
        }
    private:

        size_t *m_ptr;

    };  
/*****************************************************************************/
    class ToStr
    {
    public:
        ToStr(std::string &str) : m_str(&str) {}
        void operator()(unsigned int arr_val) 
        {
            size_t count = NUM_BITS;
            size_t bit_num = 0;
            char c = 0;
            while(bit_num < count)
            {
                c = !!(arr_val & (1 << bit_num)) + '0';
                *m_str += c;
                ++bit_num;
            }
        }
    private:

        std::string *m_str;

    };  
/*****************************************************************************/   
    class FlipNum
    {
    public:
        FlipNum(){}
        unsigned int operator()(unsigned int arr_val) const
        {
            return(arr_val ^ 0XFFFFFFFF);
        }
    };
/*****************************************************************************/
};//BitArr end
/*****************************************************************************/
/*****************************************************************************/

/*****************************************************************************/
template <size_t N>
BitArr<N>::BitArr() : arr()
{/* EMPTY */}
/*****************************************************************************/
template <size_t N>
bool BitArr<N>::operator[](size_t idx) const
{
    return BitArr<N>::Get(idx);
}
/*****************************************************************************/
template <size_t N>
bool BitArr<N>::Get(size_t index) const
{
    size_t block_idx = 0;
    size_t bit_num = 0;
    GetIndexes(index,&block_idx, &bit_num);
    return (!!(arr[block_idx] & (1 << bit_num)));
}
/*****************************************************************************/
template <size_t N>
BitArr<N> &BitArr<N>::Set(size_t idx)
{
    size_t block_idx = 0;
    size_t bit_num = 0;
    GetIndexes(idx,&block_idx, &bit_num);
    arr[block_idx] |= ( 1 << bit_num );
    return *this;
}
/*****************************************************************************/
template <size_t N>
BitArr<N> &BitArr<N>::SetAll()
{
    std::fill(arr, arr + s_size - 1, ~0);   
    arr[s_size - 1] = ( 1 << (N - ((s_size - 1) * NUM_BITS) )) - 1;
    return *this;
}
/*****************************************************************************/
template <size_t N>
BitArr<N> &BitArr<N>::Flip(size_t idx)
{
    size_t block_idx = 0;
    size_t bit_num = 0;
    GetIndexes(idx,&block_idx, &bit_num);
    arr[block_idx] ^= ( 1 << bit_num );
    return *this;
}
/*****************************************************************************/
template <size_t N>
BitArr<N> &BitArr<N>::FlipAll()
{
    FlipNum flip_num_functor;
    std::transform(arr, arr + s_size - 1, arr,flip_num_functor );
    arr[s_size - 1] ^= ( 1 << (N - ((s_size - 1) * NUM_BITS) )) - 1;
    return *this;
}
/*****************************************************************************/
template <size_t N>
bool BitArr<N>::operator==(const BitArr<N> &other) const
{
    return std::equal(arr,arr + s_size,other.arr);
}
/*****************************************************************************/
template <size_t N>
bool BitArr<N>::operator!=(const BitArr<N> &other) const
{
    return !BitArr<N>::operator==(other);
}
/*****************************************************************************/
template <size_t N>
BitArr<N> &BitArr<N>::operator^=(const BitArr<N> &other) 
{
    std::transform(arr, arr + s_size,
                   other.arr,arr,
                   std::bit_xor<unsigned int>());
    return *this;
}
/*****************************************************************************/
template <size_t N>
BitArr<N> &BitArr<N>::operator&=(const BitArr<N> &other) 
{
    std::transform(arr, arr + s_size,
                   other.arr,arr,
                   std::bit_and<unsigned int>());
    return *this;
}
/*****************************************************************************/
template <size_t N>
BitArr<N> &BitArr<N>::operator|=(const BitArr<N> &other) 
{
    std::transform(arr, arr + s_size,
                   other.arr,arr,
                   std::bit_or<unsigned int>());
    return *this;
}
/*****************************************************************************/
/*****************************************************************************/
template <size_t N>
void BitArr<N>::GetIndexes(size_t idx, size_t *block_idx, size_t *bit_num) const
{
    *block_idx = idx / (NUM_BITS );
    *bit_num = idx - *block_idx * NUM_BITS;          
}
/*****************************************************************************/
/*****************************************************************************/
template <size_t N>
BitArr<N>::BitProxy::BitProxy(BitArr<N> &bit_arr_obj, size_t idx) 
                             : m_arr(bit_arr_obj), m_idx(idx)
{/* EMPTY */}
/*****************************************************************************/
template <size_t N>
typename BitArr<N>::BitProxy &BitArr<N>::BitProxy::operator=(bool other)
{
    if( other != *this )
    {
        m_arr.Flip(m_idx);
    }

    return *this;
}
/*****************************************************************************/
template <size_t N>
typename BitArr<N>::BitProxy &BitArr<N>::BitProxy::operator=(const BitProxy &other)
{
    return *this = other.m_arr.Get(other.m_idx);
}
/*****************************************************************************/
template <size_t N>
BitArr<N>::BitProxy::operator bool()
{
    return (m_arr.Get(m_idx));
}
/*****************************************************************************/
template <size_t N>
typename BitArr<N>::BitProxy BitArr<N>::operator[](size_t idx)
{
    BitProxy bit_proxy(*this, idx);
    return bit_proxy;
}
/*****************************************************************************/
template <size_t N>
size_t BitArr<N>::Count() const
{
    size_t count = 0;
    Counter counter_functor(&count);
    std::for_each(arr, arr + s_size, counter_functor);
    return count;
}
/*****************************************************************************/
template <size_t N>
std::string BitArr<N>::ToString() const
{
    std::string str_ans;
    ToStr ToStr_functor(str_ans);
    std::for_each(arr, arr + s_size - 1, ToStr_functor);

    size_t left = N - (s_size - 1) * sizeof(arr[0]);

    char c = 0;
    while(left)
    {
        c = Get(N - left) + '0';
        str_ans += c;
        --left;
    }

    return str_ans;

}


}// end ilrd_rd100
#endif /*__ILRD_RCSTRING_HPP__*/
