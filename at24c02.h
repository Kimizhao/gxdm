/*************************************************
 *
 *
 *
 ************************************************/
#ifndef __AT24C02_H__
#define __AT24C02_H__
/*************************************************/
#include <reg52.h>
#include <intrins.h>

#define AddWr 0xae //Write Address
#define AddRd 0xaf //Read Address

/* 
 * Global variable.
 */
sbit Sda=P1^2;
sbit Scl=P1^1;
/* No connect here- WP=0 */
sbit WP=P1^0;
void mDelay(unsigned char j);
void WrToROM(unsigned char Data[],unsigned char Address,unsigned char Num);
void RdFromROM(unsigned char Data[],unsigned char Address,unsigned char Num);

#endif /* __AT24C02_H__ */