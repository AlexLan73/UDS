#pragma once
//  ISO 15765-4 2015 стр 91
#include "Service_0x1.h"

void service_0x1(struct ResponseMessage* response, struct RequestMessage* request)
{
		auto count_pid = response->length - 1;
		
		struct ReadDanServic rds[6];
		auto count_byte = 1 + count_pid;
		int k_pid = 0;
		for (auto i = 1; i < response->length; i++)
		{
				switch (response->m[i])
				{
						case 0x0:
						{
								// читаем данные
								break;
						}
						case 0x1:
						{
								struct ReadDanServic _rds;
								_rds.pid = 0x1;
								_rds.length = 1;
								_rds.result.b[0] = 1;
								rds[k_pid] = _rds;
								count_byte = count_byte + _rds.length;
								break;
						}
						case 0x2:
						{
								// читаем данные
								break;
						}
						case 0x3:
						{
								struct ReadDanServic _rds;
								_rds.pid = 0x3;
								_rds.length = 3;
								_rds.result.b[0] = 3;
								_rds.result.b[1] = 13;
								_rds.result.b[2] = 23;
								rds[k_pid] = _rds;
								count_byte = count_byte + _rds.length;
								break;
						}
						case 0x4:
						{
								// читаем данные
								break;
						}
						case 0x5:
						{
								struct ReadDanServic _rds;
								_rds.pid = 0x5;
								_rds.length = 1;
								_rds.result.b[0] = 5;
								rds[k_pid] = _rds;
								count_byte = count_byte + _rds.length;
								break;
						}
						case 0x6:
						{
								// читаем данные
								break;
						}
						case 0x7:
						{
								// читаем данные
								break;
						}
						case 0x8:
						{
								// читаем данные
								break;
						}
						case 0x9:
						{
								// читаем данные
								break;
						}
						case 0xA:
						{
								// читаем данные
								break;
						}
						case 0xB:
						{
								// читаем данные
								break;
						}
						case 0xC:
						{
								struct ReadDanServic _rds;
								_rds.pid = 0xC;
								_rds.length = 4;
								_rds.result.l = 0xC;
								rds[k_pid] = _rds;
								count_byte = count_byte + _rds.length;
								break;
						}
						case 0xD:
						{
								struct ReadDanServic _rds;
								_rds.pid = 0xD;
								_rds.length = 4;
								_rds.result.l = 0xF;
								rds[k_pid] = _rds;
								count_byte = count_byte + _rds.length;
								break;
						}
						case 0xE:
						{
								// читаем данные
								break;
						}
						case 0xF:
						{
								// читаем данные
								break;
						}

						case 0x15:
						{
								struct ReadDanServic _rds;
								_rds.pid = 0x15;
								_rds.length = 2;
								_rds.result.w[0] = 0x15;
								rds[k_pid] = _rds;
								count_byte = count_byte + _rds.length;
								break;
						}

						default:
								break;
				}
				k_pid++;
		}

		request->length = count_byte;
		request->b = malloc(count_byte * sizeof(byte));
		byte* byte_prn = &request->b;

		byte bserv = 0x41;
		memcpy(&byte_prn, &bserv, 1);
		int k = 1;
		int i = 0;
		while (i< k_pid)
		{
				memcpy(&(byte_prn[k]), &rds[i].pid, 1);
				k++;
				memcpy(&(byte_prn[k]), &(rds[i].result.b[0]), rds[i].length);
				k = k + rds[i].length;
				i++;
		}

		for (byte i = 0; i < request.length; i++)
		{
				byte b_pid = 0xFF;
				//    byte* d_ptr = &(request.b[i]);
				byte* d_ptr = &(request);
				memcpy(&b_pid, &d_ptr, 1);
				int fff = 1;
		}


}


/*
//		auto byte_prn = sizeof(struct ReadDanServic);
//		rds = (struct ReadDanServic*)malloc(count_pid * sizeof(struct ReadDanServic));

*/