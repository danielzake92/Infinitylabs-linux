#include <iostream> //std::cout


const int EMPTY = 0xAAAADDDD;
const int ARR_SIZE = 10;

class Stack
{
public:
	Stack();
	void Push(int data);
	int Pop();
	void Print() const;

private:
	int arr[ARR_SIZE];
	int index;
};

Stack::Stack(): index(0)
{
	std::cout<<"Stack::Ctor"<<std::endl;
}

void Stack::Push(int data)
{
	if(ARR_SIZE <= index)
	{
		return;
	}
	arr[index++] = data;
}

int Stack::Pop()
{
	if(0 >= index)
	{
		return EMPTY;
	}
	return arr[index--];
}

void Stack::Print() const
{
	int i = 0;

	for(;i < index; ++i)
	{
		std::cout<<"arr[ "<< i <<"] -> "<<arr[i] << std::endl;
	}
}

int main()
{
	
	Stack s1;

	size_t i = 0;

	s1.Print();

	for(i = 0 ;i < ARR_SIZE + 20; ++i)
	{
		s1.Push(i);
	}

	s1.Print();

	std::cout<<std::endl;
	std::cout<<std::endl;

	for(i = 0;i < ARR_SIZE + 10; ++i)
	{
		s1.Pop();
	}

	s1.Print();

	s1.Push(101);
	s1.Push(102);

	s1.Print();
	return 0;
}