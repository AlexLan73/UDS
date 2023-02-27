#pragma once
#include <stdlib.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <string.h>
#include <cstdint>

//typedef unsigned char byte;
//typedef unsigned int word;
//typedef unsigned long int longs;

namespace uds 
{
		using namespace std;

		struct response_message
		{
				uint8_t length;
				uint8_t m[7];
		};

		struct request_message
		{
				uint8_t length;
				uint8_t b[100];
				uint8_t* m;
		};

		struct read_dan_service
		{
				uint8_t pid;
				uint8_t length;

				union result
				{
						uint8_t b[8];
						uint16_t w[4];
						uint32_t l[2];
				} result;

		};

}
