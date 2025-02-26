#ifndef DOCKER_WORKFLOW_H
#define DOCKER_WORKFLOW_H

#include <string>
#include <vector>

enum StartStatus
{
    START_SUCCESS = 0,
    INCOMPLETE_ARGS = 1,
    FORK_FAILED = 2,
    START_FAILED = 3
};

enum StopStatus
{
    STOP_SUCCESS = 0,
    STOP_FAILED = 1
};

class WorkFlow
{
public:
    static StartStatus StartProgram(std::vector<std::string>& args_vec);
    static StopStatus StopProgram(std::string name);
};


#endif //DOCKER_WORKFLOW_H
