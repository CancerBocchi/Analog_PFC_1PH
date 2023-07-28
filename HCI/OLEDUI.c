#include "oled.h"
#include "OLEDUI.h"



#define SCREEN_COLUMN 128
#define SCREEN_ROW 64
#define SCREEN_PAGE_NUM 8
#define NUM_OFCHINESE   8
#define MAX(x,y)  		((x)>(y)? (x):(y))
#define MIN(x,y)  		((x)<(y)? (x):(y))

uint8_t ScreenBuffer[8][128];
static unsigned char _BitTableS[8]={0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};

uint8_t font5x7[]={
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
    0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
    0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
    0x18, 0x3C, 0x7E, 0x3C, 0x18,
    0x1C, 0x57, 0x7D, 0x57, 0x1C,
    0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
    0x00, 0x18, 0x3C, 0x18, 0x00,
    0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
    0x00, 0x18, 0x24, 0x18, 0x00,
    0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
    0x30, 0x48, 0x3A, 0x06, 0x0E,
    0x26, 0x29, 0x79, 0x29, 0x26,
    0x40, 0x7F, 0x05, 0x05, 0x07,
    0x40, 0x7F, 0x05, 0x25, 0x3F,
    0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
    0x7F, 0x3E, 0x1C, 0x1C, 0x08,
    0x08, 0x1C, 0x1C, 0x3E, 0x7F,
    0x14, 0x22, 0x7F, 0x22, 0x14,
    0x5F, 0x5F, 0x00, 0x5F, 0x5F,
    0x06, 0x09, 0x7F, 0x01, 0x7F,
    0x00, 0x66, 0x89, 0x95, 0x6A,
    0x60, 0x60, 0x60, 0x60, 0x60,
    0x94, 0xA2, 0xFF, 0xA2, 0x94,
    0x08, 0x04, 0x7E, 0x04, 0x08,
    0x10, 0x20, 0x7E, 0x20, 0x10,
    0x08, 0x08, 0x2A, 0x1C, 0x08,
    0x08, 0x1C, 0x2A, 0x08, 0x08,
    0x1E, 0x10, 0x10, 0x10, 0x10,
    0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
    0x30, 0x38, 0x3E, 0x38, 0x30,
    0x06, 0x0E, 0x3E, 0x0E, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5F, 0x00, 0x00,
    0x00, 0x07, 0x00, 0x07, 0x00,
    0x14, 0x7F, 0x14, 0x7F, 0x14,
    0x24, 0x2A, 0x7F, 0x2A, 0x12,
    0x23, 0x13, 0x08, 0x64, 0x62,
    0x36, 0x49, 0x56, 0x20, 0x50,
    0x00, 0x08, 0x07, 0x03, 0x00,
    0x00, 0x1C, 0x22, 0x41, 0x00,
    0x00, 0x41, 0x22, 0x1C, 0x00,
    0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
    0x08, 0x08, 0x3E, 0x08, 0x08,
    0x00, 0x80, 0x70, 0x30, 0x00,
    0x08, 0x08, 0x08, 0x08, 0x08,
    0x00, 0x00, 0x60, 0x60, 0x00,
    0x20, 0x10, 0x08, 0x04, 0x02,
    0x3E, 0x51, 0x49, 0x45, 0x3E,
    0x00, 0x42, 0x7F, 0x40, 0x00,
    0x72, 0x49, 0x49, 0x49, 0x46,
    0x21, 0x41, 0x49, 0x4D, 0x33,
    0x18, 0x14, 0x12, 0x7F, 0x10,
    0x27, 0x45, 0x45, 0x45, 0x39,
    0x3C, 0x4A, 0x49, 0x49, 0x31,
    0x41, 0x21, 0x11, 0x09, 0x07,
    0x36, 0x49, 0x49, 0x49, 0x36,
    0x46, 0x49, 0x49, 0x29, 0x1E,
    0x00, 0x00, 0x14, 0x00, 0x00,
    0x00, 0x40, 0x34, 0x00, 0x00,
    0x00, 0x08, 0x14, 0x22, 0x41,
    0x14, 0x14, 0x14, 0x14, 0x14,
    0x00, 0x41, 0x22, 0x14, 0x08,
    0x02, 0x01, 0x59, 0x09, 0x06,
    0x3E, 0x41, 0x5D, 0x59, 0x4E,
    0x7C, 0x12, 0x11, 0x12, 0x7C,
    0x7F, 0x49, 0x49, 0x49, 0x36,
    0x3E, 0x41, 0x41, 0x41, 0x22,
    0x7F, 0x41, 0x41, 0x41, 0x3E,
    0x7F, 0x49, 0x49, 0x49, 0x41,
    0x7F, 0x09, 0x09, 0x09, 0x01,
    0x3E, 0x41, 0x41, 0x51, 0x73,
    0x7F, 0x08, 0x08, 0x08, 0x7F,
    0x00, 0x41, 0x7F, 0x41, 0x00,
    0x20, 0x40, 0x41, 0x3F, 0x01,
    0x7F, 0x08, 0x14, 0x22, 0x41,
    0x7F, 0x40, 0x40, 0x40, 0x40,
    0x7F, 0x02, 0x1C, 0x02, 0x7F,
    0x7F, 0x04, 0x08, 0x10, 0x7F,
    0x3E, 0x41, 0x41, 0x41, 0x3E,
    0x7F, 0x09, 0x09, 0x09, 0x06,
    0x3E, 0x41, 0x51, 0x21, 0x5E,
    0x7F, 0x09, 0x19, 0x29, 0x46,
    0x26, 0x49, 0x49, 0x49, 0x32,
    0x03, 0x01, 0x7F, 0x01, 0x03,
    0x3F, 0x40, 0x40, 0x40, 0x3F,
    0x1F, 0x20, 0x40, 0x20, 0x1F,
    0x3F, 0x40, 0x38, 0x40, 0x3F,
    0x63, 0x14, 0x08, 0x14, 0x63,
    0x03, 0x04, 0x78, 0x04, 0x03,
    0x61, 0x59, 0x49, 0x4D, 0x43,
    0x00, 0x7F, 0x41, 0x41, 0x41,
    0x02, 0x04, 0x08, 0x10, 0x20,
    0x00, 0x41, 0x41, 0x41, 0x7F,
    0x04, 0x02, 0x01, 0x02, 0x04,
    0x40, 0x40, 0x40, 0x40, 0x40,
    0x00, 0x03, 0x07, 0x08, 0x00,
    0x20, 0x54, 0x54, 0x78, 0x40,
    0x7F, 0x28, 0x44, 0x44, 0x38,
    0x38, 0x44, 0x44, 0x44, 0x28,
    0x38, 0x44, 0x44, 0x28, 0x7F,
    0x38, 0x54, 0x54, 0x54, 0x18,
    0x00, 0x08, 0x7E, 0x09, 0x02,
    0x18, 0xA4, 0xA4, 0x9C, 0x78,
    0x7F, 0x08, 0x04, 0x04, 0x78,
    0x00, 0x44, 0x7D, 0x40, 0x00,
    0x20, 0x40, 0x40, 0x3D, 0x00,
    0x7F, 0x10, 0x28, 0x44, 0x00,
    0x00, 0x41, 0x7F, 0x40, 0x00,
    0x7C, 0x04, 0x78, 0x04, 0x78,
    0x7C, 0x08, 0x04, 0x04, 0x78,
    0x38, 0x44, 0x44, 0x44, 0x38,
    0xFC, 0x18, 0x24, 0x24, 0x18,
    0x18, 0x24, 0x24, 0x18, 0xFC,
    0x7C, 0x08, 0x04, 0x04, 0x08,
    0x48, 0x54, 0x54, 0x54, 0x24,
    0x04, 0x04, 0x3F, 0x44, 0x24,
    0x3C, 0x40, 0x40, 0x20, 0x7C,
    0x1C, 0x20, 0x40, 0x20, 0x1C,
    0x3C, 0x40, 0x30, 0x40, 0x3C,
    0x44, 0x28, 0x10, 0x28, 0x44,
    0x4C, 0x90, 0x90, 0x90, 0x7C,
    0x44, 0x64, 0x54, 0x4C, 0x44,
    0x00, 0x08, 0x36, 0x41, 0x00,
    0x00, 0x00, 0x77, 0x00, 0x00,
    0x00, 0x41, 0x36, 0x08, 0x00,
    0x02, 0x01, 0x02, 0x04, 0x02,
    0x3C, 0x26, 0x23, 0x26, 0x3C,
    0x1E, 0xA1, 0xA1, 0x61, 0x12,
    0x3A, 0x40, 0x40, 0x20, 0x7A,
    0x38, 0x54, 0x54, 0x55, 0x59,
    0x21, 0x55, 0x55, 0x79, 0x41,
    0x21, 0x54, 0x54, 0x78, 0x41,
    0x21, 0x55, 0x54, 0x78, 0x40,
    0x20, 0x54, 0x55, 0x79, 0x40,
    0x0C, 0x1E, 0x52, 0x72, 0x12,
    0x39, 0x55, 0x55, 0x55, 0x59,
    0x39, 0x54, 0x54, 0x54, 0x59,
    0x39, 0x55, 0x54, 0x54, 0x58,
    0x00, 0x00, 0x45, 0x7C, 0x41,
    0x00, 0x02, 0x45, 0x7D, 0x42,
    0x00, 0x01, 0x45, 0x7C, 0x40,
    0xF0, 0x29, 0x24, 0x29, 0xF0,
    0xF0, 0x28, 0x25, 0x28, 0xF0,
    0x7C, 0x54, 0x55, 0x45, 0x00,
    0x20, 0x54, 0x54, 0x7C, 0x54,
    0x7C, 0x0A, 0x09, 0x7F, 0x49,
    0x32, 0x49, 0x49, 0x49, 0x32,
    0x32, 0x48, 0x48, 0x48, 0x32,
    0x32, 0x4A, 0x48, 0x48, 0x30,
    0x3A, 0x41, 0x41, 0x21, 0x7A,
    0x3A, 0x42, 0x40, 0x20, 0x78,
    0x00, 0x9D, 0xA0, 0xA0, 0x7D,
    0x39, 0x44, 0x44, 0x44, 0x39,
    0x3D, 0x40, 0x40, 0x40, 0x3D,
    0x3C, 0x24, 0xFF, 0x24, 0x24,
    0x48, 0x7E, 0x49, 0x43, 0x66,
    0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
    0xFF, 0x09, 0x29, 0xF6, 0x20,
    0xC0, 0x88, 0x7E, 0x09, 0x03,
    0x20, 0x54, 0x54, 0x79, 0x41,
    0x00, 0x00, 0x44, 0x7D, 0x41,
    0x30, 0x48, 0x48, 0x4A, 0x32,
    0x38, 0x40, 0x40, 0x22, 0x7A,
    0x00, 0x7A, 0x0A, 0x0A, 0x72,
    0x7D, 0x0D, 0x19, 0x31, 0x7D,
    0x26, 0x29, 0x29, 0x2F, 0x28,
    0x26, 0x29, 0x29, 0x29, 0x26,
    0x30, 0x48, 0x4D, 0x40, 0x20,
    0x38, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x38,
    0x2F, 0x10, 0xC8, 0xAC, 0xBA,
    0x2F, 0x10, 0x28, 0x34, 0xFA,
    0x00, 0x00, 0x7B, 0x00, 0x00,
    0x08, 0x14, 0x2A, 0x14, 0x22,
    0x22, 0x14, 0x2A, 0x14, 0x08,
    0x95, 0x00, 0x22, 0x00, 0x95,
    0xAA, 0x00, 0x55, 0x00, 0xAA,
    0xAA, 0x55, 0xAA, 0x55, 0xAA,
    0x00, 0x00, 0x00, 0xFF, 0x00,
    0x10, 0x10, 0x10, 0xFF, 0x00,
    0x14, 0x14, 0x14, 0xFF, 0x00,
    0x10, 0x10, 0xFF, 0x00, 0xFF,
    0x10, 0x10, 0xF0, 0x10, 0xF0,
    0x14, 0x14, 0x14, 0xFC, 0x00,
    0x14, 0x14, 0xF7, 0x00, 0xFF,
    0x00, 0x00, 0xFF, 0x00, 0xFF,
    0x14, 0x14, 0xF4, 0x04, 0xFC,
    0x14, 0x14, 0x17, 0x10, 0x1F,
    0x10, 0x10, 0x1F, 0x10, 0x1F,
    0x14, 0x14, 0x14, 0x1F, 0x00,
    0x10, 0x10, 0x10, 0xF0, 0x00,
    0x00, 0x00, 0x00, 0x1F, 0x10,
    0x10, 0x10, 0x10, 0x1F, 0x10,
    0x10, 0x10, 0x10, 0xF0, 0x10,
    0x00, 0x00, 0x00, 0xFF, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0xFF, 0x10,
    0x00, 0x00, 0x00, 0xFF, 0x14,
    0x00, 0x00, 0xFF, 0x00, 0xFF,
    0x00, 0x00, 0x1F, 0x10, 0x17,
    0x00, 0x00, 0xFC, 0x04, 0xF4,
    0x14, 0x14, 0x17, 0x10, 0x17,
    0x14, 0x14, 0xF4, 0x04, 0xF4,
    0x00, 0x00, 0xFF, 0x00, 0xF7,
    0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0xF7, 0x00, 0xF7,
    0x14, 0x14, 0x14, 0x17, 0x14,
    0x10, 0x10, 0x1F, 0x10, 0x1F,
    0x14, 0x14, 0x14, 0xF4, 0x14,
    0x10, 0x10, 0xF0, 0x10, 0xF0,
    0x00, 0x00, 0x1F, 0x10, 0x1F,
    0x00, 0x00, 0x00, 0x1F, 0x14,
    0x00, 0x00, 0x00, 0xFC, 0x14,
    0x00, 0x00, 0xF0, 0x10, 0xF0,
    0x10, 0x10, 0xFF, 0x10, 0xFF,
    0x14, 0x14, 0x14, 0xFF, 0x14,
    0x10, 0x10, 0x10, 0x1F, 0x00,
    0x00, 0x00, 0x00, 0xF0, 0x10,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
    0xFF, 0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xFF, 0xFF,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
    0x38, 0x44, 0x44, 0x38, 0x44,
    0x7C, 0x2A, 0x2A, 0x3E, 0x14,
    0x7E, 0x02, 0x02, 0x06, 0x06,
    0x02, 0x7E, 0x02, 0x7E, 0x02,
    0x63, 0x55, 0x49, 0x41, 0x63,
    0x38, 0x44, 0x44, 0x3C, 0x04,
    0x40, 0x7E, 0x20, 0x1E, 0x20,
    0x06, 0x02, 0x7E, 0x02, 0x02,
    0x99, 0xA5, 0xE7, 0xA5, 0x99,
    0x1C, 0x2A, 0x49, 0x2A, 0x1C,
    0x4C, 0x72, 0x01, 0x72, 0x4C,
    0x30, 0x4A, 0x4D, 0x4D, 0x30,
    0x30, 0x48, 0x78, 0x48, 0x30,
    0xBC, 0x62, 0x5A, 0x46, 0x3D,
    0x3E, 0x49, 0x49, 0x49, 0x00,
    0x7E, 0x01, 0x01, 0x01, 0x7E,
    0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
    0x44, 0x44, 0x5F, 0x44, 0x44,
    0x40, 0x51, 0x4A, 0x44, 0x40,
    0x40, 0x44, 0x4A, 0x51, 0x40,
    0x00, 0x00, 0xFF, 0x01, 0x03,
    0xE0, 0x80, 0xFF, 0x00, 0x00,
    0x08, 0x08, 0x6B, 0x6B, 0x08,
    0x36, 0x12, 0x36, 0x24, 0x36,
    0x06, 0x0F, 0x09, 0x0F, 0x06,
    0x00, 0x00, 0x18, 0x18, 0x00,
    0x00, 0x00, 0x10, 0x10, 0x00,
    0x30, 0x40, 0xFF, 0x01, 0x01,
    0x00, 0x1F, 0x01, 0x01, 0x1E,
    0x00, 0x19, 0x1D, 0x17, 0x12,
    0x00, 0x3C, 0x3C, 0x3C, 0x3C,
    0x00, 0x00, 0x00, 0x00, 0x00,
};





