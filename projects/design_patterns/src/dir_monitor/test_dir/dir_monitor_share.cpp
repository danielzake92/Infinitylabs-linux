#include <iostream> // io
#include <unistd.h> //write

__attribute__((constructor))
static void example_plugin_ctor() 
{
    write(STDOUT_FILENO, "plugin loaded!\n",16);
//   std::cout << "plugin loaded!" << std::endl;
}

// extern "C" void foo()
// {
//     std::cout << "plugin loaded!" << std::endl;
// }