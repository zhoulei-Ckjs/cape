#include "Log.h"
#include <string>
#include <chrono>

namespace cape
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

    void Log::Close()
    {
        if(dog_log.is_open())
            dog_log.close();
    }
}