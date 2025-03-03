#ifndef DOG_RESTDOG_H
#define DOG_RESTDOG_H

#include <cpprest/uri_builder.h>
#include <cpprest/http_listener.h>
#include <string>

class RestDog
{
public:
    friend class WorkFlow;
    void SetUri(std::string uri);
    void Start();
    void Stop();
    static void PostMethod(const web::http::http_request& request);
    static void PutMethod(const web::http::http_request& request);

private :
    web::uri_builder* uri_;
    web::http::experimental::listener::http_listener *listener_;
};

#endif //DOG_RESTDOG_H
