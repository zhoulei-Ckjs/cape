#include "DogLog.h"
#include <string>
#include <chrono>

namespace dog
{
    DogLog cout;
    Time time;

    void endl(DogLog d){}

    DogLog::OpenStatus DogLog::Open(char *file_name)
    {
        dog_log.open(file_name, std::ios::app | std::ios::out);
        if (dog_log.is_open())
            return OPEN_SUCCESS;
        return OPEN_FAILURE;
    }
}