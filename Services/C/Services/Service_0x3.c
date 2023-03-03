#pragma once
//    ISO 15031-5 2015 стр 47
#include "Service_0x3.h"

#include "Global_Function.h"

void service_0x3(struct response_message* response, struct request_message* request)
{
		struct read_dan_service rds[1];
		auto count_byte = 1;  // NOLINT(clang-diagnostic-implicit-int)
		int k_pid = 0;

		//rds[k_pid].pid = 0x3;
		//rds[k_pid].length = 6;
		rds[k_pid].result.w[0] = 0x0;
		rds[k_pid].result.w[1] = 0x1;
		rds[k_pid].result.w[2] = 0x2;

		count_byte = 7;

		free(request->m);
		byte num_serv_return = 0x43;
		request->m = (byte*)calloc(count_byte, sizeof(byte));
		memcpy(&request->m[0], &num_serv_return, 1);
		memcpy(&request->m[1], &(rds[0].result.b[0]), 6);
		request->length = count_byte;
		return;
}