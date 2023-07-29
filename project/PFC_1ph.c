#include "PFC_1ph.h"

POWER_MEAS_SINE_ANALYZER  AC_Analyzer;
SPLL_1PH_SOGI             SPLL_Data;
spwm                      SPWM_Mode;

System_Flag               System_State;
Mode_Switch               Contrarian_Bridge_State;
bool                      First_Run_Flag;

uint16_t  PF_angle;
bool      SPLL_Flag;
float     Internal_SineSignal;
float     PF_theta;
float     Past_Volt;//用于过零比较



void Project_Init()
{
    //初始化结构体
    POWER_MEAS_SINE_ANALYZER_reset(&AC_Analyzer);
    POWER_MEAS_SINE_ANALYZER_config(&AC_Analyzer,PowerMea_Fre,
                                             0,INPUT_AC_FRE+5.0f,
                                             INPUT_AC_FRE-5.0f);
    SPLL_1PH_SOGI_reset(&SPLL_Data);
    SPLL_1PH_SOGI_config(&SPLL_Data,INPUT_AC_FRE,HRTIM_IT_FRE,
                            SPLL_B0,SPLL_B1);

    SPWM_Init(&SPWM_Mode,INPUT_AC_FRE,HRTIM_IT_FRE,MasterTimer);
    OLED_Init();
    
    //开启外设
    HAL_HRTIM_WaveformCounterStart(&hhrtim1,HRTIM_TIMERID_TIMER_A);
    HAL_HRTIM_WaveformCounterStart(&hhrtim1,HRTIM_TIMERID_TIMER_B);
    HAL_HRTIM_WaveformCounterStart(&hhrtim1,HRTIM_TIMERID_MASTER);
    HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC_Sample.ADC_Raw_Value,3);
    HAL_TIM_Base_Start(&htim1);

    //标志位初始化
    Contrarian_Bridge_State = OFF;
    System_State = System_Stop;
    SPLL_Flag = SPLL_NO;
    First_Run_Flag = RUN;
}

void InternalACGenerater()
{
    static float step = 2.0f * PI * INPUT_AC_FRE/HRTIM_IT_FRE;
    static float theta = 0.0f;
    if(theta >= 2*PI)
        theta -= 2*PI;
    theta += step;
    Internal_SineSignal = sinf(theta);
    
}

bool Spll_Run(float Acwave)
{
    bool result;
    SPLL_1PH_SOGI_run(&SPLL_Data,Acwave);
    result = SPLL_Data.u_Q[0] < 0.05 ? true : false;
    return result;
}

void Ac_Analyser_Run(float i, float v)
{
    AC_Analyzer.i = i;
    AC_Analyzer.v = v;
    POWER_MEAS_SINE_ANALYZER_run(&AC_Analyzer);
}

void System_Stop_Program()
{
    Contrarian_Bridge_Switch(OFF);
    System_State = System_Stop;
    SPLL_Flag = SPLL_NO;
    First_Run_Flag = STOP;
}
