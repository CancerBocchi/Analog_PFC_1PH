#ifndef __PFC_1PH_DEFINES_H__
#define __PFC_1PH_DEFINES_H__



#define HRTIM_IT_FRE 10000.0f
#define HRTIM_IT_PER (1/HRTIM_IT_FRE)
#define INPUT_AC_FRE 50.0f
#define PowerFre_Div 20.0f
#define PowerMea_Fre (HRTIM_IT_FRE/PowerFre_Div)

#define SPLL_B0  66.76140651f
#define SPLL_B1 -66.53477549f
#define Angle_Rad 0.01745329f

#define SPLL_OK true
#define SPLL_NO false
#define RUN     true
#define STOP    false

#define Uref      3.0f
#define ADC_Bits  4096.0f
#define Kac       112.45f
#define Kraw      Uref/ADC_Bits
#define TSnum     (HRTIM_IT_FRE/INPUT_AC_FRE)

#endif //f