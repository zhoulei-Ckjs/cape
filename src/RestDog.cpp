#include "RestDog.h"
#include "WorkFlow.h"
#include "DogLog.h"
#include "Common.h"

void RestDog::PostMethod(web::http::http_request request)
{
    auto path = request.relative_uri().path();
    std::cout << path << std::endl;

    std::vector<std::string> args;
    if (path == "/start/odsp")
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
//        handle_stop(request);
        request.reply(web::http::status_codes::OK, "stop odsp success!");
    }
    else if(path == "/stop/ret")
    {
        dog::cout << dog::time << "[stop]" << dog::endl;
//        handle_stop(request);
        request.reply(web::http::status_codes::OK, "stop odsp success!");
    }
    else if(path == "/stop/event_transfer")
    {
        dog::cout << dog::time << "[stop]" << dog::endl;
//        handle_stop(request);
        request.reply(web::http::status_codes::OK, "stop odsp success!");
    }
    else if(path == "/stop/rts")
    {
        dog::cout << dog::time << "[stop]" << dog::endl;
//        handle_stop(request);
        request.reply(web::http::status_codes::OK, "stop odsp success!");
    }
    else if(path == "/stop/wovt")
    {
        dog::cout << dog::time << "[stop]" << dog::endl;
//        handle_stop(request);
        request.reply(web::http::status_codes::OK, "stop odsp success!");
    }
    else if(path == "/stop/logon")
    {
        dog::cout << dog::time << "[stop]" << dog::endl;
//        handle_stop(request);
        request.reply(web::http::status_codes::OK, "stop odsp success!");
    }
    else if(path == "/stop/uuas")
    {
        dog::cout << dog::time << "[stop]" << dog::endl;
//        handle_stop(request);
        request.reply(web::http::status_codes::OK, "stop odsp success!");
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

void RestDog::SetUri(std::string uri)
{
    uri_ = new web::uri_builder(U(uri));
    auto addr = uri_->to_uri();
    listener_ = new web::http::experimental::listener::http_listener(addr);
}

void RestDog::Start()
{
    listener_->support(web::http::methods::POST, PostMethod);
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