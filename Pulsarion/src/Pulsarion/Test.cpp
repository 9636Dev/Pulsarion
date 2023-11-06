#include "Pulsarionpch.h"
#include "Test.h"

int Test::Run()
{
    Pulsarion::Log::Init();
    PLS_LOG_INFO("Hello! Welcome to Pulsarion!");
    return 1;
}
