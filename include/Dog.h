#ifndef DOG_DOG_H
#define DOG_DOG_H

typedef struct Whistle
{
    long type;          // 消息类型
    char text[100];     // 消息内容
}Whistle;

class Dog
{
public :
    static void Run();
};

#endif //DOG_DOG_H
