#ifndef DOG_RESTKEEPER_H
#define DOG_RESTKEEPER_H

#include <cpprest/uri_builder.h>
#include <cpprest/http_listener.h>
#include <string>
#include <atomic>

#include "Common.h"

class RestKeeper
{
public:
    friend class WorkFlow;
    RestKeeper();
    void Initialize();
    void RaiseDog();
    void SetUri(std::string uri);
    void Start();
    void Stop();
    void PostMethod(const web::http::http_request& request);
    void PutMethod(const web::http::http_request& request);

    /**
     * @brief 收取任务完成状态
     */
    void ReceiveBark();

private :

    /**
     * @brief 创建消息队列
     * @return 创建状态
     * @retval 0 创建成功
     * @retval -1 创建失败
     */
    int CreateWhistleAndBark();

    /**
     * @brief 发送命令给 Dog
     * @param command_type 命令类型
     * @param message 命令额外信息
     * @return 发送状态
     * @retval -1 发送失败
     * @retval 0 发送成功
     */
    int IssueCommand(CommandType command_type, const char* message);

public :
    std::atomic<int> whistle_unique_id_;

private :
    web::uri_builder* uri_;
    web::http::experimental::listener::http_listener *listener_;
    std::map<std::string, std::vector<int>> program_pids_;
    std::map<std::string, std::string> program_exe_path_;
    int whistle_msg_id_ = -1;                   ///< 消息发送队列 id
    int bark_msg_id_ = -1;                      ///< 消息回复队列 id

    std::map<int, Bark> whistle_reply_map_;     ///< 存放 whistle 回复消息的 map
    std::mutex whistle_reply_map_mutex_;
};

#endif
