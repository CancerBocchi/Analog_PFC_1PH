#include "PFC_1ph.h"

void AC_Lab1()
{
    InternalACGenerater();
    if(Spll_Run(Internal_SineSignal))
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
    else
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
}

void AC_Lab2()
{
    static int power_mea_flag;

    Contrarian_Bridge_Switch(ON);

    if(Spll_Run(ADC_Sample.Bus_Volt))
    {
        SPLL_Flag = SPLL_OK;
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
    }
    else
    {
        SPLL_Flag = SPLL_NO;
        HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);
    }

    SEGGER_RTT_printf(0,"%d\n",FLOAT_PRINTF(ADC_Sample.Bus_Current));

    if(SPLL_Flag == SPLL_OK)
    {
        Pessitive_SPWM(&SPWM_Mode,SPLL_Data.theta);
        power_mea_flag++;
        if(power_mea_flag == PowerFre_Div)
        {
            Ac_Analyser_Run(ADC_Sample.Bus_Current,ADC_Sample.Bus_Volt);
            power_mea_flag = 0;
        }
        
    }
}