/*
 *更新显示
 */
void flash()
{
    for(uint8_t i=0;i<8;i++)
    {
        OLED_WriteAdd(i+0xb0);//设置页地址（0~7）
		OLED_WriteAdd(((0x00&0xf0)>>4)|0x10);//设置显示位置—列低地址
		OLED_WriteAdd((0x00&0x0f)|0x00);//设置显示位置—列高地址

        for(uint8_t m=0;m<128;m++)
        {    
            OLED_WriteData(ScreenBuffer[i][m]); 
        }
    }
   
    
}

void OLED_CleanBuffer(void)
{
	uint8_t i,n;
	for(i=0;i<8;i++){				
		for(n=0;n<128;n++){
            ScreenBuffer[i][n]=0x00;  
        }
	} //更新缓冲区显示
}

unsigned char pgm_read_byte(const unsigned char *addr)
{
    return *addr;
}

//计算m^n
unsigned int oled_pow(unsigned char m,unsigned char n)
{
	unsigned int result=1;	 
	while(n--)result*=m;    
	return result;
}	

//读取选择的缓冲区的8位数据
unsigned char ReadByteBuffer(int page,int x)
{
	return  ScreenBuffer[page][x];
}
//写入读取选择的缓冲区8位数据
void WriteByteBuffer(int page,int x,unsigned char byte)
{
	ScreenBuffer[page][x] =byte;
}
// 设置当前选择的缓冲区中某一个点的亮灭,bg,背景颜色,1为原色，0为反色
void SetPointBuffer(uint8_t x, uint8_t y,uint8_t bg)
{
    if (x > SCREEN_COLUMN - 1 || y > SCREEN_ROW - 1) // 超出范围
        return;
    if(bg){
        ScreenBuffer[y / SCREEN_PAGE_NUM][x] |= (1<<(y%SCREEN_PAGE_NUM));
    }
    else{
        ScreenBuffer[y / SCREEN_PAGE_NUM][x] &= ~(1<<(y%SCREEN_PAGE_NUM));
    }       
}

