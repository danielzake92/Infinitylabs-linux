/****************************************************************************
* FILE: rc_string.cpp		        Purpose: Implementation for RCString Class.
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Itamar Aron				STATUS: Approved
*
*
****************************************************************************/
#include <cstring> //strlen, strcpy
#include <cassert> //assert
#include <exception>// for exception obj
#include <new> //for bad_alloc

#include "rc_string.hpp" 

namespace ilrd_rd100
{//namespace ilrd_rd100 start


/****************************************************************************/
RCString::RCString(const char *str) //defaultive Ctor  
{
	assert(str);

	MakeACpy(str);//uses new thus could throw bad alloc
}
/****************************************************************************/
RCString::RCString(const RCString& other_)//copy Ctor
{
	ShallowCpy(other_);
	++(*m_ref);
}
/****************************************************************************/
RCString& RCString::operator=(const RCString& other_) 
{
	if(this == &other_)
	{
		return *this;
	}
	if(!IsStringShared())
	{
		DeleteFields();
	}
	else
	{
		--(*m_ref);
	}

	ShallowCpy(other_);

	++(*m_ref);

	return *this;
}
/****************************************************************************/
bool operator==(const RCString &lhs, const RCString &rhs)
{
	return (0 == strcmp(lhs.CStr(), rhs.CStr())); //no cast needed
}
/****************************************************************************/
bool operator!=(const RCString &lhs, const RCString &rhs)
{
	return !(lhs == rhs); //no cast needed
}
/****************************************************************************/
bool operator>(const RCString &lhs, const RCString &rhs)
{
	return (0 < strcmp(lhs.CStr(), rhs.CStr()));
}
/****************************************************************************/
bool operator<(const RCString &lhs, const RCString &rhs)
{
	return !(lhs > rhs);
}
/****************************************************************************/
const char *RCString::CStr() const
{
	return m_cstr;
}	
/****************************************************************************/
size_t RCString::Length() const
{
	return strlen(m_cstr);
}
/****************************************************************************/
std::ostream& operator<<(std::ostream& os, const RCString& str)
{
	return os<<str.CStr();
}
/****************************************************************************/
std::istream& operator>>(std::istream& lhs, RCString& rhs)
{
	char buff[rhs.buffsiz];
	lhs>>buff;
	rhs = buff; 
	return lhs;
}
/****************************************************************************/
RCString::~RCString() 
{
	--(*m_ref);
	if(0 == *m_ref)
	{
		DeleteFields();
	}
}
/****************************************************************************/
char RCString::operator[](size_t idx) const
{
	return (*(m_cstr + idx));
}
/****************************************************************************/
char &RCString::operator[](size_t idx) 
{
	if(IsStringShared())
	{
		--(*m_ref);
		MakeACpy(m_cstr); //uses new thus could throw bad alloc
	}
	return (*(m_cstr + idx));
	// return const_cast<char&>( static_cast<const RCString&>(*this)[idx]); //mayers
}
/****************************************************************************/
bool RCString::IsStringShared() const
{
	return (1 < *m_ref) ? true : false;
}
/****************************************************************************/
char *RCString::StringAllocAndCopy(const char *str)
{
	char *cstr = static_cast<char*>
				 (operator new (sizeof(char) * (strlen(str) + 1)));
	strcpy(cstr, str);
	return cstr;
}
/****************************************************************************/
void RCString::ShallowCpy(const RCString& other)
{
	m_cstr = other.m_cstr;
	m_ref = other.m_ref;
}
/****************************************************************************/
void RCString::DeleteFields()
{
	delete m_ref; m_ref = NULL;
	delete m_cstr; m_cstr = NULL;
}
/****************************************************************************/
void RCString::MakeACpy(const char *str)
{
	m_ref = NULL;
	m_cstr = NULL;

	try
	{
		m_ref = new size_t(1);
		m_cstr = StringAllocAndCopy(str); //uses new thus could throw bad alloc
	}
	catch(const std::bad_alloc& e)
	{
		std::cerr << e.what() << '\n';
		DeleteFields();
		std::bad_alloc bad;
		throw(bad);
	}
}





}//namespace ilrd_rd100 end

