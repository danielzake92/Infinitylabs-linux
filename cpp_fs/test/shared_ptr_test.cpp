/****************************************************************************
* FILE: shared_ptr_test.hpp	            PURPOSE: API for SharedPtr Class.
*
* DEVELOPER: DanielZ
*
* REVIEWER:  Liad OZ	                STATUS: 
*
****************************************************************************/

#include <iostream> // std::cout

#include "tester.hpp" // test utills
#include "shared_ptr.hpp"


class Animal
{
public:
    Animal(int num) : m_a(num)
    {
        //std::cout<<"Animal Ctor"<<std::endl;
    }
    Animal(const Animal &other)
    {
        m_a = other.m_a;
        //std::cout<<"Animal CCtor"<<std::endl;
    }
    virtual ~Animal()
    {
        //std::cout<<"Animal Dtor"<<std::endl;
    }
    virtual void Show() const
    {
        //std::cout<<"Animal show m_a = "<<m_a<<std::endl;
    }
    virtual int Get() const
    {
        return m_a;
    }
private:
    int m_a;
};
class Dog : public Animal
{
public:
    Dog() : Animal(2),m_d(10)
    {
        //std::cout<<"Dog Ctor"<<std::endl;
    }
    Dog(const Dog &other) : Animal(other)
    {
        m_d = other.m_d;
        //std::cout<<"Dog CCtor"<<std::endl;
    }
    virtual ~Dog()
    {
        //std::cout<<"Dog Dtor"<<std::endl;
    }
    virtual void Show() const
    {
        //std::cout<<"Dog show m_d = "<<m_d<<std::endl;
    }
    virtual int Get() const
    {
        return m_d;
    }
private:
    int m_d;
};


using namespace ilrd_rd100;
/********************************* driver ************************************/
int main(void)
{
    SharedPtr<Animal> pa1(new Animal(1));
    SharedPtr<Animal> pa2(new Animal(2));
    SharedPtr<Animal> pa3(pa1);

    SharedPtr<Dog> pd1(new Dog);
    SharedPtr<Dog> pd2(new Dog);
    SharedPtr<Dog> pd3(pd1);

    SharedPtr<Animal> pa4(pd3);

    SharedPtr<Animal> pa5;

    pa5.Get();

    Test( (pa1.Get() == pa3.Get()), true,"Cctor test" ,__LINE__);
    Test( (pa1.Get() != pa2.Get()), true,"Cctor test" ,__LINE__);

    Test( (pd1.Get() == pd3.Get()), true,"Cctor test" ,__LINE__);
    Test( (pa4.Get() == pd3.Get()), true,"Cctor test" ,__LINE__);

    Test( (pa5.Get() == NULL), true,"NULL test" ,__LINE__);


    pa1->Show();
    (*pa2).Show();

    pa1 = pa2;

    pd1 = pd2;
    pa1 = pa3;
    pa1 = pd1;

    (*pa1) = (*pa2);


	TestReport("end");

	return 0;
}
/*****************************************************************************/
