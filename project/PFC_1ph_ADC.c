#include "PFC_1ph_ADC.h"

uint16_t AC_Offset;
Sample_Typedef ADC_Sample;

bool AC_Offset_Get()
{
    static int add_num = 0;
    static int sum_v = 0;
    bool flag;
    if(add_num < Tnum)
    {
        sum_v += ADC_Sample.ADC_Raw_Value[0];
        add_num++;
        flag =  false;
    }
    else if(add_num >= Tnum)
    {
        AC_Offset = sum_v / Tnum;
        flag = true;
    }
    return flag;
}

void ADC_Conversion()
{
    ADC_Sample.Bus_Volt    = (ADC_Sample.ADC_Raw_Value[0] + AC_Offset)*Kraw;
    ADC_Sample.Bus_Current = (ADC_Sample.ADC_Raw_Value[2]);
}
