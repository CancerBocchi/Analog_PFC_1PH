#include "PFC_1ph.h"

void HAL_HRTIM_RegistersUpdateCallback(HRTIM_HandleTypeDef * hhrtim,uint32_t TimerIdx)//周期回调
{
    switch (System_State)
    {
    case System_Init:
        if(AC_Offset_Get())
            System_State = System_Run;       
        break;
    
    case System_Run:
        
        break;
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)//adc转换完后进入中断
{
    ADC_Conversion();
}