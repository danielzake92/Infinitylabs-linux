// set_unexpected example
#include <iostream>       // std::cerr
#include <exception>      // std::set_unexpected
#include <cstdlib> 

// void myunexpected ()
// {
//   std::cerr << "unexpected called\n";
//   throw 'x';     // throws int (in exception-specification)
// }

// void myterminate () 
// {
//   std::cerr << "terminate handler called\n";
//   //exit(1);
// }

// void myfunction () throw () 
// {
//   throw 'x';   // throws char (not in exception-specification)
// }

// int main (void)
// {
//   std::set_unexpected (myunexpected);
//   std::set_terminate (myterminate);
//   try
//   {
//     myfunction();
//   }
//   catch (int) { std::cerr << "caught int\n"; }
//   catch (...) { std::cerr << "caught some other exception type\n"; }
//   return 0;
// }

void Bar(int *ptr)
{
  std::cout << "Bar" << std::endl;
}

void Fishi()
{
  std::cout << "Fishi" << std::endl;
}

void Fifi(int *ptr)
{
  std::cout << "Fifi" << std::endl;
}

void Dodo()
{
  std::cout << "Dodo" << std::endl;

  throw(10);

}


void Foo()
{
  int *ip = new int;
  Bar(ip);
  Fishi();
  Fifi(ip);
  Dodo();
  delete ip;

}

int main()
{
  Foo();
  return 0;
}

