#ifndef DOG_DOG_H
#define DOG_DOG_H

class Dog
{
public :
    static void Run();

private :
    static void CreateWhistleAndBark();

public :
    static int whistle_msg_id_;
    static int bark_msg_id_;
};

#endif //DOG_DOG_H
