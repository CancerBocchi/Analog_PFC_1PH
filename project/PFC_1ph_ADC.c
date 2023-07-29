#include "PFC_1ph_ADC.h"

uint16_t AC_Offset[2];
Sample_Typedef ADC_Sample;

bool AC_Offset_Get()
{
    static int add_num = 0;
    static int sum_v[2] = {0,0};
    bool flag = false;
    if(add_num < TSnum*6)
    {
        sum_v[0] += ADC_Sample.ADC_Raw_Value[0];
        sum_v[1] += ADC_Sample.ADC_Raw_Value[1];
        add_num++;
        flag =  false;
    }
    else if(add_num >= TSnum*6)
    {
        AC_Offset[0] = sum_v[0] / TSnum/6;
        AC_Offset[1] = sum_v[1] / TSnum/6;
        flag = true;
        add_num = 0;
    }
    return flag;
}

void ADC_Conversion()
{
    //TogglePin_C13;
    ADC_Sample.Bus_Volt    = (ADC_Sample.ADC_Raw_Value[0] - AC_Offset[0])*Kraw*Kac;
    ADC_Sample.Bus_Current = (ADC_Sample.ADC_Raw_Value[1] - AC_Offset[1])*Kraw*Kac;
    
    //TogglePin_C13;
}
