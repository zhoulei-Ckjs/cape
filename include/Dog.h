#ifndef DOG_DOG_H
#define DOG_DOG_H

#include "Common.h"

class Dog
{
public :
    static void Run();

private :
    static void CreateWhistleAndBark();
    static void IssueBark(int unique_id, TaskCompletionStatus status);

public :
    static int whistle_msg_id_;
    static int bark_msg_id_;
};

#endif //DOG_DOG_H
