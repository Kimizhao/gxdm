#include <reg52.h>
#include <intrins.h>

sbit RS = P2^4;
sbit RW = P2^5;
sbit E  = P2^6;
sbit PSB= P2^1; //������ѡ���  ���ߴ���
#define DataPort P0   

sbit KEY_UP=P3^0; //����
sbit KEY_DOWN=P3^1;
sbit KEY_TURN=P3^2;
sbit KEY_TIMER=P3^3;

unsigned char curr,currold;//ȫ�ֱ�������ǰ��ͷλ��
unsigned char TU;
unsigned int speed_num;
unsigned int timer_num;
unsigned char turn_char[4];



unsigned char code user16x16[]={ //��ͷͼƬ
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
                  ��ʱ����
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
                ��æ����
***********************************************/
void Check_Busy()
{  
    RS=0;  //д����
    RW=1;  //��״̬
    E=1;
    DataPort=0xff;
    while((DataPort&0x80)==0x80);//æ��ȴ�
    E=0;
}

/***********************************************
                д������
***********************************************/
void Write_Cmd(unsigned char Cmd)
{
 Check_Busy();
 RS=0;  //д����
 RW=0;  //write
 E=1;
 DataPort=Cmd;
 DelayUs2x(5);
 E=0;
 DelayUs2x(5);
}

/***********************************************
                 д������
***********************************************/
void Write_Data(unsigned char Data)
{
 Check_Busy();
 RS=1; //д����
 RW=0; //write
 E=1;
 DataPort=Data;
 DelayUs2x(5);
 E=0;
 DelayUs2x(5);
}

/***********************************************
               Һ������ʼ��
***********************************************/
void Init_ST7920()
{  
   DelayMs(40);           //����40MS����ʱ����
   PSB=1;                 //����Ϊ8BIT���ڹ���ģʽ
   DelayMs(1);            //��ʱ
   Write_Cmd(0x30);       //ѡ�����ָ�
   DelayUs2x(50);         //��ʱ����100us
   Write_Cmd(0x30);       //ѡ��8bit������
   DelayUs2x(20);         //��ʱ����37us
   Write_Cmd(0x0c);       //����ʾ(���αꡢ������)
   DelayUs2x(50);         //��ʱ����100us
   Write_Cmd(0x01);       //�����ʾ�������趨��ַָ��Ϊ00H
   DelayMs(15);           //��ʱ����10ms
   Write_Cmd(0x06);       //ָ�������ϵĶ�ȡ��д��ʱ���趨�α���ƶ�����ָ����ʾ����λ�������������1λ�ƶ�
   DelayUs2x(50);         //��ʱ����100us
}

/***********************************************
                �û��Զ����ַ�
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
               ��ʾ�û��Զ����ַ�
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
                  ��ʾ�ַ���
            x:������ֵ����Χ0~8
            y:������ֵ����Χ1~4
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
                     ����
***********************************************/
void ClrScreen()
{ 
   Write_Cmd(0x01);
   DelayMs(15);
}
    
/***********************************************
               ������ʾ����
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

��ֵת��
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

