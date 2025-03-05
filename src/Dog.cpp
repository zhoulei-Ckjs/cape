#include <unistd.h>
#include <sys/wait.h>

#include "Dog.h"
#include "Log.h"


void Dog::Initialize()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        cape::cout << cape::time << "[Error]: 创建 Dog 进程失败!!!" << cape::endl;
        exit(0);
    }

    if(pid == 0)
    {

    }
}