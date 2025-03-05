#include "Log.h"
#include <string>
#include <chrono>

namespace dog
{
    Log cout;
    Time time;

    void endl(Log d){}

    Log::OpenStatus Log::Open(char *file_name)
    {
        dog_log.open(file_name, std::ios::app | std::ios::out);
        if (dog_log.is_open())
            return OPEN_SUCCESS;
        return OPEN_FAILURE;
    }
}