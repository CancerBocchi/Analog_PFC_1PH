#include "PFC_1ph.h"

void PFC_KeyboardControll()
{
    static int KeyBoard_Tick = 0;
    static int KeyBoard_Num = 0;
    KeyBoard_Num = keyboard_scan();
    if(KeyBoard_Num)
    {
        if(__HAL_TIM_GetCounter(&htim1) - KeyBoard_Tick >= 2000)
        {
            switch(KeyBoard_Num)
            {
                case 1:
                    if(PF_angle < 90)
                        PF_angle += 1;
                    break;
                case 2:
                    if(PF_angle < 90)
                        PF_angle -= 1;
                    break;
                case 3:

                    break;
                case 4:

                    break;
                case 5:

                    break;
                case 6:

                    break;
                case 7:

                    break;
                case 8:

                    break;
                case 9:

                    break;
                case 10:

                    break;
                case 11:

                    break;
                case 12:

                    break;
                case 13:

                    break;
                case 14:

                    break;
                case 15:

                    break;
                case 16:

                    break;
            }
            KeyBoard_Tick = __HAL_TIM_GetCounter(&htim1);
            KeyBoard_Num = 0;
        }
    }
}

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

void AC_Lab3()
{
    static int power_mea_flag;
    PFC_KeyboardControll();
    //
    //open the high bridge
    //
    Contrarian_Bridge_Switch(ON);
    //
    //确认是否锁相成功
    //
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

    //
    //锁相成功后开启spwm并且开始测量各个参数
    //
    PF_theta = PF_angle * Angle_Rad;
    if(SPLL_Flag == SPLL_OK)
    {
        Pessitive_SPWM(&SPWM_Mode,(SPLL_Data.theta + PF_theta));
        if(power_mea_flag == PowerFre_Div)
        {
            Ac_Analyser_Run(ADC_Sample.Bus_Current,ADC_Sample.Bus_Volt);
            power_mea_flag = 0;
        }
        power_mea_flag++;
    }
}