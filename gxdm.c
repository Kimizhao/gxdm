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
unsigned char which_group;
//unsigned char code TAB5[]={" CW "};
//unsigned char code TAB6[]={" CCW"};

unsigned char const dofly[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
		                  	 0x77,0x7c,0x39,0x5e,0x79,0x71};//0-F

void main()
{
	uchar key;
	speed_num=0;
	timer_num=0;
	TU=0;
	//LCD 初始化
	Init_ST7920();  
	DisplayUpdata(1);
	WP=0;
	
	WrToROM(1,GROUP_DEFAULT,1);
	
	which_fun=FUN_NON;
	RdFromROM(&which_group,GROUP_DEFAULT,1);
	
	WriteToROM(128,256,0,GROUP_1);
	WriteToROM(512,768,1,GROUP_7);
	
	ReadFromROM(&timer_num,&speed_num,&TU,3);
	
	Num_zhuanh(speed_num,2);
	Num_zhuanh(timer_num,1);
	TURN_FZ(TU);
	

	
	while(1)
	{
		key=keyscan();
		switch(key)
		{
			case BT_TIMER:
				which_fun=FUN_TIMER;
				ClearGroupRow(1,which_group);
				break;
			case BT_SPEED:
				which_fun=FUN_SPEED;
				ClearGroupRow(2,which_group);
				break;
			case BT_TURN:
				which_fun=FUN_TURN;
				ClearGroupRow(3,which_group);
				break;
			case BT_CRST:
				break;
			case BT_ESC:
				break;
			case BT_UP:
				if (which_fun!=FUN_NON)
				{
					mDelay(1000);
					switch (which_fun)
					{
						case FUN_TIMER:
							timer_num++;
							Num_zhuanh(timer_num,1);
							break;
						case FUN_SPEED:
							speed_num++;
							Num_zhuanh(speed_num,2);
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
					ReadFromROM(&timer_num,&speed_num,&TU,which_group*3+1);
					Num_zhuanh(speed_num,2);
					Num_zhuanh(timer_num,1);
					TURN_FZ(TU);
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
							Num_zhuanh(timer_num,1);
							break;
						case FUN_SPEED:
							speed_num--;
							Num_zhuanh(speed_num,2);
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
					ReadFromROM(&timer_num,&speed_num,&TU,which_group*3+1);
					Num_zhuanh(speed_num,2);
					Num_zhuanh(timer_num,1);
					TURN_FZ(TU);
					mDelay(500);
				}
				break;
			case BT_ENT:P0=dofly[7];break;
			case BT_WATER:P0=dofly[8];break;
			case BT_STOP:P0=dofly[9];break;
			case BT_GREASE:P0=dofly[10];break;
			case BT_START:P0=dofly[11];break;
			default:
				break;
		}

	}
	
	
/*
   speed_num=278;
   timer_num=678;
   TU=0;//0 为CW 1为CCW
   Init_ST7920(); 
  // CGRAM(); //写入自定义字符 
   DisplayUpdata();
   Num_zhuanh(speed_num,2);
   //WP=0;//写保护关掉
  
WriteToROM(timer_num,speed_num,TU,0);
   speed_num=200;
   timer_num=600;
   TU=1;//0 为CW 1为CCW

ReadFromROM(&timer_num,&speed_num,&TU,0);
   // RdFromROM(timer_num,0,1);//调用存储数据                                                                                                                                                              RdFromROM(timer_num,0,2);
    Num_zhuanh(timer_num,1);
    Num_zhuanh(speed_num,2);
	TURN_FZ(TU);
 while(1)
   {     

     if(curr!=currold) //光标位置变化，则更新显示
      {
       DisplayUpdata();
       currold=curr;
      } 
 
   if(!KEY_UP)  
    {
     DelayMs(10);
     if(!KEY_UP)     
    {
        while(!KEY_UP);
      {
    if(curr<4)
     //判断数组中数值个数
     { curr++; }
      }
    }
 }

  if(!KEY_DOWN) 
    {
     DelayMs(10);
       if(!KEY_DOWN)     
         {
           while(!KEY_DOWN);
               {
                    if(curr>0)
                    { curr--; }
                }
          }
     }  



  if(!KEY_TURN) 
    {
     DelayMs(10);
       if(!KEY_TURN)     
         {
		  TU=!TU;
		  	speed_num=speed_num+10;
			 Num_zhuanh(speed_num,2);
           while(!KEY_TURN)
               {
/*                     if(TU)
                    { LCD_PutString(4,3,TAB5);
				
					}
                    if(!TU)
                    { LCD_PutString(4,3,TAB6);
				//	speed_num=speed_num-10;
					} */
				
 
 /*
 
                }

				
          }
     }  



  if(!KEY_TIMER) 
    {
     DelayMs(10);
       if(!KEY_TIMER)     
         {
           while(!KEY_TIMER);
               {
             timer_num=timer_num+5;
			 Num_zhuanh(timer_num,1);
			 TU=!TU;
			 TURN_FZ(TU);

                }
          }
     }  
	 	 
}

*/

}





/***********************************************
                 MAIN1

void main()
{
   speed_num=278;
   timer_num=0;
   Init_ST7920(); 
   CGRAM(); //写入自定义字符 
   DisplayUpdata();
   Num_zhuanh(timer_num,1);
   Num_zhuanh(speed_num,2);
   while(1)
   {     

     if(curr!=currold) //光标位置变化，则更新显示
      {
       DisplayUpdata();
       currold=curr;
      } 
 
   if(!KEY_UP)  
    {
     DelayMs(10);
     if(!KEY_UP)     
    {
        while(!KEY_UP);
      {
    if(curr<4)
     //判断数组中数值个数
     { curr++; }
      }
    }
 }

  if(!KEY_DOWN) 
    {
     DelayMs(10);
       if(!KEY_DOWN)     
         {
           while(!KEY_DOWN);
               {
                    if(curr>0)
                    { curr--; }
                }
          }
     }  



  if(!KEY_TURN) 
    {
     DelayMs(10);
       if(!KEY_TURN)     
         {
		  TU=!TU;
		  	speed_num=speed_num+10;
			 Num_zhuanh(speed_num,2);
           while(!KEY_TURN)
               {
                    if(TU)
                    { LCD_PutString(4,3,TAB5);
				
					}
                    if(!TU)
                    { LCD_PutString(4,3,TAB6);
				//	speed_num=speed_num-10;
					}
				
                }

				
          }
     }  



  if(!KEY_TIMER) 
    {
     DelayMs(10);
       if(!KEY_TIMER)     
         {
           while(!KEY_TIMER);
               {
             timer_num=timer_num+5;
			 Num_zhuanh(timer_num,1);
			 TU=!TU;
			 TURN_FZ(TU);

                }
          }
     }  
	 	 
}
}

***********************************************/
