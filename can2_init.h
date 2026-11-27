#include<lpc21xx.h>
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct CAN2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}CAN2_MSG;
void CAN2_INIT(void)
{
	PINSEL1|=0x14000;
	VPBDIV  =1;
	C2MOD   =0x01;
	AFMR    =0x02;
	C2BTR   =0X001C001D;
	C2MOD   =0X00;
}
void CAN2_TX(CAN2_MSG m)
{
	C2TID1  =m.id;
	C2TFI1  =(m.dlc<<16);
	if(m.rtr==0)
	{
		C2TFI1&=~(1<<30);
		C2TDA1 =m.byteA;
		C2TDB1 =m.byteB;
	}
	else
	{
		C2TFI1|=(1<<30);
	}
	C2CMR = (1<<0)|(1<<5);
	while(((C2GSR>>3)&1)==0);
}
void CAN2_RX(CAN2_MSG *m)
{
	while((C2GSR&0X1)==0);
	m->id  =C2RID;
	m->dlc =(C2RFS>>16)&0X0F;
	m->rtr =(C2RFS>>30)&0X1;
	if(m->rtr==0)
	{
		m->byteA = C2RDA;
		m->byteB = C2RDB;
	}
	C2CMR =1<<2;
}