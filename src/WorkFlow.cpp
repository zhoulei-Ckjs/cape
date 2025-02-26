#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

#include "WorkFlow.h"
#include "DogLog.h"

StartStatus WorkFlow::StartProgram(std::vector<std::string>& args_vec)
{
    if(args_vec.empty())
        return INCOMPLETE_ARGS;

    pid_t pid = fork();
    if(pid < 0)
        return FORK_FAILED;
    if(pid == 0)
    {
        dog::cout << dog::time << "正在启动进程 [" << args_vec[0] << "] ..." << dog::endl;
        /// 使用 execvp 启动新的程序
        char *args[4] = {nullptr};
        for(int i = 0; i < args_vec.size(); i++)
        {
            args[i] = const_cast<char*>(args_vec[i].c_str());
        }
        execvp(args[0], args); ///< 这会用 待执行的进程 替换当前子进程
        dog::cout << dog::time << "[Error] 进程启动失败！" << dog::endl;
        exit(0);
    }
    else
    {
        /// 父进程代码
        dog::cout << dog::time << "父进程：等待子进程结束" << dog::endl;
        wait(nullptr);  ///< 等待子进程结束
        dog::cout << dog::time << "子进程结束" << dog::endl;
    }

    return START_SUCCESS;
}

StopStatus WorkFlow::StopProgram(std::string name)
{
    std::string command = "pkill -9 ";
    command += name;
    std::cout << "正在停止进程 [" << name << "] ..." << std::endl;

    if (system(command.c_str()) == 0)
    {
        std::cout << "进程 [" << name << "] 成功杀死." << std::endl;
        return STOP_SUCCESS;
    }
    else
    {
        std::cerr << "无法杀死 [" << name << "]" << std::endl;
        return STOP_FAILED;
    }
}