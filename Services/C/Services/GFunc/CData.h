#pragma once
#include <stdlib.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <string.h>

typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long int longs;

struct response_message
{
		byte length;
		byte m[7];
};

struct request_message
{
		byte length;
		byte b[100];
		byte* m;
};

struct read_dan_service
{
		byte pid;
		byte length;

		union result
		{
				byte b[8];
				word w[4];
				longs l[2];
		} result;
		
};
