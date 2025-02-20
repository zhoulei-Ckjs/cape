#ifndef DOCKER_WORKFLOW_H
#define DOCKER_WORKFLOW_H

#include <string>
#include <vector>

enum StartStatus
{
    START_SUCCESS = 0,
    INCOMPLETE_ARGS = 1,
    FORK_FAILED = 2
};

class WorkFlow
{
public:
    static int StartProgram(std::vector<std::string>& args_vec);
    static int StopProgram(std::string name);
};


#endif //DOCKER_WORKFLOW_H
