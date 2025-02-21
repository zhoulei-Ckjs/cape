#include <string>
#include <chrono>

std::string GetTime()
{
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    char buf[64];
    std::strftime(buf, sizeof(buf), "[%Y-%m-%d %H:%M:%S] : ", local_time);
    return buf;
}
