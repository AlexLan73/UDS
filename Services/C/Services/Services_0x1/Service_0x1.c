#pragma once
//  ISO 15765-4 2015 стр 91
#include "Service_0x1.h"

#include "Global_Function.h"

void service_0x1(struct response_message* response, struct request_message* request)
{
		struct read_dan_service rds[6];
		auto count_byte = response->length;  // NOLINT(clang-diagnostic-implicit-int)
		int k_pid = 0;
		for (auto i = 1; i < response->length; i++)  // NOLINT(clang-diagnostic-implicit-int)
		{
				switch (response->m[i])
				{
				case 0x0:
				{
						rds[k_pid].pid = 0x0;
						rds[k_pid].length = 4;
						rds[k_pid].result.b[0] = 0x0;
						rds[k_pid].result.b[1] = 0x1;
						rds[k_pid].result.b[2] = 0x2;
						rds[k_pid].result.b[3] = 0x3;
						count_byte = count_byte + rds[k_pid].length;
						break;
				}
				case 0x1:
				{
						rds[k_pid].pid = 0x1;
						rds[k_pid].length = 4;
						rds[k_pid].result.b[0] = 0x10;
						rds[k_pid].result.b[1] = 0x11;
						rds[k_pid].result.b[2] = 0x12;
						rds[k_pid].result.b[3] = 0x13;
						count_byte = count_byte + rds[k_pid].length;
						break;
				}
				case 0x2:
				{
						// читаем данные
						break;
				}
				case 0x3:
				{
						rds[k_pid].pid = 0x3;
						rds[k_pid].length = 3;
						rds[k_pid].result.b[0] = 3;
						rds[k_pid].result.b[1] = 13;
						rds[k_pid].result.b[2] = 23;
						count_byte = count_byte + rds[k_pid].length;
						break;
				}
				case 0x4:
				{
						// читаем данные
						break;
				}
				case 0x5:
				{
						rds[k_pid].pid = 0x5;
						rds[k_pid].length = 1;
						rds[k_pid].result.b[0] = 5;
						count_byte = count_byte + rds[k_pid].length;
						break;
				}
				case 0x6:  // NOLINT(bugprone-branch-clone)
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
						rds[k_pid].pid = 0xC;
						rds[k_pid].length = 4;
						rds[k_pid].result.l[0] = 0xC;
						count_byte = count_byte + rds[k_pid].length;
						break;
				}
				case 0xD:
				{
						struct read_dan_service _rds;
						_rds.pid = 0xD;
						_rds.length = 4;
						_rds.result.l[0] = 0xF;
						rds[k_pid] = _rds;
						count_byte = count_byte + _rds.length;
						break;
				}
				case 0xE:  // NOLINT(bugprone-branch-clone)
				{
						break;
				}
				case 0xF:
				{
						break;
				}

				case 0x15:
				{
						rds[k_pid].pid = 0x15;
						rds[k_pid].length = 2;
						rds[k_pid].result.w[0] = 0x15;
						count_byte = count_byte + rds[k_pid].length;
						break;
				}
				case 0x19:
				{
						rds[k_pid].pid = 0x19;
						rds[k_pid].length = 2;
						rds[k_pid].result.b[0] = 0x19;
						rds[k_pid].result.b[1] = 0x1A;
						count_byte = count_byte + rds[k_pid].length;
						break;
				}

				case 0x20:
				{
						rds[k_pid].pid = 0x20;
						rds[k_pid].length = 4;
						rds[k_pid].result.b[0] = 0x20;
						rds[k_pid].result.b[1] = 0x21;
						rds[k_pid].result.b[2] = 0x22;
						rds[k_pid].result.b[3] = 0x23;
						count_byte = count_byte + rds[k_pid].length;
						break;
				}

				default:
						break;
				}
				k_pid++;
		}
		request->length = count_byte;  // NOLINT(clang-diagnostic-implicit-int-conversion)
		// ReSharper disable once CppIncompatiblePointerConversion
		form_data_for_can(&rds, k_pid, request, 0x41);  // NOLINT(clang-diagnostic-incompatible-pointer-types)

		return;
}