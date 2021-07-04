#include "tester.hpp"
#include "bitarr.hpp"

using namespace ilrd_rd100; 
using namespace std; 

void TestGetSetCtor(void);
void TestFlip(void);
void TestXorAndOrOP(void);
void TestBitProxy(void);
void TestCounter(void);

void Foo(void);


int main()
{
	TestGetSetCtor();
	TestFlip();
	TestXorAndOrOP();
	TestBitProxy();
	TestCounter();

	TestReport("Bittarray test");
	return 0;
}
void TestGetSetCtor(void)
{
	BitArr<22> b1;
	b1 = b1.Set(10);

	Test(b1.Get(10) == 1, true, "Get and Set", __LINE__);
	Test(b1.Get(9) == 0, true, "Get and Set", __LINE__);

	const BitArr<33> b2;

	Test(b1.Get(10) == 1, true, "Get and Set", __LINE__);
	Test(b2[10] == 0, true, "Get and Set", __LINE__);

	BitArr<22> b3(b1);

	Test(b3.Get(10) == 1, true, "Defaultive Cctor", __LINE__);
	Test(b1 == b3, true, "Operator=", __LINE__);

	b3 = b3.Set(5);

	Test(b1 != b3, true, "Operator=", __LINE__);

	b3 = b3.SetAll();
	Test(b3.Get(5) == 1, true, "SetAll", __LINE__);
	Test(b3.Get(18) == 1, true, "SetAll", __LINE__);
	Test(b3.Get(21) == 1, true, "SetAll", __LINE__);
}
/*****************************************************************************/
void TestFlip(void)
{
	BitArr<92> b1;
	BitArr<92> b2;

	b1 = b1.Set(87);
	Test(b1.Get(87) == 1, true, "Get and Set", __LINE__);

	b1 = b1.Set(83);
	Test(b1.Get(83) == 1, true, "Get and Set", __LINE__);

	b1 = b1.Flip(83);
	Test(b1.Get(83) == 0, true, "Flip", __LINE__);

	b1 = b1.FlipAll();
	Test(b1.Get(83) == 1, true, "Flip", __LINE__);

	size_t i = 0;
	for(i = 0; i < 92 && 87!= i; ++i)
	{
		Test(b1.Get(i) == 1, true, "Flip", __LINE__);	
	}

}
/*****************************************************************************/
void TestXorAndOrOP()
{
	BitArr<4> b1;
	BitArr<4> b2;
	BitArr<4> b3;

	//1010
	b1 = b1.Set(1);
	b1 = b1.Set(3);

	//0101
	b2 = b2.Set(0);
	b2 = b2.Set(2);

	b1 ^= b2; //1010 ^ 0101 = 1111	

	Test(b1.Get(0) == 1, true, "XOR", __LINE__);
	Test(b1.Get(1) == 1, true, "XOR", __LINE__);
	Test(b1.Get(2) == 1, true, "XOR", __LINE__);
	Test(b1.Get(3) == 1, true, "XOR", __LINE__);

	b1 &= b3; //1111 & 0000 = 0000

	Test(b1.Get(0) == 0, true, "AND", __LINE__);
	Test(b1.Get(1) == 0, true, "AND", __LINE__);
	Test(b1.Get(2) == 0, true, "AND", __LINE__);
	Test(b1.Get(3) == 0, true, "AND", __LINE__);

	//1010
	b1 = b1.Set(1);
	b1 = b1.Set(3);	

	//1111
	b2 = b2.SetAll();

	b1 |= b2; //1010 | 1111 = 1111

	Test(b1.Get(0) == 1, true, "OR", __LINE__);
	Test(b1.Get(1) == 1, true, "OR", __LINE__);
	Test(b1.Get(2) == 1, true, "OR", __LINE__);
	Test(b1.Get(3) == 1, true, "OR", __LINE__);
}
/*****************************************************************************/
void TestBitProxy()
{
	BitArr<4> b1;

	b1[0] = 1;
	b1[1] = b1[0];

	Test(b1.Get(0) == 1, true, "BIT PROXY", __LINE__);
	Test(b1.Get(1) == 1, true, "BIT PROXY", __LINE__);

}
/*****************************************************************************/
void TestCounter()
{
	BitArr<12> b1;

	Test(b1.Count() == 0, true, "COUNT", __LINE__);

	b1 = b1.SetAll();

	Test(b1.Count() == 12, true, "COUNT", __LINE__);

	b1[5] = 0;
	Test(b1.Count() == 11, true, "COUNT", __LINE__);

	b1[2] = b1[5];
	Test(b1.Count() == 10, true, "COUNT", __LINE__);

	cout<< b1.ToString()<<endl;

	BitArr<4> b2;

	b2[0] = 1;
	b2[1] = 1;

	cout<< b2.ToString()<<endl;

}
/*****************************************************************************/
// void Foo(void)
// {
// 	size_t var = 8;
// 	BitArr<var> b1;
// }

