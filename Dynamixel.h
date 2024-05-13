#ifndef DYNAMIXEL
#define DYNAMIXEL

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
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
	
	uint16 crc;

}dxl_packet;

typedef struct dxl
{
	uint8 bIsOpen;
	uint8 state;
	uint16 packet_length;
	uint8* param;
	size_t index;
	size_t param_index;
	uint8 param_len;
	dxl_packet packet;


	uint8 packet_buff[DLX_PACKET_BUFF_MAX];

}dxl;



enum Packet_States
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
	DXL_STATUS_CRC_L = 10,
	DXL_STATUS_CRC_H = 11,
	
};

enum Error
{
	No_Error = 0x00,
	Result_Fail = 0x01,
	Instruction_Error = 0x02,
	CRC_Error = 0x03,
	Data_Range_Error = 0x04,
	Data_Length_Error = 0x05,
	Data_Limit_Error = 0x06,
	Access_Error = 0x07,

};





//uint8 Send_Instruction(dxl* p_dxl, uint8 id, uint8 inst, uint8* p_param, uint16* param_len);
extern uint8 Receive_Status_Packet(dxl* p_dxl,uint8 rxbuff[], size_t rxbuff_size);
extern unsigned short update_crc(unsigned short crc_accum, unsigned char* data_blk_ptr, unsigned short data_blk_size);
#endif
