#include <iostream>
#include "WorkFlow.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    std::vector<std::string> args_vec;
    args_vec.push_back("ls");
    args_vec.push_back("-lh");
    WorkFlow::StartProgram(args_vec);
    WorkFlow::StopProgram("main");
    return 0;
}
