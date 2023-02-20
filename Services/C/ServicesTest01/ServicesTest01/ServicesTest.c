#include <stdio.h>
#include "..\..\Services\Services_0x1\Service_0x1.h"
#include "..\..\Services\GFunc\CData.h"

void case_request(struct ResponseMessage* response, struct RequestMessage* request)
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
  default:
    break;
  }
}

int main(void)      
{                   
  printf(" --- Hello! --- \n"); 
  struct RequestMessage request;
  byte responseM[] = { 0x1, 0x15, 0x1, 0x5, 0x3, 0xC, 0xD };
  struct  ResponseMessage response;
  response.length = sizeof(responseM);

  for (size_t i = 0; i < response.length; i++)
    response.m[i] = responseM[i];

  request.length = 0xAA;
  request.m = (byte*) malloc(0xFF * sizeof(byte));
  request.b[0] = 0x0;
  request.b[1] = 0x1;
  request.b[2] = 0x2;
  struct RequestMessage* request_prn = &request;

  byte dfd =0x10;
  byte* m_prn = &(request.m[0]);
  memcpy(&m_prn, &dfd, 1);
  dfd = 0x20;
  //m_prn = &(request_prn->m[1]);
  m_prn = (*m_prn + 1); //&(request_prn->m[1]);
  memcpy(&(m_prn), &dfd, 1);
  dfd = 0x30;
  //memcpy(&request.m[2], &dfd, 1);
  ////dfd = 0x10;
  //memcpy(&request.m[3], &dfd, 1);
  ////dfd = 0x50;
  //memcpy(&request.m[4], &dfd, 1);

//  struct RequestMessage *request_prn = &request;
//  auto xx = sizeof(request);
  case_request(&response, &request);

  for (byte i = 0; i < request.length; i++)
  {
    byte b_pid = 0xFF;
//    byte* d_ptr = &(request.b[i]);
    byte d_ptr = request.b[i];
//    memcpy(&b_pid, &(request.b[i]), 1);
    int fff = 1;
  }
  //				struct ReadDanServic z = rds[i];
  ////				byte_prn[i] = z.pid;
  //				byte bb = i;
  //				byte* byte_prn0 =&( byte_prn[i]);
  //				memcpy(&byte_prn0, &bb, 1);
  //
  ////				memcpy(queue->data[queue->last].bytes, data, PT_PAR_QUEUE_ELEMENT_SIZE); //dst src len
  ////				queue->data[queue->last].id = id;
  ////				queue->size++;
  //
  //				byte xxx;
  //
  //				memcpy(&xxx, &byte_prn0, 1);
  //
  ////				auto xxx = byte_prn[i];
  //				int hh = 1;
  //
  ////				auto z_l = ( z).
  //		}





  return 0;                     
}


//  int count1 = sizeof(m) / sizeof(unsigned char) - 1;
//  int count = sizeof(m); /// sizeof(m[0]);
  //for (int i = 0; i < count; i++) 
  //{
  //  auto x = m[i];
  //  int j = 1;
  //}
