#pragma once

#include "Global_Function.h"

#include <stdlib.h>
#include <string.h>

void form_data_for_can(const struct read_dan_service* source, const int count, struct request_message* request, byte num_serv_return)
{
		free(request->m);
		request->m = (byte*)calloc(request->length, sizeof(byte));
		memcpy(&request->m[0], &num_serv_return, 1);
		int k = 1;
		int i = 0;
		while (i < count)
		{
				struct read_dan_service xx = source[i];
				memcpy(&request->m[k], &xx.pid, 1);
				k++;
				memcpy(&request->m[k], &(xx.result.b[0]), xx.length);
				k = k + xx.length;
				i++;
		}



}
