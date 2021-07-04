/*****************************************************************************
*	FILENAME:	weird_string.cpp           AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for weird_string lib.							     *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout
#include <cstring> // cstrings


class String
{
public:

    String(const char *str = "ABC"); //non explicit by design

    String(const String &other);

    void operator=(const String &other);

    String &operator=(const char);

	char &operator[](size_t idx);

	size_t static GetInstances();

    ~String();
	
private:

	static size_t m_counter;
    char *m_cstr;
	void AllocAndCpy(const char * str);
};

size_t String::m_counter = 0;

void String::AllocAndCpy(const char * str)
{
	size_t len = strlen(str) + 1;
	m_cstr = new char[len];
	memcpy(m_cstr, str,len);
}

String::String(const char *str)
{
	AllocAndCpy(str);
	++m_counter;
}

String::String(const String &other)
{
	AllocAndCpy(other.m_cstr);
	++m_counter;
}

void String::operator=(const String &other)
{
	char *temp = m_cstr;
	AllocAndCpy(other.m_cstr);
	delete[] temp;
}

String &String::operator=(const char c)
{
	char *run = m_cstr;
	while(*run)
	{
		*run = c;
		++run;
	}
	return *this;
}

char &String::operator[](size_t idx)
{
	return *(m_cstr + idx);
}

String::~String()
{
	delete[] m_cstr;
	--m_counter;
}

size_t String::GetInstances()
{
	return m_counter;
}

int main(void)
{
	String s0;

	String s1("1234");

	String s2(s1);

	s1[0] = 'r';

	s2[0] = s1[1];

	s1 = "abc";

	s1 = s2;

	s1 = 'a';

	return 0;
}
/*****************************************************************************/