//给选择的缓冲区写入8位数据
void FillByte(int page,int x,unsigned  char byte)
{
	
		WriteByteBuffer(page,x,ReadByteBuffer(page,x)|(byte));

		//WriteByteBuffer(page,x,ReadByteBuffer(page,x)&(~byte));
}

// 绘制一个点
void DrawPixel(uint8_t x, uint8_t y,uint8_t bg)
{
    SetPointBuffer(x, y, bg);
}

// 划线
// 参数:起点坐标 终点坐标
void DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    uint8_t us;
    uint8_t usX_Current, usY_Current;

    int lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance;
    int lIncrease_X, lIncrease_Y;

    lDelta_X = x2 - x1; // 计算坐标增量
    lDelta_Y = y2 - y1;

    usX_Current = x1;
    usY_Current = y1;

    if (lDelta_X > 0)
        lIncrease_X = 1; // 设置单步正方向
    else if (lDelta_X == 0)
        lIncrease_X = 0; // 垂直线
    else
    {
        lIncrease_X = -1; // 设置单步反方向
        lDelta_X = -lDelta_X;
    }

    // Y轴的处理方式与上图X轴的处理方式同理
    if (lDelta_Y > 0)
        lIncrease_Y = 1;
    else if (lDelta_Y == 0)
        lIncrease_Y = 0; // 水平线
    else
    {
        lIncrease_Y = -1;
        lDelta_Y = -lDelta_Y;
    }

    // 选取不那么陡的方向依次画点
    if (lDelta_X > lDelta_Y)
        lDistance = lDelta_X;
    else
        lDistance = lDelta_Y;

    // 依次画点 进入缓存区 画好后再刷新缓冲区就好啦
    for (us = 0; us <= lDistance + 1; us++) // 画线输出
    {
        SetPointBuffer(usX_Current, usY_Current, 1); // 画点
        lError_X += lDelta_X;
        lError_Y += lDelta_Y;

        if (lError_X > lDistance)
        {
            lError_X -= lDistance;
            usX_Current += lIncrease_X;
        }

        if (lError_Y > lDistance)
        {
            lError_Y -= lDistance;
            usY_Current += lIncrease_Y;
        }
    }

}
// 快速划线 专用于画横平的线 提高效率
void DrawFastHLine(uint8_t x, uint8_t y, uint8_t w)
{
    int end = x + w;
    int a;
    for (a = MAX(0, x); a < MIN(end, SCREEN_COLUMN); a++)
    {
        SetPointBuffer(a, y, 1);
    }

}
// 快速划线 专用于画竖直的线 提高效率
void DrawFastVLine(uint8_t x, uint8_t y, uint8_t h)
{
    int end = y + h;
    int a;

    for (a = MAX(0, y); a < MIN(end, SCREEN_ROW); a++)
    {
        SetPointBuffer(x, a, 1);
    }

}

