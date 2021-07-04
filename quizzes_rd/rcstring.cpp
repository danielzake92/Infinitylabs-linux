
#include <iostream> // cout
#include <cstring> //strcpy

class String
{
public:

	String &operator=(const String &other);
	String &operator=(const char *other);

private:
	struct RC
	{
		char *m_str;
		size_t m_count;
	};

	RC *m_rc;

};

String &String::operator=(const String &other)
{
	if(m_rc->m_count > 1)
	{
		--(m_rc->m_count);
	}
	else
	{
		delete m_rc; 
		m_rc = 0;
	}
	++((other.m_rc)->m_count);
	m_rc = other.m_rc;
	return *this;
}

String &String::operator=(const char *other)
{
	char *temp = m_rc->m_str;
	m_rc->m_str = new char[strlen(other) + 1];
	strcpy(m_rc->m_str, other);

	if(m_rc->m_count > 1)
	{
		--(m_rc->m_count);
	}
	else
	{
		delete temp;
	}

	return *this;

}

