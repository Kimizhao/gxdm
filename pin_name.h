
#ifndef PIN_NAME_



#define DataPort P0   

/* 
 * Global variable.
 */
sbit RS = P2^4;
sbit RW = P2^5;
sbit E  = P2^6;
sbit PSB= P2^1; //串并口选择端  并高串低



sbit KEY_UP=P3^0; //按键
sbit KEY_DOWN=P3^1;
sbit KEY_TURN=P3^2;
sbit KEY_TIMER=P3^3;


unsigned char curr,currold;//全局变量，当前箭头位置
unsigned char TU;
unsigned int speed_num;
unsigned int timer_num;
unsigned char turn_char[4];
unsigned char time_num1;
unsigned char code user16x16[]={ //箭头图片
0x00,0x00,0x80,0x00,0x40,0x00,0x20,0x00,
0x10,0x00,0x08,0x00,0x04,0x00,0x02,0x00,
0x04,0x00,0x08,0x00,0x10,0x00,0x20,0x00,
0x40,0x00,0x80,0x00,0x00,0x00,0x00,0x00,
};



unsigned char code TAB1[]={"  TIMER: 065 SE2"};
unsigned char code TAB2[]={"  SPEED: 200 RPM"};
unsigned char code TAB3[]={"  TURN : CCW"};
unsigned char code TAB4[]={"  COUNT: 00"};
unsigned char code TAB5[]={" CW "};
unsigned char code TAB6[]={" CCW"};
unsigned char code TAB7[]={"0123456789"};
unsigned char code TAB8[]={">"};
#endif
