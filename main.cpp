#include "WorkFlow.h"
#include "RestWatcher.h"
#include "Log.h"
#include "Common.h"

void StartCape()
{
    cape::cout << cape::endl;
    cape::cout << "*********************************************" << cape::endl;
    cape::cout << "            watcher start working            " << cape::endl;
    cape::cout << "*********************************************" << cape::endl;
}

int main()
{
    cape::cout.Open("cape.log");
    StartCape();

    RestWatcher rest_watcher;
    rest_watcher.Initialize();
//    rest_watcher.RaiseDog();
    rest_watcher.SetUri("http://0.0.0.0:8888");
    rest_watcher.Start();

    while(!stop_flag)
    {
        sleep(1);
    }

    rest_watcher.Stop();
    cape::cout << "over main" << cape::endl;

    return 0;
}
