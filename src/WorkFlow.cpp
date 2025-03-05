#include <unistd.h>
#include <sys/wait.h>

#include "WorkFlow.h"
#include "Log.h"
#include "RestWatcher.h"

pid_t WorkFlow::StartProgram(std::vector<std::string>& args_vec)
{
    dog::cout << dog::time << "正在启动进程 [" << args_vec[0] << "] ..." << dog::endl;

    if(args_vec.empty())
    {
        dog::cout << dog::time << "[Error]: 启动参数为空!!!" << dog::endl;
        return -1;
    }

    if (access(args_vec[0].c_str(), F_OK) != 0)
    {
        dog::cout << dog::time << "[Error]: 文件 [" << args_vec[0] << "] 不存在!!!" << dog::endl;
        return -1;
    }

    pid_t pid = fork();
    if(pid < 0)
    {
        dog::cout << dog::time << "[Error]: 启动时创建进程失败!!!" << dog::endl;
        return -1;
    }

    if(pid == 0)
    {
        pid_t session_id = setsid();
        if(session_id < 0)
        {
            std::cout << "创建会话失败" << std::endl;
            dog::cout << dog::time << "创建会话失败" << dog::endl;
            kill(getpid(), SIGKILL);
        }
        /// 使用 execvp 启动新的程序
        char *args[4] = {nullptr};
        for(int i = 0; i < args_vec.size(); i++)
        {
            args[i] = const_cast<char*>(args_vec[i].c_str());
        }
        execvp(args[0], args); ///< 这会用 待执行的进程 替换当前子进程

        dog::cout << dog::time << "[child][Error]: 进程 [" << args[0] << "] 失败, 退出!!!" << dog::endl;
        /// 在调用execvp失败的情况下，无法调用exit退出子进程，由于cpprest的原因。
        kill(getpid(), SIGKILL);
    }

    return pid;
}

std::vector<int> WorkFlow::CheckProgram(const std::string& name)
{
    std::vector<int> ret;
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "pgrep -x %s", name.c_str());

    // 打开管道执行命令
    FILE* fp = popen(cmd, "r");
    if (fp == nullptr)
    {
        dog::cout << dog::time << "执行命令失败" << cmd << dog::endl;
        return ret;
    }

    // 读取命令输出
    char buffer[16];

    while (fgets(buffer, sizeof(buffer), fp) != nullptr)
    {
        std::string temp(buffer);
        temp.pop_back();
        ret.push_back(stoi(temp));
    }

    fclose(fp);
    return ret;
}

StopStatus WorkFlow::StopProgram(const std::string& name, const std::vector<int>& pids)
{
    dog::cout << dog::time << "正在停止进程 [" << name << "] ..." << dog::endl;
    int status;             ///< 子进程退出状态
    for (auto it : pids)
    {
        kill(-getsid(it), SIGKILL);
        waitpid(it, &status, 0);
    }

    std::vector<int> left = CheckProgram(name);
    if(left.empty())
    {
        dog::cout << dog::time << "进程 [" << name << "] 成功杀死." << dog::endl;
        return STOP_SUCCESS;
    }
    else
    {
        std::string command = "pkill -9 ";
        command += name;

        system(command.c_str());

        left = CheckProgram(name);
        if(left.empty())
        {
            dog::cout << dog::time << "进程 [" << name << "] 成功杀死." << dog::endl;
            return STOP_SUCCESS;
        }

        dog::cout << dog::time << "无法杀死 [" << name << "]" << dog::endl;
        return STOP_FAILED;
    }
}