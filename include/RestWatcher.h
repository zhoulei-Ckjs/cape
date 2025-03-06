#ifndef DOG_RESTWATCHER_H
#define DOG_RESTWATCHER_H

#include <cpprest/uri_builder.h>
#include <cpprest/http_listener.h>
#include <string>

class RestWatcher
{
public:
    friend class WorkFlow;
    void RaiseDog();
    void SetUri(std::string uri);
    void Start();
    void Stop();
    void PostMethod(const web::http::http_request& request);
    void PutMethod(const web::http::http_request& request);

private :
    void Initialize();
    /**
     * @brief 创建消息队列
     * @return 创建状态
     * @retval 0 创建成功
     * @retval -1 创建失败
     */
    int CreateWhistle();

private :
    web::uri_builder* uri_;
    web::http::experimental::listener::http_listener *listener_;
    std::map<std::string, std::vector<int>> program_pids_;
    std::map<std::string, std::string> program_exe_path_;
};

#endif
