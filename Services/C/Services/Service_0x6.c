#pragma once
//  ISO 15765-4 2015 стр 91
#include "Service_0x6.h"

#include "Global_Function.h"

void service_0x6(struct response_message* response, struct request_message* request)
{
//		struct read_dan_service rds[1];
		auto count_byte = 0;  // NOLINT(clang-diagnostic-implicit-int)
		free(request->m);

		if (response->m[1] == 0x0)
		{
				request->length = 0;
				return;
		}

		byte m0[7];
		m0[0] = 0x46;
		m0[1] = response->m[1];	// PID

//		request->m = (byte*)calloc(count_byte, sizeof(byte));

		switch (response->m[1]) // Test ID
		{
				case 0x1:
				{
						m0[2] = 0x1;
						m0[3] = 0x1;
						m0[4] = 0x11;
						m0[5] = 0x21;
						m0[6] = 0x31;
						request->length = 7;
						break;
				}
				case 0x2:
				{
						m0[2] = 0x21;
						m0[3] = 0x31;
						m0[4] = 0x41;
						m0[5] = 0x51;
						m0[6] = 0x61;
						request->length = 7;
						break;
				}
				default:
						request->length = 0;
						return;
		}

//		free(request->m);
		request->m = (byte*)calloc(request->length, sizeof(byte));
		memcpy(&request->m[0], &m0[0], request->length);
		return;
}


