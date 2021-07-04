/****************************************************************************
* FILE: tester.hpp		            Purpose: Tester Template Header
*
* DEVELOPER: Itamar Aron						
*
* VERSION: 1
*
****************************************************************************/

#include <iostream> //cout, cin
#include <cstddef> //size_t

# define BLACK "\033[30;1m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
# define BLUE "\033[34;1m"
# define PURPLE "\033[35;1m"
# define CYAN "\033[36;1m"
# define WHITE "\033[37;1m"
# define DEFAULT "\x1b[0;0m"

static size_t num_tests = 0;
static size_t num_passed = 0;

template <typename T>
void inline Test(const T &t1, const T &t2, const std::string &name, int line)
{
    ++num_tests;

    if (t1 == t2)
    {
        ++num_passed;
    }
    else
    {
        std::cout << "\033[1;31mTest " << name << " in line "  << line << " Failed \033[0m" << std::endl;
    }
}

inline void TestReport(const std::string &subject)
{
    if (num_passed != num_tests)
    {
        std::cout << "\033[1;31m" << subject <<": Passed " << 
        num_passed << "/" << num_tests << " tests.\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1;32m" <<subject << ": Passed All "<<num_tests<< " Tests!\033[0m" << std::endl;
    }
}