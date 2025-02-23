#include "DogLog.h"

DogLog::Endl DogLog::endl;

DogLog::OpenStatus DogLog::Open(char* file_name)
{
    dog_log.open(file_name);
    if(dog_log.is_open())
        return OPEN_SUCCESS;
    return OPEN_FAILURE;
}