#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <string>

#include <cpprest/filestream.h>

#include "RestKeeper.h"
#include "WorkFlow.h"
#include "Log.h"
#include "Dog.h"
#include "Tools.h"

void RestKeeper::PostMethod(const web::http::http_request& request)
{
    auto path = request.relative_uri().path();
    auto paths = web::uri::split_path(request.relative_uri().path());

    /// 命令错误检查
    if(paths.size() != 2)
    {
        std::stringstream wss;
        wss << "未定义方法：" << path.c_str();
        request.reply(web::http::status_codes::NotImplemented, wss.str());
        cape::cout << cape::time << wss.str() << cape::endl;
        return;
    }
    std::string command = paths.front();
    std::string program = paths.back();
    if(command != "start" && command != "check" && command != "stop")
    {
        request.reply(web::http::status_codes::NotImplemented, "未知命令：" + command);
        cape::cout << cape::time << "未知命令：" << command << cape::endl;
        return;
    }
    if(program_exe_path_.find(program) == program_exe_path_.end())
    {
        request.reply(web::http::status_codes::NotImplemented, "未知程序：" + command);
        cape::cout << cape::time << "未知程序：" << command << cape::endl;
        return;
    }

    if(command == "start")
    {
        int unique_id = ++whistle_unique_id_;
        PerformTask(unique_id, CommandType::START, program, request);
    }
    else if(command == "check")
    {
        int unique_id = ++whistle_unique_id_;
        PerformTask(unique_id, CommandType::CHECK, program, request);
    }
    else if(command == "stop")
    {
        int unique_id = ++whistle_unique_id_;
        PerformTask(unique_id, CommandType::STOP, program, request);
    }
    else        ///< 不该出现，前面已经做了非 start、check、stop 判断。
    {
        request.reply(web::http::status_codes::InternalError, "内部逻辑错误");
        cape::cout << cape::time << "内部逻辑错误" << cape::endl;
    }
}

void RestKeeper::PutMethod(const web::http::http_request& request)
{
    auto path = request.relative_uri().path();
    auto paths = web::uri::split_path(request.relative_uri().path());

    if(path.find("upload") == std::string::npos || paths.size() != 2)
    {
        std::stringstream wss;
        wss << "未定义方法：" << path.c_str();
        request.reply(web::http::status_codes::NotImplemented, wss.str());
        cape::cout << cape::time << wss.str() << cape::endl;
        return;
    }

    std::string file_name = paths.back();   ///< 获取文件名字

    cape::cout << cape::time << "[Accepting file " << file_name << "]" << cape::endl;
    auto fileStream = std::make_shared<concurrency::streams::ostream>();
    /// 异步打开文件流
    concurrency::streams::fstream::open_ostream(U(file_name)).then(
            [=](const concurrency::streams::ostream& outFile)
            {
                *fileStream = outFile;

                /// 读取请求体数据并写入文件
                return request.body().read_to_end(fileStream->streambuf());
            }
    ).then(
            [=](size_t bytesRead)
            {
                cape::cout << cape::time << "成功写入 " << bytesRead << " 字节" << cape::endl;

                /// 关闭文件流
                return fileStream->close();
            }
    ).then(
            [=](const pplx::task<void>& previousTask)
            {
                try
                {
                    previousTask.get();  ///< 检查是否有异常
                    request.reply(web::http::status_codes::OK, U("文件上传成功"));
                    cape::cout << cape::time << "文件接收成功" << cape::endl;
                }
                catch (const std::exception& e)
                {
                    request.reply(web::http::status_codes::InternalError, U("文件上传失败"));
                    cape::cout << cape::time << "文件写入失败: " << e.what() << cape::endl;
                }
            }
    );
}

RestKeeper::RestKeeper()
{
    whistle_unique_id_ = 0;
}

void RestKeeper::Initialize()
{
    /// 进程 pid
    program_pids_.insert({"test", std::vector<int>()});
    program_pids_.insert({"odsp", std::vector<int>()});
    program_pids_.insert({"ret", std::vector<int>()});
    program_pids_.insert({"event_transfer", std::vector<int>()});
    program_pids_.insert({"event_repository", std::vector<int>()});
    program_pids_.insert({"rts", std::vector<int>()});
    program_pids_.insert({"wovt", std::vector<int>()});
    program_pids_.insert({"logon", std::vector<int>()});
    program_pids_.insert({"uuas", std::vector<int>()});
    program_pids_.insert({"wme", std::vector<int>()});

    /// 进程路径
    program_exe_path_.insert({"test", "/root/cape/cmake-build-debug-remote-host/test/test"});
    program_exe_path_.insert({"odsp", "/home/hongshan/ODSP/start.sh"});
    program_exe_path_.insert({"ret", "/home/hongshan/RET/start.sh"});
    program_exe_path_.insert({"event_transfer", "/home/hongshan/BEDD_TRANSFER/start.sh"});
    program_exe_path_.insert({"event_repository", "/home/hongshan/BEDD/start.sh"});
    program_exe_path_.insert({"rts", "/home/hongshan/RTS/start.sh"});
    program_exe_path_.insert({"wovt", "/home/hongshan/WOVT/start.sh"});
    program_exe_path_.insert({"logon", "/home/hongshan/LOGON/start.sh"});
    program_exe_path_.insert({"uuas", "/home/hongshan/UUAS/start.sh"});
    program_exe_path_.insert({"wme", "/home/hongshan/WME/start.sh"});
}

