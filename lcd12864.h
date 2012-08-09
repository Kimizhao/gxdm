


/***********************************************
                  ÑÓÊ±º¯Êý
***********************************************/

#ifndef __LCD12864_H__
#define __LCD12864_H__

void DelayUs2x(unsigned char t);
void DelayMs(unsigned char t);
void DisplayUpdata(void);
void Check_Busy();
void Write_Cmd(unsigned char Cmd);
void Write_Data(unsigned char Data);
void Init_ST7920();
void DisplayCGRAM(unsigned char x,unsigned char y);
void LCD_PutString(unsigned char x,unsigned char y,unsigned char code *s);
void ClrScreen();
void DisplayUpdata(void);
void Num_zhuanh(unsigned int x,unsigned char u);
void TURN_FZ(unsigned char v);

#endif
