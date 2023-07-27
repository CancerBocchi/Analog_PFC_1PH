#include "keyboard.h"
#include "gpio.h"
#include "inc.h"

int KeyBoard_Num;


keyboard_pin col[4]=
{
    {col_1_GPIO_Port,col_1_Pin},
    {col_2_GPIO_Port,col_2_Pin},
    {col_3_GPIO_Port,col_3_Pin},
    {col_4_GPIO_Port,col_4_Pin}
};

keyboard_pin row[4]=
{
    {row_1_GPIO_Port,row_1_Pin},
    {row_2_GPIO_Port,row_2_Pin},
    {row_3_GPIO_Port,row_3_Pin},
    {row_4_GPIO_Port,row_4_Pin},
};

int keyboard_scan()
{
    int temp=0;
    for(int i=0;i<4;i++)
    {
        HAL_GPIO_WritePin(col[i].Port,col[i].Pin,1);
        for(int j=0;j<4;j++)
        {
            if(HAL_GPIO_ReadPin(row[j].Port,row[j].Pin))
            {
                temp=j*4+i+1;
                //Block_UART_printf(&huart1,"%d,%d,%d\n",j,i,temp);
            }
        }
        HAL_GPIO_WritePin(col[i].Port,col[i].Pin,0);
    }
    return temp;
}
/**
 * @brief 执行函数 switch语句中填写需要的内容
 * 
 */
void keyboard_execute()
{
    static int KeyBoard_Tick = 0;
    KeyBoard_Num = keyboard_scan();
    if(KeyBoard_Num)
    {
        if(HAL_GetTick() - KeyBoard_Tick >= 200)
        {
            //Block_UART_printf(&huart1,"%d\n",KeyBoard_Num);
           
            switch(KeyBoard_Num)
            {
                case 1:
                
                    break;
                case 2:

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
            KeyBoard_Tick = HAL_GetTick();
            KeyBoard_Num = 0;
        }
    }
}
