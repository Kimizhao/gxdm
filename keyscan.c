#include "scaner.h"
uchar keyscan(void)//����ɨ�躯����ʹ�����з�תɨ�跨 ���磺��Ϊ�͵�λ����Ϊ����λ
{
	uchar cord_h,cord_l;//����ֵ
	P3=0x0f;            //�������ȫΪ0
	cord_h=P3&0x0f;     //��������ֵ
	
	if(cord_h!=0x0f)    //�ȼ�����ް�������
	{
		delay(100);        //ȥ��
		if(cord_h!=0x0f)
		{
			cord_h=P3&0x0f; //��������ֵ
			P3=cord_h|0xf0; //�����ǰ����ֵ
			cord_l=P3&0xf0; //��������ֵ
			return(cord_h+cord_l);//������������ֵ
		}
		
	}
	
	return(0xff);     //���ظ�ֵ
}

void delay(uint i)//��ʱ����
{
	while(i--);
}