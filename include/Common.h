#ifndef DOG_COMMON_H
#define DOG_COMMON_H

extern int stop_flag;

enum CommandType
{
    START,
    CHECK,
    STOP,
    UPLOAD
};

typedef struct Whistle
{
    long type;                  ///< 消息类型
    int unique_id_;             ///< 指令唯一标识
    CommandType command_type_;  ///< 指令类型
    char text[128];             ///< 附加消息
}Whistle;

enum TaskCompletionStatus
{
    INVALID,
    SUCCESS,
    FAILED
};

typedef struct Bark
{
    long type;                      ///< 消息类型
    int unique_id_;                 ///< 指令唯一标识
    TaskCompletionStatus status_;   ///< 任务完成状态
    int progress_num_;              ///< 进程个数
}Bark;

#endif //DOG_COMMON_H