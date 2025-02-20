#include "WorkFlow.h"
#include "RestDog.h"

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
    RestDog dog;
    dog.CreateServer();
    while(true)
        sleep(1);
    return 0;
}
