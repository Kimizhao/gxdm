/*copyright 2007,ShangHai  HaoTun Electronic Technology co.,Ltd
 *
 *This sample is used for EEPROM 24C02 Read and Write.
 *
 *write by Shifang 2007-4-29
 *
 *V1.1
 * Modified by Kimi 20120806
 */
#include "at24c02.h"

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
 * Discription: Read datas from EEPROM.
 * Data[]: datas read
 * Address: subaddress = 0
 * Num: size of Data[]
 * example: RdFromROM(Number,0,5)
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


/* Useage.
void main()
{
	unsigned char Number[5]={0x06,0x5b,0x4f,0x66,0x5b};
	unsigned char i;
	WP=0;
	P2=0x00;

	WrToROM(Number,0,5);
	mDelay(200);
	Number[0]=0;
	Number[1]=0;
	Number[2]=0;
	Number[3]=0;
	Number[4]=0;
	RdFromROM(Number,0,5);

	while(1) { 

		P0=Number[i];
		mDelay(200);
		mDelay(200);
		i++;
		if(i==5)
		i=0;
	}

}
 */