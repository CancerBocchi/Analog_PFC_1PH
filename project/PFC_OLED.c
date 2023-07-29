#include "PFC_1ph.h"

void PFC_OLEDUI_Design()
{
    DrawRoundRect(4,2,124,60,10);
    DrawLine(4,32,128,32);
    DrawLine(65,2,65,61);
    
    switch (System_State)
    {
    case System_Run:
        DrawString(68,6,"Run",1);
        break;
    
    case System_Init:
        DrawString(68,6,"Init",1);
        break;
    
    case System_Stop:
        DrawString(68,6,"Stop",1);
        break;
    }

    if(SPLL_Flag == SPLL_OK)
        DrawString(68,14,"Locked",1);
    else
        DrawString(68,14,"Unlocked",1);
    //DrawString(,);
}