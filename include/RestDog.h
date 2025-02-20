#ifndef DOG_RESTDOG_H
#define DOG_RESTDOG_H

#include <cpprest/uri_builder.h>
#include <cpprest/http_listener.h>

class RestDog
{
public:
    void CreateServer();

private:
    static void PostMethod(web::http::http_request request);
};

#endif //DOG_RESTDOG_H
