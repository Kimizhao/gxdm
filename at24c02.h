/*************************************************
 *
 *
 *
 ************************************************/
#ifndef __AT24C02_H__
#define __AT24C02_H__
/*************************************************/

void mDelay(unsigned char j);
void WrToROM(unsigned char Data[],unsigned char Address,unsigned char Num);//-->
//void WritePageToROM(unsigned char Data[],unsigned char Address);//-->
void RdFromROM(unsigned char Data[],unsigned char Address,unsigned char Num);//-->
//void RandomRdFromROM(unsigned char *Data,unsigned char Address);//-->
//void RdCurAddrFromROM(unsigned char *Data);
//void SeqRdCurAddrFromROM(unsigned char Data[],unsigned char Address, unsigned char Num);

/* 
 * gAddr_1 --> timer_Low
 *    	+1 --> timer_Hight
 *	  	+2 --> speed_Low
 *	  	+3 --> speed_Hight
 *	  	+4 --> turn
 * gAddr_2 --> timer_Low
 *    	+1 --> timer_Hight
 *	  	+2 --> speed_Low
 *	  	+3 --> speed_Hight
 *	  	+4 --> turn
 *    	..
 *	   	n
 */
void WriteToROM(unsigned int timer, unsigned int speed, unsigned char turn, unsigned char gAddr);
void ReadFromROM(unsigned int *timer, unsigned int *speed, unsigned char *turn, unsigned char gAddr);

#endif /* __AT24C02_H__ */