// 画部分圆
// 圆心坐标 半径 4份圆要画哪一份或哪几份
void DrawCircleHelper(uint8_t x0, uint8_t y0, unsigned char r, unsigned char cornername)
{
    int f = 1 - r;
    int ddF_x = 1;
    int ddF_y = -2 * r;
    int x = 0;
    int y = r;

    while (x < y)
    {
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }

        x++;
        ddF_x += 2;
        f += ddF_x;

        if (cornername & 0x4) // 右上
        {
            // 此处画圆的方式是交替打点 从2边打到中间 最终x<y就打完点跳出循环
            SetPointBuffer(x0 + x, y0 + y, 1);
            SetPointBuffer(x0 + y, y0 + x, 1);
        }
        if (cornername & 0x2) // 右下
        {
            SetPointBuffer(x0 + x, y0 - y, 1);
            SetPointBuffer(x0 + y, y0 - x, 1);
        }
        if (cornername & 0x8) // 左上
        {
            SetPointBuffer(x0 - y, y0 + x, 1);
            SetPointBuffer(x0 - x, y0 + y, 1);
        }
        if (cornername & 0x1) // 左下
        {
            SetPointBuffer(x0 - y, y0 - x, 1);
            SetPointBuffer(x0 - x, y0 - y, 1);
        }
    }

}
//给选择的缓冲区填充一个矩形
void FillRect(int x,int y,int width,int height)
{
	int i,j;
	int temp =(y+height-1)/8-y/8;	//需要填充的矩形在屏幕中所占的行数 屏幕被分为8大行
	if(x>SCREEN_COLUMN ||y>SCREEN_ROW)   
			return;
	for(i=x; i<x+width&&i<128; i++)
	{
		if( temp==0 )
		{
			FillByte(y/8,i,_BitTableS[height-1]<<(y%8));
		}
		else
		{
			//从左往右 竖向填充
			FillByte(y/8,i,_BitTableS[(8-y%8)-1]<<(y%8));
			for(j=1;j<temp;j++)
			{
				FillByte(y/8+j,i,0xff);
			}
			FillByte(y/8+temp,i,_BitTableS[(height-1+y)%8]);
		}	
	}
}
//使用对角点填充矩形
void DrawRect1(int left,int top,int right,int bottom)
{
	DrawLine ( left, top, right, top );
	DrawLine ( left, bottom , right , bottom );
	DrawLine ( left, top, left, bottom );
	DrawLine ( right , top, right , bottom );	
}
//功能:使用对角点填充矩形
void DrawFillRect1(int left,int top,int right,int bottom)
{
	DrawRect1(left,top,right,bottom);
	FillRect(left+1,top+1,right-left-1,bottom-top-1);	
}
//左上角坐标 矩形宽高
void DrawRect2(int left,int top,int width,int height)
{
		DrawLine ( left, top, left+width-1, top );
		DrawLine ( left, top+height-1 , left+width-1 , top+height-1 );
		DrawLine ( left, top, left, top+height-1);
		DrawLine ( left+width-1 , top, left+width-1 , top+height-1);	
}
//填充矩形
void DrawFillRect2(int left,int top,int width,int height)
{
	//先用上面的函数画外框
	DrawRect2(left,top,width,height);
	//然后填充实心
	FillRect(left+1,top+1,width-1,height-1);	
}

