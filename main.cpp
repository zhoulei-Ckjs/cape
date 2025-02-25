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

int main()
{
    dog::cout.Open("dog.log");
    dog::cout << dog::time << "监控程序开始运行！" << dog::endl;
    RestDog dog;
    dog.CreateServer();
    while(true)
        sleep(1);
    std::cout << "123" << std::endl;
    return 0;
}
