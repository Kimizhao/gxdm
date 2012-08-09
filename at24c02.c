/*copyright 2007,ShangHai  HaoTun Electronic Technology co.,Ltd
 *
 *This sample is used for EEPROM 24C02 Read and Write.
 *
 *write by Shifang 2007-4-29
 *
 *V1.1
 * Modified by Kimi 20120806
 */
#include "common.h"

#define AddWr 0xae //Write Address
#define AddRd 0xaf //Read Address

/* 
 * Global variable.
 */
sbit Sda=P1^2;
sbit Scl=P1^1;
/* No connect here- WP=0 */

void mDelay(unsigned char j)
{
	unsigned int i;
	for(;j>0;j--){
	for(i=0;i<125;i++){
			;
		}
	}
}

void Start(void)
{
	Sda=1;
	_nop_();_nop_();
	Scl=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	Sda=0;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	Scl=0;
}

void Stop(void)
{
	Sda=0;
	_nop_();
	Scl=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	Sda=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	Scl=0;
}

void Ack(void)
{
	Sda=0;
	_nop_();_nop_();_nop_();
	Scl=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	Scl=0;
	_nop_();_nop_();
}

void NoAck(void)
{
	Sda=1;
	_nop_();_nop_();_nop_();
	Scl=1;
	_nop_();_nop_();_nop_();_nop_();_nop_();
	Scl=0;
	_nop_();_nop_();
}

void Send(unsigned char Data)
{ 
	unsigned char BitCounter=8;
	unsigned char temp;

	do {
		temp=Data;
		Scl=0;
		_nop_();_nop_();_nop_();_nop_();_nop_();
		if((temp&0x80)==0x80)
			Sda=1;
		else
			Sda=0;


		Scl=1;
		temp=Data<<1;
		Data=temp;
		BitCounter--;
	} while(BitCounter);
	
	Scl=0;
}

unsigned char Read(void)
{
	unsigned char temp=0;
	unsigned char temp1=0;
	unsigned char BitCounter=8;

	Sda=1;
	do {
		Scl=0;
		_nop_();_nop_();_nop_();_nop_();_nop_();
		Scl=1;
		_nop_();_nop_();_nop_();_nop_();_nop_();
		if(Sda)
			temp=temp|0x01;
		else
			temp=temp&0xfe;

		if(BitCounter-1){
			temp1=temp<<1;
			temp=temp1;
		}
		
		BitCounter--;
	} while(BitCounter);
	
	return(temp);
}

/*
 * Discription: Write datas to EEPROM.
 * Data[]: datas
 * Address: subaddress = 0
 * Num: size of Data[]
 * example: WrToROM(Number,0,5)
 */
void WrToROM(unsigned char Data[],unsigned char Address,unsigned char Num)
{
	unsigned char i;
	unsigned char *PData;
	PData=Data;
	for(i=0;i<Num;i++) {
		Start();
		Send(AddWr);
		Ack();
		Send(Address+i);
		Ack();
		Send(*(PData+i));
		Ack();
		Stop();
		mDelay(20);
	}
}

/*
 * Discription: Write datas to EEPROM(Page write).
 * Data[]: datas(at24c02 8-Bytes/page)
 * Address: Word Address
 */
/* void WritePageToROM(unsigned char Data[],unsigned char Address)
{
	unsigned char i;
	unsigned char *PData;
    unsigned char Num = 8;
	PData=Data;

    Start();
    Send(AddWr);
    Ack();
    Send(Address);
    Ack();
        
	for(i=0;i<Num;i++) {
		Send(*(PData+i));
		Ack();
	}
    
    Stop();
	mDelay(20);
} */

/*
 * Discription: Read datas from EEPROM.
 * Data[]: datas
 * Address: Word Address
 * Num: size of Data[]
 * Example: RdFromROM(Number,0,5)
 */
void RdFromROM(unsigned char Data[],unsigned char Address,unsigned char Num)
{
	unsigned char i;
	unsigned char *PData;
	PData=Data;
	for(i=0;i<Num;i++) {
		Start();
		Send(AddWr);
		Ack();
		Send(Address+i);
		Ack();
		Start();
		Send(AddRd);
		Ack();
		*(PData+i)=Read();
		Scl=0;
		NoAck();
		Stop();
	}
}

/*
 * Discription: Read data from EEPROM(Random read).
 * Data: datas Random read
 * Address: Word Address
 */
/* void RandomRdFromROM(unsigned char *Data,unsigned char Address)
{
	unsigned char *PData;
	PData=Data;

    Start();
    Send(AddWr);
    Ack();
    Send(Address);
    Ack();
    Start();
    Send(AddRd);
    Ack();
    *PData=Read();
    Scl=0;
    NoAck();
    Stop();

} */

/*
 * Discription: Read Currend address data from EEPROM.
 * Data[]: datas read
 */
/* void RdCurAddrFromROM(unsigned char *Data)
{
	unsigned char *PData;
	PData=Data;

    Start();
    Send(AddRd);
    Ack();
    *(PData)=Read();
    Scl=0;
    NoAck();
    Stop();

} */

/*
 * Discription: Sequential read currned address data(n) from EEPROM.
 * Data[]: Sequential datas read.
 */
/* void SeqRdCurAddrFromROM(unsigned char Data[],unsigned char Address, unsigned char Num)
{
	unsigned char i;
    unsigned char *PData;
	PData=Data;

    Start();
    Send(AddWr);
    Ack();
	Send(Address);
	Ack();
	Start();
	Send(AddRd);
	Ack();
    for(i=0; i < Num; i++){
        *(PData+i)=Read();
        Scl=0;
    }
    
    NoAck();
    Stop();
} */

/*
 */
void WriteToROM(unsigned int timer, unsigned int speed, unsigned char turn, unsigned char gAddr)
{
	unsigned char tm[2],sp[2],tu;
	
	tm[0]=timer&0x00ff;
	tm[1]=timer>>8;
	
	sp[0]=speed&0x00ff;
	sp[1]=speed>>8;
	
	tu=turn;
	
	WrToROM(tm,gAddr,2);
	WrToROM(sp,gAddr+2,2);
	WrToROM(&tu,gAddr+4,1);

}

/*
 */
void ReadFromROM(unsigned int *timer, unsigned int *speed, unsigned char *turn, unsigned char gAddr)
{
	unsigned char tm2[2],sp2[2],tu2;
	
	RdFromROM(tm2,gAddr,2);
	RdFromROM(sp2,gAddr+2,2);
	RdFromROM(&tu2,gAddr+4,1);
	
	*timer=tm2[0]+tm2[1]*256;
	*speed=sp2[0]+sp2[1]*256;
	*turn=tu2;
	
	/* temp3=temp1+temp2<<8;
	timer=&temp3; */

}
