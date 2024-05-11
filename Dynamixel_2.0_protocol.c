#include "Dynamixel.h"

uint8 Receive_Status_Packet(dxl* p_dxl, uint8 rxbuff[], size_t rxbuff_size)
{
	uint16 param_lenght = 0;
	uint16 packet_length = 0;

	p_dxl->state = NULL;
	for (size_t i = 0; i < rxbuff_size; ++i)
	{
		switch (p_dxl->state)
		{
			case DXL_STATUS_HEADER1:
				if (rxbuff[i] == 0xFF)
				{
					p_dxl->packet_buff[DXL_STATUS_HEADER1] = rxbuff[i];
					p_dxl->state = DXL_STATUS_HEADER2;
					p_dxl->packet.header1 = rxbuff[i];
				}
				break;

			case DXL_STATUS_HEADER2:
				if (rxbuff[i] == 0xFF)
				{
					p_dxl->packet_buff[DXL_STATUS_HEADER2] = rxbuff[i];
					p_dxl->state = DXL_STATUS_HEADER3;
					p_dxl->packet.header2 = rxbuff[i];
				}
				else
				{
					p_dxl->state = DXL_STATUS_HEADER1;
				}
				break;

			case DXL_STATUS_HEADER3:
				if (rxbuff[i] == 0xFF)
				{
					p_dxl->packet_buff[DXL_STATUS_HEADER3] = rxbuff[i];
					p_dxl->state = DXL_STATUS_RESERVED;
					p_dxl->packet.header3 = rxbuff[i];
				}
				else
				{
					p_dxl->state = DXL_STATUS_HEADER1;
				}
				break;

			case DXL_STATUS_RESERVED:
				if (rxbuff[i] == 0x00)
				{
					p_dxl->packet_buff[DXL_STATUS_RESERVED] = rxbuff[i];
					p_dxl->state = DXL_STATUS_ID;
					p_dxl->packet.reserved = rxbuff[i];
				}
				break;

			case DXL_STATUS_ID:
				p_dxl->packet_buff[DXL_STATUS_ID] = rxbuff[i];
				p_dxl->state = DXL_STATUS_Len1;
				p_dxl->packet.id = rxbuff[i];
				break;

			case DXL_STATUS_Len1:
				p_dxl->packet_buff[DXL_STATUS_Len1] = rxbuff[i];
				p_dxl->state = DXL_STATUS_Len2;
				p_dxl->packet.length_l = rxbuff[i];
				break;

			case DXL_STATUS_Len2:
				p_dxl->packet_buff[DXL_STATUS_Len2] = rxbuff[i];
				p_dxl->state = DXL_STATUS_Inst;
				p_dxl->packet.lenght_h = rxbuff[i];
				break;

			case DXL_STATUS_Inst:
				packet_length = (uint16)p_dxl->packet_buff[DXL_STATUS_Len1];
				packet_length = (uint16)p_dxl->packet_buff[DXL_STATUS_Len1] << 8;
				if (p_dxl->packet_buff[DXL_STATUS_Inst] == 0x55)
				{
					p_dxl->packet_buff[DXL_STATUS_Inst] = rxbuff[i];
					param_lenght = packet_length - 4;
				}




		}	
				
	}
}
