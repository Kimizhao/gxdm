#include <reg52.h>
#include <intrins.h>

sbit RS = P2^4;
sbit RW = P2^5;
sbit E  = P2^6;
sbit PSB= P2^1; //串并口选择端  并高串低
#define DataPort P0   

sbit KEY_UP=P3^0; //按键
sbit KEY_DOWN=P3^1;
sbit KEY_TURN=P3^2;
sbit KEY_TIMER=P3^3;

unsigned char curr,currold;//全局变量，当前箭头位置
unsigned char TU;
unsigned int speed_num;
unsigned int timer_num;
unsigned char turn_char[4];



unsigned char code user16x16[]={ //箭头图片
0x00,0x00,0x80,0x00,0x40,0x00,0x20,0x00,
0x10,0x00,0x08,0x00,0x04,0x00,0x02,0x00,
0x04,0x00,0x08,0x00,0x10,0x00,0x20,0x00,
0x40,0x00,0x80,0x00,0x00,0x00,0x00,0x00,
};



unsigned char code TAB1[]={"  TIMER: 065 SEC"};
unsigned char code TAB2[]={"  SPEED: 200 RPM"};
unsigned char code TAB3[]={"  TURN : CCW"};
unsigned char code TAB4[]={"  COUNT: 00"};
unsigned char code TAB5[]={" CW "};
unsigned char code TAB6[]={" CCW"};
unsigned char code TAB7[]={"0123456789"};

/***********************************************
                  延时函数
***********************************************/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}

void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     DelayUs2x(245);
     DelayUs2x(245);
 }
}

/***********************************************
                判忙函数
***********************************************/
void Check_Busy()
{  
    RS=0;  //写命令
    RW=1;  //读状态
    E=1;
    DataPort=0xff;
    while((DataPort&0x80)==0x80);//忙则等待
    E=0;
}

/***********************************************
                写入命令
***********************************************/
void Write_Cmd(unsigned char Cmd)
{
 Check_Busy();
 RS=0;  //写命令
 RW=0;  //write
 E=1;
 DataPort=Cmd;
 DelayUs2x(5);
 E=0;
 DelayUs2x(5);
}

/***********************************************
                 写入数据
***********************************************/
void Write_Data(unsigned char Data)
{
 Check_Busy();
 RS=1; //写数据
 RW=0; //write
 E=1;
 DataPort=Data;
 DelayUs2x(5);
 E=0;
 DelayUs2x(5);
}

/***********************************************
               液晶屏初始化
***********************************************/
void Init_ST7920()
{  
   DelayMs(40);           //大于40MS的延时程序
   PSB=1;                 //设置为8BIT并口工作模式
   DelayMs(1);            //延时
   Write_Cmd(0x30);       //选择基本指令集
   DelayUs2x(50);         //延时大于100us
   Write_Cmd(0x30);       //选择8bit数据流
   DelayUs2x(20);         //延时大于37us
   Write_Cmd(0x0c);       //开显示(无游标、不反白)
   DelayUs2x(50);         //延时大于100us
   Write_Cmd(0x01);       //清除显示，并且设定地址指针为00H
   DelayMs(15);           //延时大于10ms
   Write_Cmd(0x06);       //指定在资料的读取及写入时，设定游标的移动方向及指定显示的移位，光标从右向左加1位移动
   DelayUs2x(50);         //延时大于100us
}

/***********************************************
                用户自定义字符
***********************************************/
void CGRAM()
{ 
     int i;
     Write_Cmd(0x30); 
     Write_Cmd(0x40);
     for(i=0;i<16;i++)
       {
        Write_Data(user16x16[i*2]);
        Write_Data(user16x16[i*2+1]);
      }
}   

/***********************************************
               显示用户自定义字符
***********************************************/
void DisplayCGRAM(unsigned char x,unsigned char y)
{ 
 switch(y)
     {
   case 1: Write_Cmd(0x80+x);break;
   case 2: Write_Cmd(0x90+x);break;
   case 3: Write_Cmd(0x88+x);break;
   case 4: Write_Cmd(0x98+x);break;
      default:break;
  }
    Write_Data(00);
    Write_Data(00);
}         

/***********************************************
                  显示字符串
            x:横坐标值，范围0~8
            y:纵坐标值，范围1~4
***********************************************/
void LCD_PutString(unsigned char x,unsigned char y,unsigned char code *s)
{ 
 switch(y)
     {
   case 1: Write_Cmd(0x80+x);break;
   case 2: Write_Cmd(0x90+x);break;
   case 3: Write_Cmd(0x88+x);break;
   case 4: Write_Cmd(0x98+x);break;
      default:break;
  }
 while(*s>0)
   { 
      Write_Data(*s);
      s++;
      DelayUs2x(50);
   }
}

/***********************************************
                     清屏
***********************************************/
void ClrScreen()
{ 
   Write_Cmd(0x01);
   DelayMs(15);
}
    
/***********************************************
               调用显示更新
***********************************************/
void DisplayUpdata(void)
{   

	  ClrScreen();
LCD_PutString(0,1,TAB1);
LCD_PutString(0,2,TAB2);
LCD_PutString(0,3,TAB3);
LCD_PutString(0,4,TAB4);

 DisplayCGRAM(0,curr%4+1); 
}

/***********************************************

数值转换
***********************************************/

void Num_zhuanh(unsigned int x,unsigned char u)
{
unsigned int temp;
unsigned char disp[3];
temp=x;
disp[0]=temp/100;
disp[1]=(temp%100)/10;
disp[2]=(temp%100)%10;
//Write_Cmd(0x94);

 switch(u)
     {
   case 1: Write_Cmd(0x84);break;
   case 2: Write_Cmd(0x94);break;
   case 3: Write_Cmd(0x8C);break;
   case 4: Write_Cmd(0x9C);break;
      default:break;
  }

Write_Data(TAB6[0]);
Write_Data(TAB7[disp[0]]);
Write_Data(TAB7[disp[1]]);
Write_Data(TAB7[disp[2]]);
}




/***********************************************
                 TURN FUZ
***********************************************/

void TURN_FZ(unsigned char v)

{
int i;
unsigned char p;
p=v;
if(p)
{
   for(i=0;i<4;i++)
         {
	       turn_char[i]=TAB6[i];
	      }
}
if(!p)
{
   for(i=0;i<4;i++)
         {
	       turn_char[i]=TAB5[i];
	      }
}



Write_Cmd(0x8C);

for(i=0;i<4;i++)
{
Write_Data(turn_char[i]);

}

}




/***********************************************
                 MAIN
***********************************************/
void main()
{
   timer_num=120;
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

