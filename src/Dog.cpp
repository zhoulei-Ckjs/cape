#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "Dog.h"
#include "Log.h"
#include "Common.h"

int Dog::msgid = -1;

void Dog::Run()
{
    key_t key = ftok("msg_queue", 65);  // 获取相同的键
    msgid = msgget(key, 0666 | IPC_CREAT);  // 获取消息队列 ID

    if (msgid == -1)
    {
        cape::cout << cape::time << "[Dog]: 消息队列创建失败!" << cape::endl;
        kill(-getsid(getpid()), SIGKILL);
    }

    Whistle whistle;

    while(true)
    {
        if (msgrcv(msgid, &whistle, sizeof(whistle), 1, 0) == -1)
        {
            cape::cout << cape::time << "[Dog]: 消息队列接收失败!" << cape::endl;
        }
        else
        {
            cape::cout << cape::time << "[Dog]: 收到消息: {type: " << whistle.command_type_
            << ", text: " << whistle.text << "}" << cape::endl;
        }
    }

    /// 删除消息队列
    if (msgctl(msgid, IPC_RMID, nullptr) == -1)
    {
        cape::cout << "[Dog]: 删除消息队列失败!" << cape::endl;
    }
}