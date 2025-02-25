#ifndef DOG_DOGLOG_H
#define DOG_DOGLOG_H

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

namespace dog
{
    class Time{};

    class DogLog
    {
    public:
        enum OpenStatus
        {
            OPEN_SUCCESS = 0,
            OPEN_FAILURE = 1
        };

        /**
         * @brief 打开日志文件
         * @param file_name 日志文件名
         * @return 打开状态
         */
        OpenStatus Open(char* file_name);

        template<class T>
        DogLog& operator<<(const T& message)
        {
            if(dog_log.is_open())
            {
                dog_log << message;
            }
            else
            {
                std::cerr << "[Error]：未指定输出日志文件名或日志文件打开失败！" << std::endl;
            }
            return *this;
        }

        DogLog& operator<<(const Time& t)
        {
            if(dog_log.is_open())
            {
                std::time_t now = std::time(nullptr);
                std::tm* local_time = std::localtime(&now);
                char buf[64];
                std::strftime(buf, sizeof(buf), "[%Y-%m-%d %H:%M:%S] : ", local_time);
                dog_log << buf;
            }
            else
            {
                std::cerr << "[Error]：未指定输出日志文件名或日志文件打开失败！" << std::endl;
            }
            return *this;
        }

        DogLog& operator<<(void(*__fp)(DogLog d))
        {
            if(dog_log.is_open())
            {
                dog_log << "\n";
                dog_log.flush();
            }
            else
            {
                std::cerr << "[Error]：未指定输出日志文件名或日志文件打开失败！" << std::endl;
            }
            return *this;
        }

    private:
        std::ofstream dog_log;
    };

    extern Time time;
    extern DogLog cout;
    void endl(DogLog d);
}

#endif //DOG_DOGLOG_H
