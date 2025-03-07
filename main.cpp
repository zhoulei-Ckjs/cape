#include "WorkFlow.h"
#include "RestKeeper.h"
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

    RestKeeper rest_keeper;
    rest_keeper.Initialize();
    rest_keeper.RaiseDog();
    rest_keeper.SetUri("http://0.0.0.0:8888");
    rest_keeper.Start();

    while(!stop_flag)
    {
        sleep(1);
    }

    rest_keeper.Stop();
    cape::cout << "over main" << cape::endl;
    cape::cout.Close();

    return 0;
}
