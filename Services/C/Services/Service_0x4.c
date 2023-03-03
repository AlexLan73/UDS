#pragma once
//    ISO 15031-5 2015 стр 47
#include "Service_0x4.h"

#include "Global_Function.h"

void service_0x4(struct response_message* response, struct request_message* request)
{
		struct read_dan_service rds[1];
		auto count_byte = 1;  // NOLINT(clang-diagnostic-implicit-int)
		rds[0].result.b[0] = 0x44;

		free(request->m);
		byte num_serv_return = 0x44;
		request->m = (byte*)calloc(count_byte, sizeof(byte));
		memcpy(&request->m[0], &num_serv_return, 1);
		request->length = count_byte;
		return;
}