#include <fstream>

#include "WorkFlow.h"
#include "RestDog.h"
#include "Common.h"

void test()
{
    std::vector<std::string> args_vec;
    args_vec.push_back("ls");
    args_vec.push_back("-lh");
    WorkFlow::StartProgram(args_vec);
    WorkFlow::StopProgram("main");
}

void StartDog()
{
    dog::cout << dog::endl;
    dog::cout << "*********************************************" << dog::endl;
    dog::cout << "       =999=.       *505*      *^^^^        " << dog::endl;
    dog::cout << "       |     *     @     *    ♥    <--      " << dog::endl;
    dog::cout << "       *     #     *     $    *      *       " << dog::endl;
    dog::cout << "       *6666^        O.O      .(⊙_☉)        " << dog::endl;
    dog::cout << "*********************************************" << dog::endl;
    dog::cout << "                   Started                   " << dog::endl;
    dog::cout << "*********************************************" << dog::endl;
}

int main()
{
    dog::cout.Open("dog.log");
    StartDog();
    RestDog dog;
    dog.CreateServer();
    while(true)
        sleep(1);
    std::cout << "123" << std::endl;
    return 0;
}
