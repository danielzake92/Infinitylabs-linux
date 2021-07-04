#include <iostream>

#include "string.hpp"
using namespace ilrd_rd100;

void Test1(const String str);//naming

int main()
{
    String s1("hello its a big string");
    String s2("hello");
    String s3(s1);

    String s32;

    String arr[5];

    arr[2] = "55";

    std::cout << "arr[2] ->" << arr[2] << std::endl;

    std::cout << "s1 ->" << s1.CStr() << std::endl;
    std::cout << "s1.Length = " << s1.Length() << std::endl;

    std::cout << "s2 ->" << s2.CStr() << std::endl;
    std::cout << "s2.Length = " << s2.Length() << std::endl;

    std::cout << "s3 ->" << s3.CStr() << std::endl;
    std::cout << "s3.Length = " << s3.Length() << std::endl;

    std::cout << "s1==s2 ->" << (s1==s2) << std::endl;
    std::cout << "s1>s2 ->" << (s1>s2) << std::endl;
    std::cout << "s1<s2 ->" << (s1<s2) << std::endl;

    s2 = s1;
    std::cout << "s1==s2 ->" << (s1==s2) << std::endl;


    s1 = s1;

    String &a = s1;

    a = s1;

    //String s5(NULL);
    //string &a(s1);


    std::cout << "a ->" << a.CStr() << std::endl;

    std::cout << "s2 = s1" << std::endl;

    std::cout << "s1 ->" << s1.CStr() << std::endl;
    std::cout << "s1.Length = " << s1.Length() << std::endl;
    
    std::cout << "s2 ->" << s2.CStr() << std::endl;
    std::cout << "s2.Length = " << s2.Length() << std::endl;


    Test1("hllis");

    std::cout<< s1 << std::endl;
    std::cout<< "\"hello its a big string\" == s1 ->" <<("hello its a big string" == s1) << std::endl;
    std::cout<< "\"hello its a bng\" == s1 ->" <<("hello its a bng" == s1) << std::endl;

}
void Test1(const String str)
{
    std::cout << "str ->" << str.CStr() << std::endl;
    std::cout << "str.Length = " << str.Length() << std::endl;

}