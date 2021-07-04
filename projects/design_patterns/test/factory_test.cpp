/*****************************************************************************
*	FILENAME:	factory_test.cpp              AUTHOR: Daniel Zaken  LAB: RD100	 *
 *																			 *
 *	REVIEWER:																 *
 *																			 *
 *	PURPOSE:    Testing for factory lib.							      	 *
 *																			 *
 *****************************************************************************/

#include <iostream> // cout

#include <boost/shared_ptr.hpp> //shared_ptr

#include "tester.hpp" // test utills

#include "factory.hpp"

using namespace ilrd_rd100;
/********************************* driver ************************************/

class Animal
{
public:
    virtual ~Animal(){}
    virtual void MakeSound(){}
};

class Lion : public Animal
{
public:
    Lion(int age): m_age(age)
	{
		std::cout << "Lion Ctor" << std::endl;
	}
    ~Lion()
	{
		std::cout << "Lion Dtor" << std::endl;
	}
    virtual void MakeSound()
    {
        std::cout << "I am a Lion" << std::endl;
    }

	static boost::shared_ptr<Animal> FactoryFunc(int param)
	{
		boost::shared_ptr<Lion> l_ptr(new Lion(param));
		return l_ptr;
	}

private:
	int m_age;
};

class Elephent : public Animal
{
public:
    Elephent(int age): m_age(age)
	{
		std::cout << "Elephent Ctor" << std::endl;
	}
    ~Elephent()
	{
		std::cout << "Elephent Dtor" << std::endl;
	}
    virtual void MakeSound()
    {
        std::cout << "I am a Elephent" << std::endl;
    }

	static boost::shared_ptr<Animal> FactoryFunc(int param)
	{
		boost::shared_ptr<Elephent> e_ptr(new Elephent(param));
		return e_ptr;
	}

private:
	int m_age;
};


int main(void)
{
	Factory<std::string, boost::shared_ptr<Animal>, int> f;

	f.Add("lion",  Lion::FactoryFunc);
	f.Add("elephent",  Elephent::FactoryFunc);

	boost::shared_ptr<Animal> leo(f.Create("lion", 3));
	boost::shared_ptr<Animal> elphi(f.Create("elephent", 5));

	TestReport("Factory test");

	return 0;
}
/*****************************************************************************/