//填充2个四分之一圆和中间的矩形
//此函数专用于画圆角矩形
//右上四分之一圆或左下四分之一圆的圆心 半径 中间矩形的高
void DrawFillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta)
{
	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0;
	int y = r;
	

	while (x < y)
	{
		if (f >= 0){
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (cornername & 0x1)//填充右边的2个四分之一圆和中间的矩形
		{
			DrawFastVLine(x0+x, y0-y, 2*y+1+delta);
			DrawFastVLine(x0+y, y0-x, 2*x+1+delta);
		}
		if (cornername & 0x2)//填充左边的2个四分之一圆和中间的矩形
		{
			DrawFastVLine(x0-x, y0-y, 2*y+1+delta);
			DrawFastVLine(x0-y, y0-x, 2*x+1+delta);
		}
	}
}

// 画圆角矩形
void DrawRoundRect(uint8_t x, uint8_t y, unsigned char w, unsigned char h, unsigned char r)
{
    // 画出边缘 因为边缘是直线 所以专用高效率函数
    DrawFastHLine(x + r, y, w - 2 * r);         // Top
    DrawFastHLine(x + r, y + h - 1, w - 2 * r); // Bottom
    DrawFastVLine(x, y + r, h - 2 * r);         // Left
    DrawFastVLine(x + w - 1, y + r, h - 2 * r); // Right
    // 画出四个圆角
    DrawCircleHelper(x + r, y + r, r, 1);
    DrawCircleHelper(x + w - r - 1, y + r, r, 2);
    DrawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4);
    DrawCircleHelper(x + r, y + h - r - 1, r, 8);

}

