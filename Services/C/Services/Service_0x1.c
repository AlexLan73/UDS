#pragma once
//  ISO 15765-4 2015 ??? 91
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
						break;
				}
				case 0x2:
				{
						// ?????? ??????
						break;
				}
				case 0x3:
				{
						rds[k_pid].pid = 0x3;
						rds[k_pid].length = 3;
						rds[k_pid].result.b[0] = 3;
						rds[k_pid].result.b[1] = 13;
						rds[k_pid].result.b[2] = 23;
						break;
				}
				case 0x4:
				{
						// ?????? ??????
						break;
				}
				case 0x5:
				{
						rds[k_pid].pid = 0x5;
						rds[k_pid].length = 1;
						rds[k_pid].result.b[0] = 5;
						break;
				}
				case 0x6:  // NOLINT(bugprone-branch-clone)
				{
						// ?????? ??????
						break;
				}
				case 0x7:
				{
						// ?????? ??????
						break;
				}
				case 0x8:
				{
						// ?????? ??????
						break;
				}
				case 0x9:
				{
						// ?????? ??????
						break;
				}
				case 0xA:
				{
						// ?????? ??????
						break;
				}
				case 0xB:
				{
						// ?????? ??????
						break;
				}
				case 0xC:
				{
						rds[k_pid].pid = 0xC;
						rds[k_pid].length = 4;
						rds[k_pid].result.l[0] = 0xC;
						break;
				}
				case 0xD:
				{
						rds[k_pid].pid = 0xD;
						rds[k_pid].length = 4;
						rds[k_pid].result.l[0] = 0xD;
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
						break;
				}
				case 0x19:
				{
						rds[k_pid].pid = 0x19;
						rds[k_pid].length = 2;
						rds[k_pid].result.b[0] = 0x19;
						rds[k_pid].result.b[1] = 0x1A;
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
						break;
				}

				case 0x21:
				{
						rds[k_pid].pid = 0x21;
						rds[k_pid].length = 1;
						rds[k_pid].result.b[0] = 0x21;
						break;
				}

				case 0x30:
				{
						rds[k_pid].pid = 0x30;
						rds[k_pid].length = 1;
						rds[k_pid].result.b[0] = 0x30;
						break;
				}

				case 0x31:
				{
						rds[k_pid].pid = 0x31;
						rds[k_pid].length = 1;
						rds[k_pid].result.b[0] = 0x31;
						break;
				}

				case 0x4D:
				{
						rds[k_pid].pid = 0x4D;
						rds[k_pid].length = 1;
						rds[k_pid].result.b[0] = 0x4D;
						break;
				}

				case 0x4E:
				{
						rds[k_pid].pid = 0x4E;
						rds[k_pid].length = 1;
						rds[k_pid].result.b[0] = 0x4E;
						break;
				}

				default:
						break;
				}
				count_byte = count_byte + rds[k_pid].length;
				k_pid++;
		}
		request->length = count_byte;  // NOLINT(clang-diagnostic-implicit-int-conversion)
		// ReSharper disable once CppIncompatiblePointerConversion
		form_data_for_can(&rds, k_pid, request, 0x41);  // NOLINT(clang-diagnostic-incompatible-pointer-types)

		return;
}