#pragma once
//  ISO 15765-4 2015 стр 91
#include "Service_0x5.h"

#include "Global_Function.h"

void service_0x5(struct response_message* response, struct request_message* request)
{
//		struct read_dan_service rds[1];
//		auto count_byte = 0;  // NOLINT(clang-diagnostic-implicit-int)
		free(request->m);

		byte m0[6];
		m0[0] = 0x45;
//		request->m = (byte*)calloc(count_byte, sizeof(byte));

		m0[1] = response->m[1];

		switch (response->m[1]) // Test ID
		{
				case 0x1:
				{
						m0[2] = response->m[2];

						if (response->m[2] == 1) 
						{
								m0[3] = 0x11;
								request->length = 4;

						}else if(response->m[2] == 2)
						{
								m0[3] = 0x21;
								request->length = 4;
						}
						break;
				}
				case 0x5:
				{
						m0[2] = response->m[2];

						if (response->m[2] == 1)
						{
								m0[3] = 0x51;
								m0[4] = 0x52;
								m0[5] = 0x53;
								request->length = 6;
						}
						break;
				}
						default:
								request->length = 0;
								return;
								break;

		}

//		free(request->m);
		request->m = (byte*)calloc(request->length, sizeof(byte));
		memcpy(&request->m[0], &m0[0], request->length);
		return;
}


