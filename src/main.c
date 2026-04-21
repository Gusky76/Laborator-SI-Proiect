#include "servocontrol.h"

int main(void)
{
    ServoControl_Init();

    while (1)
    {
        ServoControl_Update();  
    }
}