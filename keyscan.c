#include "scaner.h"
uchar keyscan(void)//键盘扫描函数，使用行列反转扫描法 比如：行为低电位，列为高四位
{
	uchar cord_h,cord_l;//行列值
	P3=0x0f;            //行线输出全为0
	cord_h=P3&0x0f;     //读入列线值
	
	if(cord_h!=0x0f)    //先检测有无按键按下
	{
		delay(100);        //去抖
		if(cord_h!=0x0f)
		{
			cord_h=P3&0x0f; //读入列线值
			P3=cord_h|0xf0; //输出当前列线值
			cord_l=P3&0xf0; //读入行线值
			return(cord_h+cord_l);//键盘最后组合码值
		}
		
	}
	
	return(0xff);     //返回该值
}

void delay(uint i)//延时函数
{
	while(i--);
}