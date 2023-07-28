#include "inc.h"
#include "PFC_1ph.h"


/*variable define*/
// spwm SPWM1;
spwm spwmmod;

/*task init*/
void Task_Init()
{
    Project_Init();
    //Contrarian_Bridge_Switch(ON);
}

/*task do*/
void Task_Do()
{
    OLED_Screen();
}

/*IT Function*/
