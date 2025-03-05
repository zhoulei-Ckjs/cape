#ifndef DOCKER_WORKFLOW_H
#define DOCKER_WORKFLOW_H

#include <string>
#include <vector>

enum StopStatus
{
    STOP_SUCCESS = 0,
    STOP_FAILED = 1
};

class WorkFlow
{
public:
    static pid_t StartProgram(std::vector<std::string>& args_vec);
    static std::vector<int> CheckProgram(const std::string& name);
    static StopStatus StopProgram(const std::string& name, const std::vector<int>& pids);
};


#endif //DOCKER_WORKFLOW_H
