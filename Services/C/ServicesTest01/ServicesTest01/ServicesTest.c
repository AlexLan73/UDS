//#include <stdio.h>



#include "../../Services/Service_0x1.h"
#include "../../Services/Service_0x2.h"
#include "../../Services/GFunc/CData.h"

void case_request(struct response_message* response, struct request_message* request)
{
  if (response->length < 2 || response->length > 7)
    return;

  switch (response->m[0])
  {
    case 0x1:
    {
      service_0x1(response, request);
      break;
    }
    case 0x2:
    {
      service_0x2(response, request);
      break;
    }

  default:
    break;
  }
}

int main(void)      
{                   
//  printf(" --- Hello! --- \n"); 
  struct request_message request;
  const byte response_m[] = { 0x1, 0x15, 0x1, 0x5, 0x3, 0xC, 0xD };
  struct  response_message response;
  response.length = sizeof(response_m);

  for (size_t i = 0; i < response.length; i++)
    response.m[i] = response_m[i];

  request.length = 0xAA;
  request.m = (byte*)calloc(0x3, sizeof(byte));
  request.b[0] = 0x0;
  request.b[1] = 0x1;
  request.b[2] = 0x2;

  case_request(&response, &request);

	 byte dfd = 0x0;

  for (byte i = 0; i < request.length; i++)
  {
    memcpy(&dfd, &request.m[i], 1);
  }
  return 0;                     
}

