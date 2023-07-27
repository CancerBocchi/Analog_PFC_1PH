#include "inc.h"
#include "PFC_1ph.h"


/*variable define*/
// spwm SPWM1;
spwm spwmmod;

/*task init*/
void Task_Init()
{
//    Project_Init();
    SPWM_Init(&spwmmod,50,20000,MasterTimer);
    HAL_HRTIM_WaveformCountStart_IT(&hhrtim1,HRTIM_TIMERID_MASTER);
    HAL_HRTIM_WaveformCountStart(&hhrtim1,HRTIM_TIMERID_TIMER_A);
    HAL_HRTIM_WaveformCountStart(&hhrtim1,HRTIM_TIMERID_TIMER_B);
    HAL_HRTIM_WaveformOutputStart(&hhrtim1,HRTIM_OUTPUT_TA1);
    //Contrarian_Bridge_Switch(ON);
}

/*task do*/
void Task_Do()
{
    
}

/*IT Function*/