//画实心圆角矩形
void DrawfillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r)
{
  //画实心矩形
  DrawFillRect2(x+r, y, w-2*r, h);

  //再填充左右两边
  DrawFillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1);	//右上角的圆心
  DrawFillCircleHelper(x+r, y+r, r, 2, h-2*r-1);		//左下角的圆心
}
//direction=1,画左边,direction=0,画右边
void DrawHalfRoundRect(uint8_t x,uint8_t y,uint8_t w,uint8_t h,uint8_t direction)
{
    DrawFastHLine(x+1,y,w-2);
    DrawFastHLine(x+1,y+h,w-2);
   if(direction){
        DrawFastVLine(x,y+1,h-1);
        DrawFastVLine(x+w-1,y,h+1);
   }else{
        DrawFastVLine(x,y,h+1);
        DrawFastVLine(x+w-1,y+1,h-1);
   }
    
}

// 显示一个字符
// 字体尺寸1,2,3,4,5随便取，只要屏幕够大
void DrawChar(uint8_t x, uint8_t y, unsigned char c,float size,uint8_t bg)
{
    uint8_t i, j;
    unsigned char a, b;
     
    // 使用原作粗体字符
    // 判断一个字符的上下左右是否超出边界范围
    // if ((x >= SCREEN_COLUMN) ||     // Clip right
    //     (y >= SCREEN_ROW) ||        // Clip bottom
    //     ((x + 5 * size - 1) < 0) || // Clip left
    //     ((y + 8 * size - 1) < 0)    // Clip top
    // )
    //     return;
    if(!bg)
    {
        FillRect(x-(size),y-1,7*size,8*size+(2-size));
    }
    for (i = 0; i < 6; i++)
    {
        int line;
        // 一个字符在font5x7中由一行6个char表示
        // line为这个字符的第某行内容
        if (i == 5)
            line = 0x0;
        else
            line = pgm_read_byte(font5x7 + (c * 5) + i);

        for (j = 0; j < 8; j++)
        {
            // 不同号大小的字体只是最基础字体的放大倍数 这点要注意
            // 比如基础字是1个像素 放大后就是4个像素 再就是9个像素 达到马赛克的放大效果
            if(line&0x1)
            {
                for (a = 0; a < size; a++)
                    for (b = 0; b < size; b++)
                        SetPointBuffer(x + (i * size) + a, y + (j * size) + b, bg);
            }
            line >>= 1;
        }
    }
}

