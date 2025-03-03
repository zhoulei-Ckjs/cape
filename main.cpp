#include <fstream>

#include "WorkFlow.h"
#include "RestDog.h"
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

    RestDog rest_dog;
    rest_dog.SetUri("http://0.0.0.0:8888");
    rest_dog.Start();

    while(!stop_flag)
    {
        sleep(1);
    }

    rest_dog.Stop();
    dog::cout << "over main" << dog::endl;

    return 0;
}
