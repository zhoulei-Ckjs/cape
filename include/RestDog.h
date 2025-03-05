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
    void PostMethod(const web::http::http_request& request);
    void PutMethod(const web::http::http_request& request);

private :
    void Initialize();

private :
    web::uri_builder* uri_;
    web::http::experimental::listener::http_listener *listener_;
    std::map<std::string, std::vector<int>> program_pids_;
    std::map<std::string, std::string> program_exe_path_;
};

#endif //DOG_RESTDOG_H
