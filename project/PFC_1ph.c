#include "PFC_1ph.h"

POWER_MEAS_SINE_ANALYZER  AC_Analyzer;
SPLL_1PH_SOGI             SPLL_Data;
spwm                      SPWM_Mode;

System_Flag               System_State;
Mode_Switch               Contrarian_Bridge_State;

float  Internal_SineSignal;
bool   SPLL_Flag;

void Project_Init()
{
    //初始化结构体
    POWER_MEAS_SINE_ANALYZER_reset(&AC_Analyzer);
    POWER_MEAS_SINE_ANALYZER_config(&AC_Analyzer,HRTIM_IT_FRE,
                                             0,INPUT_AC_FRE+5.0f,
                                             INPUT_AC_FRE-5.0f);
    SPLL_1PH_SOGI_reset(&SPLL_Data);
    SPLL_1PH_SOGI_config(&SPLL_Data,INPUT_AC_FRE,HRTIM_IT_FRE,
                            SPLL_B0,SPLL_B1);

    SPWM_Init(&SPWM_Mode,INPUT_AC_FRE,HRTIM_IT_FRE,MasterTimer);
    
    //开启外设
    HAL_HRTIM_WaveformCounterStart_IT(&hhrtim1,HRTIM_TIMERID_MASTER);
    HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC_Sample.ADC_Raw_Value,3);

    //标志位初始化
    Contrarian_Bridge_State = OFF;

    
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
    SPLL_1PH_SOGI_run(&SPLL_Data,Acwave);
    return SPLL_Data.u_Q[0] < 0.05 ? false : true;
}

void Ac_Analyser_Run(float i, float v)
{
    AC_Analyzer.i = i;
    AC_Analyzer.v = v;
    POWER_MEAS_SINE_ANALYZER_run(&AC_Analyzer);
}

