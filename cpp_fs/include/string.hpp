/****************************************************************************
* FILE: string.hpp		            Purpose: API for String Class.
*
* DEVELOPER:	Daniel Zaken					
*
* REVIEWER: 	Or Kaz					STATUS: Approved
*
* VERSION: 
*
****************************************************************************/
#ifndef __ILRD_RD100_STRING_HPP__
#define __ILRD_RD100_STRING_HPP__

#include <cstddef> // size_t
#include <iostream> // ostream

namespace ilrd_rd100
{

class String
{
public:


    String(const char *str = ""); //non explicit by design

    ~String();
    
    const char *CStr() const;    
    
    String(const String &other);
    
    size_t Length() const;

    //Operators
    
    String &operator=(const String &other);

private:

    char *m_cstr;
};

std::ostream &operator<<(std::ostream &lhs, const String &rhs);

bool operator==(const String &lhs, const String &rhs);

bool operator>(const String &lhs, const String &rhs);

bool operator<(const String &lhs, const String &rhs);

}

#endif /*__ILRD_STRING_HPP__*/