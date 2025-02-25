#include "RestDog.h"
#include "Common.h"

void RestDog::PostMethod(web::http::http_request request)
{
    auto path = request.relative_uri().path();
    std::cout << path << std::endl;
    if (path == "/start")
    {
        dog::cout << dog::time << "[start]" << dog::endl;
//        handle_start(request);
        request.reply(web::http::status_codes::OK, "start");
    }
    else if (path == "/stop")
    {
        dog::cout << dog::time << "[stop]" << dog::endl;
//        handle_stop(request);
        request.reply(web::http::status_codes::OK, "stop");
    }
    else
    {
        request.reply(web::http::status_codes::NotFound, "Not Found");
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