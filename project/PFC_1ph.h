#ifndef __PFC_1PH_H__
#define __PFC_1PH_H__

#include "inc.h"
#include "PFC_1ph_Defines.h"
#include "PFC_1ph_ADC.h"

typedef enum
{
    System_Init = 0x00,
    System_Run  = 0x01,
}System_Flag;

typedef enum
{
    OFF = 0x00,
    ON  = 0x01,
}Mode_Switch;

extern POWER_MEAS_SINE_ANALYZER  AC_Analyzer;
extern SPLL_1PH_SOGI             SPLL_Data;
extern spwm                      SPWM_Mode;

extern System_Flag               System_State;
extern Mode_Switch               Contrarian_Bridge_State;

extern float  Internal_SineSignal;
extern bool   SPLL_Flag;
extern spwm   spwmmod;

void Project_Init();
bool Spll_Run(float Acwave);
void InternalACGenerater();
void Contrarian_Bridge_Switch(bool OnOff);
void Ac_Analyser_Run(float i, float v);
void AC_Lab1();
void AC_Lab2();

#endif