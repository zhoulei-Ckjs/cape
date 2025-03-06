#include <cpprest/filestream.h>

#include "RestWatcher.h"
#include "WorkFlow.h"
#include "Log.h"
#include "Dog.h"

void RestWatcher::PostMethod(const web::http::http_request& request)
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
    cape::cout << cape::time << "[" << command << " " << program << "]" << cape::endl;
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

    std::vector<std::string> args;
    char replay_buf[64];
    if(command == "start")
    {
        args.push_back(program_exe_path_[program]);
        pid_t pid_son = WorkFlow::StartProgram(args);
        program_pids_[program].push_back(pid_son);

        if(pid_son != -1)
            request.reply(web::http::status_codes::OK, "启动成功!");
        else
            request.reply(web::http::status_codes::InternalError, "启动失败!");
    }
    else if(command == "check")
    {
        std::vector<int> processes = WorkFlow::CheckProgram(program);
        if(processes.empty())
            snprintf(replay_buf, sizeof replay_buf, "[%s]未运行！", "logon");
        else
            snprintf(replay_buf, sizeof replay_buf, "当前[%s]正在运行，且存在 %ld 个实例！", "logon", processes.size());
        request.reply(web::http::status_codes::OK, replay_buf);
    }
    else if(command == "stop")
    {
        StopStatus status = WorkFlow::StopProgram(program, program_pids_[program]);
        if(status == STOP_SUCCESS)
            request.reply(web::http::status_codes::OK, "停止成功!");
        else
            request.reply(web::http::status_codes::InternalError, "停止失败!");
    }
    else        ///< 不该出现，前面已经做了非 start、check、stop 判断。
    {
        request.reply(web::http::status_codes::InternalError, "内部逻辑错误");
        cape::cout << cape::time << "内部逻辑错误" << cape::endl;
    }
}

void RestWatcher::PutMethod(const web::http::http_request& request)
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

void RestWatcher::Initialize()
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

    /// 进程路径
    program_exe_path_.insert({"test", "/root/cape/cmake-build-debug/test/test"});
    program_exe_path_.insert({"odsp", "/home/hongshan/ODSP/start.sh"});
    program_exe_path_.insert({"ret", "/home/hongshan/RET/start.sh"});
    program_exe_path_.insert({"event_transfer", "/home/hongshan/BEDD_TRANSFER/start.sh"});
    program_exe_path_.insert({"event_repository", "/home/hongshan/BEDD/start.sh"});
    program_exe_path_.insert({"rts", "/home/hongshan/RTS/start.sh"});
    program_exe_path_.insert({"wovt", "/home/hongshan/WOVT/start.sh"});
    program_exe_path_.insert({"logon", "/home/hongshan/LOGON/start.sh"});
    program_exe_path_.insert({"uuas", "/home/hongshan/UUAS/start.sh"});
}

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

int RestWatcher::CreateWhistle()
{
    key_t key = ftok("whistle", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        cape::cout << cape::time << "创建消息队列失败!" << cape::endl;
        return -1;
    }

    struct Whistle whistle;
    whistle.type = 1;  // 设置消息类型
    strcpy(whistle.text, "Hello from sender!");  // 设置消息内容

    if (msgsnd(msgid, &whistle, sizeof(whistle), 0) == -1) {
        cape::cout << cape::time << "[watcher]: 消息发送失败!" << cape::endl;
        return -1;
    }

    cape::cout << cape::time << "[watcher]: 发送消息: " << whistle.text << cape::endl;
    return 0;
}

void RestWatcher::RaiseDog()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        cape::cout << cape::time << "[Error]: 创建 Dog 进程失败!!!" << cape::endl;
        exit(0);
    }

    if(pid == 0)
    {
        Dog::Run();
    }

    CreateWhistle();
}

void RestWatcher::SetUri(std::string uri)
{
    uri_ = new web::uri_builder(U(uri));
    auto addr = uri_->to_uri();
    listener_ = new web::http::experimental::listener::http_listener(addr);
}

void RestWatcher::Start()
{
    Initialize();

    auto post_method = std::bind(&RestWatcher::PostMethod, this, std::placeholders::_1);
    auto put_method = std::bind(&RestWatcher::PutMethod, this, std::placeholders::_1);
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

void RestWatcher::Stop()
{
    listener_->close().wait();  ///< 等待所有操作完成
}