#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>

#include "Dog.h"
#include "Log.h"
#include "Common.h"
#include "Tools.h"
#include "WorkFlow.h"

int Dog::whistle_msg_id_ = -1;
int Dog::bark_msg_id_ = -1;
RestKeeper* Dog::master_ = nullptr;

void Dog::Voice()
{
    cape::cout << "*********************************************" << cape::endl;
    cape::cout << "               dog resurrection              " << cape::endl;
    cape::cout << "*********************************************" << cape::endl;
}

void Dog::SetMaster(RestKeeper* master)
{
    master_ = master;
}

void Dog::Run()
{
    CreateWhistleAndBark();

    Whistle whistle;

    while(true)
    {
        if (msgrcv(whistle_msg_id_, &whistle, sizeof(whistle), 1, 0) == -1)
        {
            cape::cout << cape::time << "消息队列接收失败!" << cape::endl;
        }
        else
        {
            cape::cout << cape::time << "[" << whistle.unique_id_ << " " <<
                cape::get_enum_name(whistle.command_type_) << " " << whistle.text << "]" << cape::endl;

            switch(whistle.command_type_)
            {
                case CommandType::START:
                {
                    std::vector<std::string> args;
                    args.push_back(master_->program_exe_path_[whistle.text]);
                    pid_t pid_son = WorkFlow::StartProgram(args);

                    if(pid_son > 0)
                        master_->program_pids_[whistle.text].push_back(pid_son);

                    if(pid_son != -1)
                        IssueBark(whistle.unique_id_, TaskCompletionStatus::SUCCESS);
                    else
                        IssueBark(whistle.unique_id_, TaskCompletionStatus::FAILED);
                }
                    break;
                case CommandType::CHECK:
                {
                    std::vector<int> program_pids = WorkFlow::CheckProgram(whistle.text);
                    IssueBark(whistle.unique_id_, TaskCompletionStatus::SUCCESS, program_pids.size());
                }
                    break;
                case CommandType::STOP:
                {
                    StopStatus stop_status = WorkFlow::StopProgram(whistle.text, master_->program_pids_[whistle.text]);
                    if(stop_status == StopStatus::STOP_SUCCESS)
                        IssueBark(whistle.unique_id_, TaskCompletionStatus::SUCCESS);
                    else
                        IssueBark(whistle.unique_id_, TaskCompletionStatus::FAILED);
                }
                    break;
                case CommandType::UPLOAD:
                {
                    IssueBark(whistle.unique_id_, TaskCompletionStatus::FAILED);
                }
                    break;
                default:
                {
                    IssueBark(whistle.unique_id_, TaskCompletionStatus::INVALID);
                }
                    break;
            }
        }
    }

    /// 删除消息队列
    if (msgctl(whistle_msg_id_, IPC_RMID, nullptr) == -1)
    {
        cape::cout << "[Dog]: 删除消息队列失败!" << cape::endl;
    }
    cape::cout.Close();
}

void Dog::CreateWhistleAndBark()
{
    key_t key = ftok("whistle", 65);
    whistle_msg_id_ = msgget(key, 0666 | IPC_CREAT);

    if (whistle_msg_id_ == -1)
    {
        cape::cout << cape::time << "消息队列 whistle 创建失败!" << cape::endl;
        kill(-getsid(getpid()), SIGKILL);
    }

    key = ftok("bark", 66);
    bark_msg_id_ = msgget(key, 0666 | IPC_CREAT);

    if (bark_msg_id_ == -1)
    {
        cape::cout << cape::time << "创建消息队列 bark 失败!" << cape::endl;
        kill(-getsid(getpid()), SIGKILL);
    }
}

void Dog::IssueBark(int unique_id, TaskCompletionStatus status, int progress_num)
{
    Bark bark;
    bark.type = 1;                                       ///< 设置消息类型
    bark.unique_id_ = unique_id;                         ///< 指令唯一ID
    bark.status_ = status;                               ///< 设置状态
    bark.progress_num_ = progress_num;                   ///< 进程存在个数

    if (msgsnd(bark_msg_id_, &bark, sizeof(bark), 0) == -1)
    {
        cape::cout << cape::time << "消息发送失败!" << cape::endl;
    }
    else
    {
        cape::cout << cape::time << "<-- [" << bark.unique_id_ << " " <<
            cape::get_enum_name(bark.status_) << "]" << cape::endl;
    }
}