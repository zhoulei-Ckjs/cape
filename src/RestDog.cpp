#include <cpprest/filestream.h>

#include "RestDog.h"
#include "WorkFlow.h"
#include "DogLog.h"

void RestDog::PostMethod(const web::http::http_request& request)
{
    auto path = request.relative_uri().path();

    std::vector<std::string> args;
    char replay_buf[64];
    if(path == "/start/test")
    {
        dog::cout << dog::time << "[start test]" << dog::endl;
        args.push_back("/root/dog/cmake-build-debug/test/test");

        StartStatus status = WorkFlow::StartProgram(args);
        if(status == StartStatus::START_SUCCESS)
            request.reply(web::http::status_codes::OK, "启动成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "启动失败!");
    }
    else if(path == "/stop/test")
    {
        dog::cout << dog::time << "[stop test]" << dog::endl;

        StopStatus status = WorkFlow::StopProgram("test");
        if(status == STOP_SUCCESS)
            request.reply(web::http::status_codes::OK, "停止成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "停止失败!");
    }
    else if (path == "/start/odsp")
    {
        dog::cout << dog::time << "[start odsp]" << dog::endl;
        args.push_back("/home/hongshan/ODSP/start.sh");

        StartStatus status = WorkFlow::StartProgram(args);
        if(status == StartStatus::START_SUCCESS)
            request.reply(web::http::status_codes::OK, "启动成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "启动失败!");
    }
    else if(path == "/start/ret")
    {
        dog::cout << dog::time << "[start ret]" << dog::endl;
        args.push_back("/home/hongshan/RET/start.sh");

        StartStatus status = WorkFlow::StartProgram(args);
        if(status == StartStatus::START_SUCCESS)
            request.reply(web::http::status_codes::OK, "启动成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "启动失败!");
    }
    else if(path == "/start/event_transfer")
    {
        dog::cout << dog::time << "[start event_transfer]" << dog::endl;
        args.push_back("/home/hongshan/BEDD_TRANSFER/start.sh");

        StartStatus status = WorkFlow::StartProgram(args);
        if(status == StartStatus::START_SUCCESS)
            request.reply(web::http::status_codes::OK, "启动成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "启动失败!");
    }
    else if(path == "/start/event_repository")
    {
        dog::cout << dog::time << "[start event_repository]" << dog::endl;
        args.push_back("/home/hongshan/BEDD/start.sh");

        StartStatus status = WorkFlow::StartProgram(args);
        if(status == StartStatus::START_SUCCESS)
            request.reply(web::http::status_codes::OK, "启动成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "启动失败!");
    }
    else if(path == "/start/rts")
    {
        dog::cout << dog::time << "[start rts]" << dog::endl;
        args.push_back("/home/hongshan/RTS/start.sh");

        StartStatus status = WorkFlow::StartProgram(args);
        if(status == StartStatus::START_SUCCESS)
            request.reply(web::http::status_codes::OK, "启动成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "启动失败!");
    }
    else if(path == "/start/wovt")
    {
        dog::cout << dog::time << "[start wovt]" << dog::endl;
        args.push_back("/home/hongshan/WOVT/start.sh");

        StartStatus status = WorkFlow::StartProgram(args);
        if(status == StartStatus::START_SUCCESS)
            request.reply(web::http::status_codes::OK, "启动成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "启动失败!");
    }
    else if(path == "/start/logon")
    {
        dog::cout << dog::time << "[start logon]" << dog::endl;
        args.push_back("/home/hongshan/LOGON/start.sh");

        StartStatus status = WorkFlow::StartProgram(args);
        if(status == StartStatus::START_SUCCESS)
            request.reply(web::http::status_codes::OK, "启动成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "启动失败!");
    }
    else if(path == "/start/uuas")
    {
        dog::cout << dog::time << "[start uuas]" << dog::endl;
        args.push_back("/home/hongshan/UUAS/start.sh");

        StartStatus status = WorkFlow::StartProgram(args);
        if(status == StartStatus::START_SUCCESS)
            request.reply(web::http::status_codes::OK, "启动成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "启动失败!");
    }
    else if (path == "/stop/odsp")
    {
        dog::cout << dog::time << "[stop odsp]" << dog::endl;

        StopStatus status = WorkFlow::StopProgram("odsp");
        if(status == STOP_SUCCESS)
            request.reply(web::http::status_codes::OK, "停止成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "停止失败!");
    }
    else if(path == "/stop/ret")
    {
        dog::cout << dog::time << "[stop ret]" << dog::endl;

        StopStatus status = WorkFlow::StopProgram("ret");
        if(status == STOP_SUCCESS)
            request.reply(web::http::status_codes::OK, "停止成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "停止失败!");
    }
    else if(path == "/stop/event_transfer")
    {
        dog::cout << dog::time << "[stop event_transfer]" << dog::endl;

        StopStatus status = WorkFlow::StopProgram("event_transfer");
        if(status == STOP_SUCCESS)
            request.reply(web::http::status_codes::OK, "停止成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "停止失败!");
    }
    else if(path == "/stop/event_repository")
    {
        dog::cout << dog::time << "[stop event_repository]" << dog::endl;

        StopStatus status = WorkFlow::StopProgram("event_repository");
        if(status == STOP_SUCCESS)
            request.reply(web::http::status_codes::OK, "停止成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "停止失败!");
    }
    else if(path == "/stop/rts")
    {
        dog::cout << dog::time << "[stop rts]" << dog::endl;

        StopStatus status = WorkFlow::StopProgram("rts");
        if(status == STOP_SUCCESS)
            request.reply(web::http::status_codes::OK, "停止成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "停止失败!");
    }
    else if(path == "/stop/wovt")
    {
        dog::cout << dog::time << "[stop wovt]" << dog::endl;

        StopStatus status = WorkFlow::StopProgram("wovt");
        if(status == STOP_SUCCESS)
            request.reply(web::http::status_codes::OK, "停止成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "停止失败!");
    }
    else if(path == "/stop/logon")
    {
        dog::cout << dog::time << "[stop logon]" << dog::endl;

        StopStatus status = WorkFlow::StopProgram("logon");
        if(status == STOP_SUCCESS)
            request.reply(web::http::status_codes::OK, "停止成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "停止失败!");
    }
    else if(path == "/stop/uuas")
    {
        dog::cout << dog::time << "[stop uuas]" << dog::endl;

        StopStatus status = WorkFlow::StopProgram("uuas");
        if(status == STOP_SUCCESS)
            request.reply(web::http::status_codes::OK, "停止成功!");
        else
            request.reply(web::http::status_codes::ExpectationFailed, "停止失败!");
    }
    else if (path == "/check/odsp")
    {
        dog::cout << dog::time << "[check odsp]" << dog::endl;

        std::vector<int> processes = WorkFlow::CheckProgram("odsp");

        if(processes.empty())
            snprintf(replay_buf, sizeof replay_buf, "[%s]未运行！", "odsp");
        else
            snprintf(replay_buf, sizeof replay_buf, "当前[%s]正在运行，且存在 %ld 个实例！", "odsp", processes.size());
        request.reply(web::http::status_codes::OK, replay_buf);
    }
    else if(path == "/check/ret")
    {
        dog::cout << dog::time << "[check ret]" << dog::endl;

        std::vector<int> processes = WorkFlow::CheckProgram("ret");

        if(processes.empty())
            snprintf(replay_buf, sizeof replay_buf, "[%s]未运行！", "ret");
        else
            snprintf(replay_buf, sizeof replay_buf, "当前[%s]正在运行，且存在 %ld 个实例！", "ret", processes.size());
        request.reply(web::http::status_codes::OK, replay_buf);
    }
    else if(path == "/check/event_transfer")
    {
        dog::cout << dog::time << "[check event_transfer]" << dog::endl;

        std::vector<int> processes = WorkFlow::CheckProgram("event_transfer");

        if(processes.empty())
            snprintf(replay_buf, sizeof replay_buf, "[%s]未运行！", "event_transfer");
        else
            snprintf(replay_buf, sizeof replay_buf, "当前[%s]正在运行，且存在 %ld 个实例！", "event_transfer", processes.size());
        request.reply(web::http::status_codes::OK, replay_buf);
    }
    else if(path == "/check/event_repository")
    {
        dog::cout << dog::time << "[check event_repository]" << dog::endl;

        std::vector<int> processes = WorkFlow::CheckProgram("event_repository");

        if(processes.empty())
            snprintf(replay_buf, sizeof replay_buf, "[%s]未运行！", "event_repository");
        else
            snprintf(replay_buf, sizeof replay_buf, "当前[%s]正在运行，且存在 %ld 个实例！", "event_repository", processes.size());
        request.reply(web::http::status_codes::OK, replay_buf);
    }
    else if(path == "/check/rts")
    {
        dog::cout << dog::time << "[check rts]" << dog::endl;

        std::vector<int> processes = WorkFlow::CheckProgram("rts");

        if(processes.empty())
            snprintf(replay_buf, sizeof replay_buf, "[%s]未运行！", "rts");
        else
            snprintf(replay_buf, sizeof replay_buf, "当前[%s]正在运行，且存在 %ld 个实例！", "rts", processes.size());
        request.reply(web::http::status_codes::OK, replay_buf);
    }
    else if(path == "/check/wovt")
    {
        dog::cout << dog::time << "[check wovt]" << dog::endl;

        std::vector<int> processes = WorkFlow::CheckProgram("wovt");

        if(processes.empty())
            snprintf(replay_buf, sizeof replay_buf, "[%s]未运行！", "wovt");
        else
            snprintf(replay_buf, sizeof replay_buf, "当前[%s]正在运行，且存在 %ld 个实例！", "wovt", processes.size());
        request.reply(web::http::status_codes::OK, replay_buf);
    }
    else if(path == "/check/logon")
    {
        dog::cout << dog::time << "[check logon]" << dog::endl;

        std::vector<int> processes = WorkFlow::CheckProgram("logon");

        if(processes.empty())
            snprintf(replay_buf, sizeof replay_buf, "[%s]未运行！", "logon");
        else
            snprintf(replay_buf, sizeof replay_buf, "当前[%s]正在运行，且存在 %ld 个实例！", "logon", processes.size());
        request.reply(web::http::status_codes::OK, replay_buf);
    }
    else if(path == "/check/uuas")
    {
        dog::cout << dog::time << "[check uuas]" << dog::endl;

        std::vector<int> processes = WorkFlow::CheckProgram("uuas");

        if(processes.empty())
            snprintf(replay_buf, sizeof replay_buf, "[%s]未运行！", "uuas");
        else
            snprintf(replay_buf, sizeof replay_buf, "当前[%s]正在运行，且存在 %ld 个实例！", "uuas", processes.size());
        request.reply(web::http::status_codes::OK, replay_buf);
    }
    else if(path == "/upload")
    {
        dog::cout << dog::time << "[upload accepted!]" << dog::endl;
//        handle_stop(request);
        request.reply(web::http::status_codes::OK, "upload success!");
    }
    else
    {
        request.reply(web::http::status_codes::NotFound, "未知指令：" + path);
        dog::cout << dog::time << "未知指令：" << path << dog::endl;
    }
}

void RestDog::PutMethod(const web::http::http_request& request)
{
    auto path = request.relative_uri().path();

    if(path.find("upload") == std::string::npos)
    {
        std::stringstream wss;
        wss << "未定义方法：" << path.c_str();
        request.reply(web::http::status_codes::NotImplemented, wss.str());
        dog::cout << dog::time << wss.str() << dog::endl;
        return;
    }

    dog::cout << dog::time << "[upload file]" << dog::endl;
    auto fileStream = std::make_shared<concurrency::streams::ostream>();
    /// 异步打开文件流
    concurrency::streams::fstream::open_ostream(U("666.zip")).then(
            [=](const concurrency::streams::ostream& outFile)
            {
                *fileStream = outFile;

                /// 读取请求体数据并写入文件
                return request.body().read_to_end(fileStream->streambuf());
            }
    ).then(
            [=](size_t bytesRead)
            {
                dog::cout << dog::time << "成功写入 " << bytesRead << " 字节" << dog::endl;

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
                    dog::cout << dog::time << "文件上传成功" << dog::endl;
                }
                catch (const std::exception& e)
                {
                    request.reply(web::http::status_codes::InternalError, U("文件写入失败"));
                    dog::cout << dog::time << "文件写入失败: " << e.what() << dog::endl;
                }
            }
    );
}

void RestDog::SetUri(std::string uri)
{
    uri_ = new web::uri_builder(U(uri));
    auto addr = uri_->to_uri();
    listener_ = new web::http::experimental::listener::http_listener(addr);
}

void RestDog::Start()
{
    listener_->support(web::http::methods::POST, PostMethod);
    listener_->support(web::http::methods::PUT, PutMethod);

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

void RestDog::Stop()
{
    listener_->close().wait();  ///< 等待所有操作完成
}