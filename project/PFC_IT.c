#include "PFC_1ph.h"


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)//adc转换完后进入中断
{    
    ADC_Conversion();
    PFC_KeyboardControll();
    switch (System_State)
    {
    case System_Init:
        if(AC_Offset_Get())
            System_State = System_Run;       
        break;
    
    case System_Run:
        AC_Lab3();
        break;

    case System_Stop:
        System_Stop_Program();
        break;
    }
    SEGGER_RTT_printf(0,"%d,%d\n",FLOAT_PRINTF(SPLL_Data.u_Q[0]),ADC_Sample.ADC_Raw_Value[0]);
}