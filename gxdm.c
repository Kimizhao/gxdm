/*
 *
 *
 */
#include "common.h"
#include "at24c02.h"
#include"pin_name.h"
#include "lcd12864.h"
#include "scaner.h"

unsigned char curr,currold;
unsigned char TU;
unsigned int speed_num;
unsigned int timer_num;
unsigned char which_fun;
char which_group;

unsigned char const dofly[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
		                  	 0x77,0x7c,0x39,0x5e,0x79,0x71};//0-F

void main()
{
	uchar key;
	speed_num=0;
	timer_num=0;
	TU=0;
	
	//LCD ³õÊ¼»¯
	Init_ST7920();  
	DisplayUpdata(1);
	WP=0;
	
	WrToROM(1,GROUP_DEFAULT,1);
	
	which_fun=FUN_NON;
	RdFromROM(&which_group,GROUP_DEFAULT,1);
	
	WriteToROM(128,256,0,GROUP_1);
	WriteToROM(512,768,1,GROUP_7);
	
	ReadFromROM(&timer_num,&speed_num,&TU,GROUP_1);
	
	Num_zhuanh(timer_num,LCD_TIMER_LINE);
	Num_zhuanh(speed_num,LCD_SPEED_LINE);
	TURN_FZ(TU);
	

	
	while(1)
	{
		key=keyscan();
		switch(key)
		{
			case BT_TIMER:
				which_fun=FUN_TIMER;
				ClearGroupRow(LCD_TIMER_LINE,which_group);
				break;
			case BT_SPEED:
				which_fun=FUN_SPEED;
				ClearGroupRow(LCD_SPEED_LINE,which_group);
				break;
			case BT_TURN:
				which_fun=FUN_TURN;
				ClearGroupRow(LCD_TURN_LINE,which_group);
				break;
			case BT_CRST:
				break;
			case BT_ESC:
				which_fun=FUN_NON;
				ReadFromROM(&timer_num,&speed_num,&TU,which_group*3+1);
				Num_zhuanh(timer_num,LCD_TIMER_LINE);
				Num_zhuanh(speed_num,LCD_SPEED_LINE);
				TURN_FZ(TU);
				ClearGroupRow(LCD_TIMER_LINE,which_group);
				mDelay(500);
				break;
			case BT_UP:
				if (which_fun!=FUN_NON)
				{
					mDelay(1000);
					switch (which_fun)
					{
						case FUN_TIMER:
							timer_num++;
							if(timer_num>999)timer_num=0;
							Num_zhuanh(timer_num,LCD_TIMER_LINE);
							break;
						case FUN_SPEED:
							speed_num++;
							if(speed_num>999)speed_num=0;
							Num_zhuanh(speed_num,LCD_SPEED_LINE);
							break;
						case FUN_TURN:
							TU=!TU;
							TURN_FZ(TU);
							break;
					default:
						break;
					}
				}else{
					which_group++;
					if (which_group==10)
					{
						which_group=0;
					}
					ReadFromROM(&timer_num,&speed_num,&TU,which_group*3+1);
					Num_zhuanh(timer_num,LCD_TIMER_LINE);
					Num_zhuanh(speed_num,LCD_SPEED_LINE);
					TURN_FZ(TU);
					ClearGroupRow(LCD_TIMER_LINE,which_group);
					mDelay(500);
				}
					
				break;
			case BT_DOWN:
				if (which_fun!=FUN_NON)
				{
					mDelay(1000);
					switch (which_fun)
					{
						case FUN_TIMER:
							timer_num--;
							if(timer_num<0)timer_num=999;
							Num_zhuanh(timer_num,LCD_TIMER_LINE);
							break;
						case FUN_SPEED:
							speed_num--;
							if(speed_num<0)speed_num=999;
							Num_zhuanh(speed_num,LCD_SPEED_LINE);
							break;
						case FUN_TURN:
							TU=!TU;
							TURN_FZ(TU);
							break;
					default:
						break;
					}
				}else{
					which_group--;
					if (which_group<0)
					{
						which_group=9;
					}
					ReadFromROM(&timer_num,&speed_num,&TU,which_group*3+1);
					Num_zhuanh(timer_num,LCD_TIMER_LINE);
					Num_zhuanh(speed_num,LCD_SPEED_LINE);
					TURN_FZ(TU);
					ClearGroupRow(LCD_TIMER_LINE,which_group);
					mDelay(500);
				}
				break;
			case BT_ENT:
 				WriteToROM(timer_num,speed_num,TU,which_group*3+1);
				WrToROM(&which_group,GROUP_DEFAULT,1); 
				ClearGroupRow(LCD_TIMER_LINE,which_group);
				
				break;
			case BT_WATER:P0=dofly[8];break;
			case BT_STOP:P0=dofly[9];break;
			case BT_GREASE:P0=dofly[10];break;
			case BT_START:P0=dofly[11];break;
			default:
				break;
		}

	}
	
}
