#include <iostream>

class Animal
{
public:
    //B():m_a(8){ std::cout << "B::Defualtive Ctor" << std::endl;}
    Animal(int a_ = 8):age(a_)
    {
    //     std::cout << "Animal::Ctor" << std::endl;
    }

    virtual ~Animal()
    {
    //    std::cout << "Animal::Dtor" << std::endl;
    }

    virtual void AnimalType() const;

    int GetAnimalAge() const;

private:
    int age;
};

void Animal::AnimalType() const
{
    std::cout << "Animal::AnimalType -> generic " << std::endl;
}

int Animal::GetAnimalAge() const
{
    std::cout << "Animal::GetAnimalAge ->" << age << std::endl;
    return age;
}

class Dog: public Animal 
{   
public:
    Dog(): Animal(),m_b(0) 
    {
    //    std::cout << "Dog::Ctor" << std::endl;
    }
    ~Dog()
    {
    //    std::cout << "Dog::Dtor" << std::endl;
    }

    virtual void AnimalType() 
    {
        std::cout << "Dog::AnimalType -> Dog "<< std::endl;
    }

private:
    int m_b;
};

class Dalmaty: public Dog
{
public:
    Dalmaty():Dog(),m_dal(0) { std::cout << "Dalmaty::Ctor" << std::endl;}
    virtual ~Dalmaty(){ std::cout << "Dalmaty::Dtor" << std::endl;}

     virtual void AnimalType() 
    {
        std::cout << "Dalmaty::AnimalType -> Dalmaty "<< std::endl;
    }

private:
    int m_dal;
};



int main()
{
    Animal *b1 = new Animal;
    Animal *b2 = new Dog;
    Animal *b3 = new Dalmaty; //not polymorphism
    Dog *b4 = new Dalmaty; //polymorphism applied


    std::cout << std::endl <<"main b1:"<< std::endl;

    b1->AnimalType();
    b1->GetAnimalAge();

    std::cout << std::endl <<"main b2:"<< std::endl;

    b2->AnimalType();
    b2->GetAnimalAge();

    Dog *xx = static_cast<Dog*>(b2);

    std::cout << std::endl <<"main xx:"<< std::endl;

    xx->AnimalType();
    xx->GetAnimalAge();

    std::cout << std::endl <<"main b3:"<< std::endl;
    b3->AnimalType();
    b3->GetAnimalAge();

    std::cout << std::endl <<"main b4:"<< std::endl;
    b4->AnimalType();
    b4->GetAnimalAge();


    delete b1;
    delete b2;
    delete b3;
    delete b4;

    return 0;
}