// 显示字符串 就是显示多次显示字符
void DrawString(uint8_t x, uint8_t y, char *str,uint8_t size)
{
    unsigned char j = 0, tempx = x, tempy = y;
    while (str[j] != '\0')
    {
        if (str[j] == '\n')
        {
            tempy += 8 * size;
            tempx = x;
            j++;
            continue;
        }
        DrawChar(tempx, tempy, str[j],size,1);
        tempx += size * 6;
        j++;
    }   
}
// 显示数字 就是多次显示数字的字符
void DrawNum(uint8_t x, uint8_t y, uint16_t num,uint8_t len,float size,uint8_t bg)
{
    unsigned char t, temp;
    unsigned char enshow = 0;

        for (t = 0; t < len; t++)
        {
            temp = (num / oled_pow(10, len - t - 1)) % 10;
            if (enshow == 0 && t < (len - 1))
            {
                if (temp == 0)
                {
                    DrawChar(x + (size * 6) * t, y, '0',size, bg);
                    continue;
                }
                else
                    enshow = 1;
            }
            DrawChar(x + (size * 6) * t, y, temp + '0',size, bg);
        }
    
}


//画一幅画，PCtoLCD2002参数请选择[阴码 列行式 逆向]
//起点坐标x y 图像取模数组 图像宽高w h
void DrawBitmap(int x, int y, const unsigned char *bitmap, unsigned char w, unsigned char h)
{
	int iCol,a;
	int yOffset = y % 8;
	int sRow = y / 8;
	int rows = h/8;

	if(h%8!=0) rows++;
	for(a = 0; a < rows; a++) 
	{
		int bRow = sRow + a;
		//if(bRow > (SCREEN_ROW/8)-1) break;
		if(bRow > -2) 
		{
			for (iCol = 0; iCol<w; iCol++) 
			{
				//if (iCol + x > (SCREEN_COLUMN-1)) break;
				if (iCol + x >= 0) 
				{
					if (bRow >= 0) 
					{
							unsigned char temp = ReadByteBuffer(bRow,x + iCol);
							temp^=(pgm_read_byte(bitmap+(a*w)+iCol) << yOffset);
							WriteByteBuffer(bRow,x + iCol,temp);	
					}
					if (yOffset && bRow<(SCREEN_ROW/8)-1 && bRow > -2) 
					{
							unsigned char temp = ReadByteBuffer(bRow+1,x + iCol);
							temp^=pgm_read_byte(bitmap+(a*w)+iCol) >> (8-yOffset);
							WriteByteBuffer( bRow+1,x + iCol,temp);						
					}
				}
			}
		}
	}
}

void OLED_DrawFloat(uint8_t x,uint8_t y,float num)
{
    uint16_t fractional;
    uint16_t integer=(int)num;   //整数部分
    num = (num-integer)*100;   //小数部分
    fractional = (int)num;
    DrawNum(x,y,integer,3 ,1,1);
    DrawChar(x+16,y,'.',1,1);
    DrawNum(x+24,y,fractional,2,1,1);

}

void OLED_Screen()
{   
    
    //HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    OLED_CleanBuffer();
    DrawRoundRect(2,2,126,62,10);
    DrawString(10,10,"Offset:",1);
	flash();
}

