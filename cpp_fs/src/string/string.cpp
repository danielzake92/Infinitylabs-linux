/****************************************************************************
* FILE: string.cpp		            Purpose: Implementation for String Class.
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Or Kats					STATUS: Approved
*
*
****************************************************************************/
#include <iostream> //std::cout
#include <cstring> //strlen, strcpy
#include <cassert> //strlen, strcpy
 
#include "string.hpp" 

namespace ilrd_rd100
{

char *BuildCstr(const char *str);

/****************************************************************************/
String::String(const char *str)
{
	assert(str);
	//m_cstr = new char [strlen(str) + 1];
	//strcpy(m_cstr, str);

	m_cstr = BuildCstr(str);

	//std::cout<< "Ctor" << std::endl;
}
/****************************************************************************/
String::String(const String& other_)
{
	m_cstr = BuildCstr(other_.m_cstr);
	
	//m_cstr = new char [strlen(other_.m_cstr) + 1];
	//strcpy(m_cstr, other_.m_cstr);//maybe memcpy better
	//std::cout<< "Cctor" << std::endl;
}
/****************************************************************************/
String& String::operator=(const String& other_) //not an acception safe
{
	size_t len = strlen(other_.m_cstr);
	
	if( len > strlen(m_cstr) )
	{
		delete[] m_cstr; //if an eception raised than ther string corupted
		m_cstr = new char [len + 1];
	}

	memmove(m_cstr, other_.m_cstr, len + 1);//for overlap //memmove good for overlap
	
	return *this;
}
/****************************************************************************/
bool operator==(const String &lhs, const String &rhs)
{
	return (0 == strcmp(lhs.CStr(), rhs.CStr())); //no cast needed
}
/****************************************************************************/
bool operator>(const String &lhs, const String &rhs)
{
	return (0 < strcmp(lhs.CStr(), rhs.CStr()));
}
/****************************************************************************/
bool operator<(const String &lhs, const String &rhs)
{
	return (0 > strcmp(lhs.CStr(), rhs.CStr()));
}
/****************************************************************************/
const char *String::CStr() const
{
	return m_cstr;
}	
/****************************************************************************/
size_t String::Length() const
{
	return strlen(m_cstr);
}
/****************************************************************************/
std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os<<str.CStr();
}
/****************************************************************************/
String::~String()
{
	delete[] m_cstr;
	m_cstr = NULL;
}
/****************************************************************************/
char *BuildCstr(const char *str)
{
	size_t len  = strlen(str) + 1;
	char *cstr = new char [len];
	memmove(cstr, str, len);
	//strcpy(cstr, str);
	return cstr;
}

}
