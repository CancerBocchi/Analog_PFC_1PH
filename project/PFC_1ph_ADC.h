#ifndef __PFC_1ph_H__
#define __PFC_1ph_H__

#include "PFC_1ph.h"

#define Uref      3.0f
#define ADC_Bits  4096.0f
#define Kac       112.45f
#define Kraw      Uref/ADC_Bits

#define Tnum     400

typedef struct 
{
    uint16_t ADC_Raw_Value[4];
    float Bus_Volt;
    float Bus_Current;
}Sample_Typedef;

extern Sample_Typedef ADC_Sample;
extern uint16_t AC_Offset[2];

bool AC_Offset_Get();
void ADC_Conversion();

#endif