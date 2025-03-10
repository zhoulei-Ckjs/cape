#ifndef DOG_DOG_H
#define DOG_DOG_H

#include "Common.h"
#include "RestKeeper.h"

class Dog
{
public :
    static void Voice();
    static void SetMaster(RestKeeper* master);
    static void Run();

private :
    static void CreateWhistleAndBark();
    static void IssueBark(int unique_id, TaskCompletionStatus status, int progress_num = -1);

public :
    static int whistle_msg_id_;
    static int bark_msg_id_;
    static RestKeeper* master_;
};

#endif //DOG_DOG_H
