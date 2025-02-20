#include "RestDog.h"

void RestDog::PostMethod(web::http::http_request request)
{
    auto path = request.relative_uri().path();
    std::cout << path << std::endl;
    if (path == "/start")
    {
//        handle_start(request);
    }
    else if (path == "/stop")
    {
//        handle_stop(request);
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

    try {
        listener.open().then([&uri](){
            std::cout << "开始监听: " << uri.to_string() << std::endl;
        }).wait();
    }
    catch (const std::exception& e)
    {
        std::cerr << "错误: " << e.what() << std::endl;
    }
}