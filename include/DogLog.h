#ifndef DOG_DOGLOG_H
#define DOG_DOGLOG_H

#include <fstream>
#include <iostream>

class DogLog
{
public:
    enum OpenStatus
    {
        OPEN_SUCCESS = 0,
        OPEN_FAILURE = 1
    };

    class Endl{};

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

    DogLog& operator<<(DogLog::Endl& e)
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

public :
    static DogLog::Endl endl;

private:
    std::ofstream dog_log;
};

#endif //DOG_DOGLOG_H
