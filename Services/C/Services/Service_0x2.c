#pragma once
//    ISO 15031-5 2015 стр 47
#include "Service_0x2.h"

#include "Global_Function.h"

void service_0x2(struct response_message* response, struct request_message* request)
{
		struct read_dan_service rds[1];
		auto count_byte = 1;  // NOLINT(clang-diagnostic-implicit-int)
		int k_pid = 0;

		rds[k_pid].pid = 0x2;
		rds[k_pid].length = 3;
		rds[k_pid].result.b[0] = 0x0;
		rds[k_pid].result.b[1] = 0x1;
		rds[k_pid].result.b[2] = 0x30;

		count_byte = count_byte + rds[k_pid].length;
		k_pid++;

		request->length = count_byte;  // NOLINT(clang-diagnostic-implicit-int-conversion)
		// ReSharper disable once CppIncompatiblePointerConversion
		form_data_for_can(&rds, k_pid, request, 0x42);  // NOLINT(clang-diagnostic-incompatible-pointer-types)

		return;
}