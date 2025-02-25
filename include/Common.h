#ifndef DOG_COMMON_H
#define DOG_COMMON_H

#include <fstream>

#include "DogLog.h"

#define TIMEDOG GetTime()

/**
 * @brief 日志
 */
namespace dog
{
    extern DogLog cout;
}

/**
 * @brief 获取当前时间字符串
 * @return 时间字符串
 */
extern std::string GetTime();

#endif //DOG_COMMON_H
