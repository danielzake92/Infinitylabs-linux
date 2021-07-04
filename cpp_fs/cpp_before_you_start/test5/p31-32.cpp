// set_unexpected example
#include <iostream>       // std::cerr
#include <exception>      // std::set_unexpected
#include <cstdlib> 

void myunexpected ()
{
  std::cerr << "unexpected called\n";
  throw 'x';     // throws int (in exception-specification)
}

void myterminate () 
{
  std::cerr << "terminate handler called\n";
  //exit(1);
}

void myfunction () throw () 
{
  throw 'x';   // throws char (not in exception-specification)
}

int main (void)
{
  std::set_unexpected (myunexpected);
  std::set_terminate (myterminate);
  try
  {
    myfunction();
  }
  catch (int) { std::cerr << "caught int\n"; }
  catch (...) { std::cerr << "caught some other exception type\n"; }
  return 0;
}






