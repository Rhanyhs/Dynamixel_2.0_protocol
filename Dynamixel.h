#ifndef DYNAMIXEL
#define DYNAMIXEL

#include <stdlib.h>
#include <stdint.h>
#define DLX_PACKET_BUFF_MAX	100
typedef uint8_t uint8;
typedef uint16_t uint16;

typedef struct dxl_packet
{
	uint8 header1;
	uint8 header2;
	uint8 header3;
	uint8 reserved;
	uint8 id;
	uint8 length_l;
	uint8 lenght_h;  //tek bir uint16 tipinde lenght te olabilir kararsýz kaldým
	uint8 inst;
	uint8 err;
	uint16 param_len;
	uint8* param;

}dxl_packet;

typedef struct dxl
{
	uint8 bIsOpen;
	uint8 state;
	uint8 is_status_packet;
	dxl_packet packet;

	uint8 packet_buff[DLX_PACKET_BUFF_MAX];

}dxl;



enum Packet_Bytes
{
	DXL_STATUS_HEADER1 = 0,
	DXL_STATUS_HEADER2 = 1,
	DXL_STATUS_HEADER3 = 2,
	DXL_STATUS_RESERVED = 3,
	DXL_STATUS_ID = 4,
	DXL_STATUS_Len1 = 5,
	DXL_STATUS_Len2 = 6,
	DXL_STATUS_Inst = 7,
	DXL_STATUS_Err = 8,
	DXL_STATUS_Param = 9,
	
};





uint8 Send_Instruction(dxl* p_dxl, uint8 id, uint8 inst, uint8* p_param, uint16* param_len);
uint8 Receive_Status_Packet(dxl* p_dxl,uint8 rxbuff[]);

#endif
