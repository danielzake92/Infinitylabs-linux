/****************************************************************************
* FILE: rc_string.hpp		        Purpose: Implementation for RCString Class.
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Itamar Aron				STATUS: Approved
*
*
****************************************************************************/
#ifndef __ILRD_RD100_RCSTRING_HPP__
#define __ILRD_RD100_RCSTRING_HPP__

#include <cstddef> // size_t
#include <iostream> // //std::cout std::cin

namespace ilrd_rd100
{//namespace ilrd_rd100 start

class RCString
{
public:
    //Ctor CCtor Dtor
    RCString(const char *str = ""); //non explicit by design
    RCString(const RCString &other);
    ~RCString();

    //Member function
    const char *CStr() const;
    size_t Length() const;
    bool IsStringShared() const;

    //Operators
    RCString &operator=(const RCString &other);
    
    char operator[](size_t idx) const;
    char &operator[](size_t idx);
    
    static const size_t buffsiz = 1024;
private:
    size_t *m_ref;
    char *m_cstr;
    //utils
    void MakeACpy(const char *str);
    void ShallowCpy(const RCString& other);
    void DeleteFields();
    char *StringAllocAndCopy(const char *src);

};

//io operators
std::ostream &operator<<(std::ostream &lhs, const RCString &rhs);
std::istream &operator>>(std::istream &lhs, RCString &rhs);//buffer size 1024


// operators ==, >, and < compare between strings lexicographically
bool operator==(const RCString &lhs, const RCString &rhs);
bool operator!=(const RCString &lhs, const RCString &rhs);
bool operator>(const RCString &lhs, const RCString &rhs);
bool operator<(const RCString &lhs, const RCString &rhs);


}//namespace ilrd_rd100 end

#endif /*__ILRD_RCSTRING_HPP__*/

