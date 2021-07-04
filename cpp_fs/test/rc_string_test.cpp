/****************************************************************************
* FILE: rc_string_test.cpp		        Purpose: Implementation for RCString Class.
*
* DEVELOPER: Daniel Zaken						
*
* REVIEWER: Itamar Aron				STATUS: Approved
*
****************************************************************************/
#include <sstream> //string stream
#include <string> //string
#include <cstring> // strcpy

#include "rc_string.hpp"
#include "tester.hpp" //test utils lib
using namespace ilrd_rd100;

static void CreationTest(void);
static void StringBoolOpTest(void);
static void StringRefTest(void);
static void StringBracketsTest(void);
static void StreamOpTest(void);
static size_t GetCounterByHack(RCString *str);


int main()
{
    CreationTest();
    StringBoolOpTest();
    StringRefTest();
    StringBracketsTest();
    StreamOpTest();
    TestReport("RC_STRING Report");
}

static void CreationTest(void)
{
    RCString s1;
    RCString s2 = "Should be defaultive Ctor";
    RCString s3("defaultive Ctor");
    RCString s4(s2);
    RCString s5("!@09   $");

    Test(s1, RCString(""), "Creation Test", __LINE__);
    Test(s2, RCString("Should be defaultive Ctor"), "Creation Test", __LINE__);
    Test(s3, RCString("defaultive Ctor"), "Creation Test", __LINE__);
    Test(s4, s2, "Creation Test", __LINE__);
    Test(strcmp(s5.CStr(),"!@09   $"), 0 , "Creation Test", __LINE__);

}

static void StringBoolOpTest(void)
{
    RCString s1 = "danielz";
    RCString s2(s1);
    RCString s3(s1);
    RCString s4 = "something else";

    Test( s1.IsStringShared(), true , "Operator ==", __LINE__);
    Test( s2.IsStringShared(), true , "Operator ==", __LINE__);
    Test( s3.IsStringShared(), true , "Operator ==", __LINE__);
    Test( s4.IsStringShared(), false , "Operator ==", __LINE__);

    Test(( s1 == s2 ), true , "Operator ==", __LINE__);
    Test(( s1 == s2 ), true , "Operator ==", __LINE__);
    Test(( s1 != s2 ), false , "Operator !=", __LINE__);

    Test(( s1 > s2 ), false , "Operator >", __LINE__);
    Test(( s1 > s4 ), false , "Operator >", __LINE__);
    Test(( s4 > s2 ), true , "Operator >", __LINE__);

    Test(( s4 < s2 ), false , "Operator <", __LINE__);
    Test(( s3 < s4 ), true , "Operator <", __LINE__);

}

static void StringRefTest(void)
{
    RCString s1 = "danielz";
    Test(GetCounterByHack(&s1), static_cast<size_t>(1) , "Test num of copies", __LINE__);

    RCString s2(s1);
    Test(GetCounterByHack(&s1), static_cast<size_t>(2) , "Test num of copies", __LINE__);

    RCString s3(s1);
    Test(GetCounterByHack(&s1), static_cast<size_t>(3) , "Test num of copies", __LINE__);

    RCString s4 = "something else";
    Test(GetCounterByHack(&s4), static_cast<size_t>(1) , "Test num of copies", __LINE__);

    s1 = s4;
    Test(GetCounterByHack(&s1), static_cast<size_t>(2) , "Test num of copies", __LINE__);
    Test(GetCounterByHack(&s4), static_cast<size_t>(2) , "Test num of copies", __LINE__);

    s1 = s1;
    Test(GetCounterByHack(&s1), static_cast<size_t>(2) , "Test num of copies", __LINE__);

    RCString s5;
    RCString s6;

    s5 = "daniel";
    Test(GetCounterByHack(&s5), static_cast<size_t>(1) , "Test num of copies", __LINE__);

    s6 = "wow its a long string";
    Test(GetCounterByHack(&s6), static_cast<size_t>(1) , "Test num of copies", __LINE__);

    s5 = s6;
    Test(GetCounterByHack(&s5), static_cast<size_t>(2) , "Test num of copies", __LINE__);
    Test(GetCounterByHack(&s6), static_cast<size_t>(2) , "Test num of copies", __LINE__);

    RCString str1("Hello World");
    RCString str2("bla");
    RCString str3("bla");
    RCString str4("bla");
    RCString str5("Hello World");

    str1 = str1;
    str2 = str1;
    str3 = str2;
    str4 = str1;
    str5 = str1;
    Test(GetCounterByHack(&str1), static_cast<size_t>(5) , "Test num of copies", __LINE__);
    str5 = "what?!";
    Test(GetCounterByHack(&str1), static_cast<size_t>(4) , "Test num of copies", __LINE__);
    Test(GetCounterByHack(&str5), static_cast<size_t>(1) , "Test num of copies", __LINE__);

}

static void StringBracketsTest(void)
{
    RCString s1 = "danielz";
    RCString s2;

    Test(s1[0],'d', "Test Brackets op", __LINE__);
    Test(s1[1],'a', "Test Brackets op", __LINE__);
    Test(s1[2],'n', "Test Brackets op", __LINE__);
    Test(s1[3],'i', "Test Brackets op", __LINE__);
    Test(s1[4],'e', "Test Brackets op", __LINE__);
    Test(s1[5],'l', "Test Brackets op", __LINE__);
    Test(s1[6],'z', "Test Brackets op", __LINE__);

    s2 = s1;

    s1[0] = 'j';
    s1[5] = 'h';

    Test((s1 == "janiehz"),static_cast<bool>(1), "Test CopyOnWrite", __LINE__);
    Test((s2 == "danielz"),static_cast<bool>(1), "Test CopyOnWrite", __LINE__);
    Test((s2 == s1),static_cast<bool>(0), "Test CopyOnWrite", __LINE__);
    Test((s2 != s1),static_cast<bool>(1), "Test CopyOnWrite", __LINE__);
}

static void StreamOpTest(void)
{
    RCString s1 = "danielz";
    
    std::ostringstream lhs_stream;
    std::ostringstream rhs_stream;

    lhs_stream << s1;
    rhs_stream << "danielz";

    std::string lhs_str = lhs_stream.str();
    std::string rhs_str = rhs_stream.str();

    Test(lhs_str, rhs_str,"Operator <<", __LINE__ );

    RCString s2 = "danielz";
    RCString s3 = "danielz";


    std::cin >> s2 >> s3;

    std::cout<< std::endl;

    std::cout<< s2 << std::endl;
    std::cout<< s3 << std::endl;
}

static size_t GetCounterByHack(RCString *str)
{
    size_t *sptr = (size_t*)str;
    return *((size_t*)*sptr);
}