void RestKeeper::PerformTask(int unique_id, CommandType type, const std::string& program, const web::http::http_request& request)
{
    IssueCommand(unique_id, type, program.c_str());
    TaskCompletionStatus reply_status = TaskCompletionStatus::INVALID;
    for(int i = 0; i < 3000; i++)
    {
        reply_status = HearBarking(unique_id);
        if(reply_status != TaskCompletionStatus::INVALID)
            break;
        usleep(1000);
    }
    switch (reply_status)
    {
        case TaskCompletionStatus::INVALID:
            request.reply(web::http::status_codes::RequestTimeout, "启动超时，请检查服务器状态!");
            break;
        case TaskCompletionStatus::SUCCESS:
            request.reply(web::http::status_codes::OK, "启动成功!");
            break;
        case TaskCompletionStatus::FAILED:
            request.reply(web::http::status_codes::ExpectationFailed, "启动失败!");
            break;
        default:
            break;
    }
}

int RestKeeper::CreateWhistleAndBark()
{
    key_t key = ftok("whistle", 65);
    whistle_msg_id_ = msgget(key, 0666 | IPC_CREAT);

    if (whistle_msg_id_ == -1)
    {
        cape::cout << cape::time << "创建消息队列 whistle 失败!" << cape::endl;
        return -1;
    }

    key = ftok("bark", 66);
    bark_msg_id_ = msgget(key, 0666 | IPC_CREAT);

    if (bark_msg_id_ == -1)
    {
        cape::cout << cape::time << "创建消息队列 bark 失败!" << cape::endl;
        return -1;
    }

    return 0;
}

int RestKeeper::IssueCommand(int unique_id, CommandType command_type, const char* message) const
{
    Whistle whistle;
    whistle.type = 1;                                         ///< 设置消息类型
    whistle.command_type_ = command_type;
    whistle.unique_id_ = unique_id;                           ///< 指令唯一ID
    strcpy(whistle.text, message);                  ///< 设置消息内容

    if (msgsnd(whistle_msg_id_, &whistle, sizeof(whistle), 0) == -1)
    {
        cape::cout << cape::time << "消息发送失败!" << cape::endl;
        return -1;
    }

    cape::cout << cape::time << "[" << whistle.unique_id_ << " " <<
        cape::get_enum_name(command_type) << " " << whistle.text << "]" << cape::endl;
    return 0;
}

TaskCompletionStatus RestKeeper::HearBarking(int unique_id)
{
    std::lock_guard<std::mutex> guard(whistle_reply_map_mutex_);
    auto it = whistle_reply_map_.find(unique_id);
    if(it != whistle_reply_map_.end())
    {
        TaskCompletionStatus status = it->second.status_;
        whistle_reply_map_.erase(unique_id);
        return status;
    }
    return TaskCompletionStatus::INVALID;
}

void RestKeeper::ReceiveBark()
{
    Bark bark;
    if (msgrcv(bark_msg_id_, &bark, sizeof(bark), 1, 0) == -1)
    {
        cape::cout << cape::time << "消息队列接收失败!" << cape::endl;
    }
    else
    {
        cape::cout << cape::time << "--> [" << bark.unique_id_ << " " <<
            cape::get_enum_name(bark.status_) << "]" << cape::endl;

        std::lock_guard<std::mutex> guard(whistle_reply_map_mutex_);
        whistle_reply_map_.insert({bark.unique_id_, bark});
    }
}

void RestKeeper::RaiseDog()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        cape::cout << cape::time << "[Error]: 创建 Dog 进程失败!!!" << cape::endl;
        exit(0);
    }

    if(pid == 0)
    {
        cape::cout.Close();
        cape::cout.Open("dog.log");
        Dog::SetMaster(this);
        Dog::Run();
    }

    if(CreateWhistleAndBark() == -1)
        exit(0);
}

void RestKeeper::SetUri(std::string uri)
{
    uri_ = new web::uri_builder(U(uri));
    auto addr = uri_->to_uri();
    listener_ = new web::http::experimental::listener::http_listener(addr);
}

void RestKeeper::Start()
{
    auto post_method = std::bind(&RestKeeper::PostMethod, this, std::placeholders::_1);
    auto put_method = std::bind(&RestKeeper::PutMethod, this, std::placeholders::_1);
    listener_->support(web::http::methods::POST, post_method);
    listener_->support(web::http::methods::PUT, put_method);

    try
    {
        listener_->open().then([=](){
            std::cout << "开始监听: " << this->uri_->to_string() << std::endl;
        }).wait();
    }
    catch (const std::exception& e)
    {
        std::cerr << "错误: " << e.what() << std::endl;
    }
}

void RestKeeper::Stop()
{
    listener_->close().wait();  ///< 等待所有操作完成
}