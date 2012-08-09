
#include <reg52.h>
#include <intrins.h>
#include "at24c02.h"
#include"pin_name.h"
#include "lcd12864.h"


void main()
{
	

   speed_num=278;
   timer_num=678;
   TU=0;//0 ΪCW 1ΪCCW
   Init_ST7920(); 
  // CGRAM(); //д���Զ����ַ� 
   DisplayUpdata();
   Num_zhuanh(speed_num,2);
   WP=0;//д�����ص�
  
WriteToROM(timer_num,speed_num,TU,0);
   speed_num=200;
   timer_num=600;
   TU=1;//0 ΪCW 1ΪCCW

ReadFromROM(&timer_num,&speed_num,&TU,0);
   // RdFromROM(timer_num,0,1);//���ô洢����                                                                                                                                                              RdFromROM(timer_num,0,2);
    Num_zhuanh(timer_num,1);
    Num_zhuanh(speed_num,2);
	TURN_FZ(TU);
 while(1)
   {     

     if(curr!=currold) //���λ�ñ仯���������ʾ
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
     //�ж���������ֵ����
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





/***********************************************
                 MAIN1

void main()
{
   speed_num=278;
   timer_num=0;
   Init_ST7920(); 
   CGRAM(); //д���Զ����ַ� 
   DisplayUpdata();
   Num_zhuanh(timer_num,1);
   Num_zhuanh(speed_num,2);
   while(1)
   {     

     if(curr!=currold) //���λ�ñ仯���������ʾ
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
     //�ж���������ֵ����
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
