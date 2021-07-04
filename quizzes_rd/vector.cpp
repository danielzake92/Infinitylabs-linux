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

class Dog
{
public:
	Dog();
	Dog(const Dog &);
	~Dog();
};

Dog::Dog()
{
	std::cout<<"Dog::Ctor"<<std::endl;
}

Dog::Dog(const Dog &)
{
	std::cout<<"Dog::CCtor"<<std::endl;
}

Dog::~Dog()
{
	std::cout<<"Dog::Dtor"<<std::endl;
}

template <class T>
class Vector
{
public:

    Vector(); //non explicit by design

    Vector(size_t capacity);

    void PushBack(const T &data);

	void Resize(size_t count);

	void Reserve(size_t demand);

    ~Vector();
	
private:

	T *m_arr;
	size_t m_capacity;
	size_t m_size;

};
/*****************************************************************************/
template <class T>
Vector<T>::Vector(): m_arr(NULL), m_capacity(0), m_size(0)
{
	/* EMPTY */
}
/*****************************************************************************/
template <class T>
Vector<T>::Vector(size_t capacity): 
m_arr(static_cast<T*>(operator new(sizeof(T) * capacity))),
m_capacity(capacity),
m_size(0)
{
	/* Empty */
}
/*****************************************************************************/
template <class T>
Vector<T>::~Vector()
{
	operator delete (m_arr);
}
/*****************************************************************************/
template <class T>
void Vector<T>::PushBack(const T &data)
{
	if(0 == m_capacity)
	{
		Reserve(1);
	}
	else if(m_size == m_capacity)
	{
		Reserve(m_capacity * 2);
	}
	else
	{
		new(m_arr + m_size) T(data);
		++m_size;
	}
}
/*****************************************************************************/
template <class T>
void Vector<T>::Resize(size_t count)
{
	
}
/*****************************************************************************/
template <class T>
void Vector<T>::Reserve(size_t new_capacity)
{
	if(new_capacity > m_capacity)
	{
		T *temp = static_cast<T*>(operator new(sizeof(T) * new_capacity));
		for(size_t i = 0; i < new_capacity; ++i)
		{
			new(temp + i) T(m_arr[i]);
		}
		for(size_t i = 0; i < new_capacity; ++i)
		{
			(m_arr + i)->~T();
		}
		operator delete (m_arr);
		m_arr = temp;
		m_capacity = new_capacity;
	}
}
/*****************************************************************************/
int main(void)
{
	// Vector<int> vec1;
	// Vector<int> vec2(4);

	// vec1.PushBack(5);
	// vec1.PushBack(2);
	// vec1.PushBack(3);
	// vec1.PushBack(1);

	Vector<Dog> v1(5);

	Dog rex;
	Dog barney;

	v1.PushBack(rex);
	v1.PushBack(barney);
	v1.PushBack(barney);


	return 0;
}
/*****************************************************************************/
