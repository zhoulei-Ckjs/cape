#include "RestDog.h"
#include "Common.h"
#include "WorkFlow.h"

void RestDog::PostMethod(web::http::http_request request)
{
    auto path = request.relative_uri().path();
    std::cout << path << std::endl;
    if (path == "/start/odsp")
    {
        dog::cout << dog::time << "[start odsp]" << dog::endl;
//        handle_start(request);
        request.reply(web::http::status_codes::OK, "start odsp success!");
    }
    else if(path == "/start/ret")
    {
        dog::cout << dog::time << "[start ret]" << dog::endl;
//        handle_start(request);
        request.reply(web::http::status_codes::OK, "start ret success!");
    }
    else if(path == "/start/event_transfer")
    {
        dog::cout << dog::time << "[start event_transfer]" << dog::endl;
//        handle_start(request);
        request.reply(web::http::status_codes::OK, "start event_transfer success!");
    }
    else if(path == "/start/rts")
    {
        dog::cout << dog::time << "[start rts]" << dog::endl;
//        handle_start(request);
        request.reply(web::http::status_codes::OK, "start rts success!");
    }
    else if(path == "/start/wovt")
    {
        dog::cout << dog::time << "[start wovt]" << dog::endl;
//        handle_start(request);
        request.reply(web::http::status_codes::OK, "start wovt success!");
    }
    else if(path == "/start/logon")
    {
        dog::cout << dog::time << "[start logon]" << dog::endl;
//        handle_start(request);
        request.reply(web::http::status_codes::OK, "start logon success!");
    }
    else if(path == "/start/uuas")
    {
        dog::cout << dog::time << "[start uuas]" << dog::endl;
//        handle_start(request);
        request.reply(web::http::status_codes::OK, "start uuas success!");
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

void RestDog::CreateServer()
{
    web::uri_builder uri(U("http://0.0.0.0:8888"));
    auto addr = uri.to_uri();
    static web::http::experimental::listener::http_listener listener(addr);

    listener.support(web::http::methods::POST, RestDog::PostMethod);

    try
    {
        listener.open().then([&uri](){
            std::cout << "开始监听: " << uri.to_string() << std::endl;
        }).wait();
    }
    catch (const std::exception& e)
    {
        std::cerr << "错误: " << e.what() << std::endl;
    }
}