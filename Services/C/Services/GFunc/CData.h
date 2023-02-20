#pragma once

typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned long int llong;

struct ResponseMessage
{
		byte length;
		byte m[7];
};

struct RequestMessage
{
		byte length;
		byte b[100];
		byte* m;
};

//Request current
//response_message, struct iso15765_tp_s* request_message

struct ReadDanServic
{
		byte pid;
		byte length;

		union Result
		{
				byte b[4];
				word w[2];
				llong l;
		} result;
		
};
