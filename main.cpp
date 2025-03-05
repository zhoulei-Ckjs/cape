#include "WorkFlow.h"
#include "RestWatcher.h"
#include "DogLog.h"
#include "Common.h"

void StartDog()
{
    dog::cout << dog::endl;
    dog::cout << "*********************************************" << dog::endl;
    dog::cout << "               Mad Dog Started               " << dog::endl;
    dog::cout << "*********************************************" << dog::endl;
}

int main()
{
    dog::cout.Open("dog.log");
    StartDog();

    RestWatcher rest_watcher;
    rest_watcher.SetUri("http://0.0.0.0:8888");
    rest_watcher.Start();

    while(!stop_flag)
    {
        sleep(1);
    }

    rest_watcher.Stop();
    dog::cout << "over main" << dog::endl;

    return 0;
}
