#include "WorkFlow.h"
#include "RestKeeper.h"
#include "Log.h"
#include "Common.h"

void Voice()
{
    cape::cout << cape::endl;
    cape::cout << "*********************************************" << cape::endl;
    cape::cout << "             keeper start working            " << cape::endl;
    cape::cout << "*********************************************" << cape::endl;
}

int main(int argc, char* argv[])
{
    cape::cout.Open("keeper.log");
    Voice();

    RestKeeper rest_keeper;
    rest_keeper.Initialize();
    rest_keeper.RaiseDog();
    rest_keeper.SetUri("http://0.0.0.0:8888");
    rest_keeper.Start();

    while(!stop_flag)
    {
        rest_keeper.ReceiveBark();
    }

    rest_keeper.Stop();
    cape::cout << "over main" << cape::endl;
    cape::cout.Close();

    return 0;
}
