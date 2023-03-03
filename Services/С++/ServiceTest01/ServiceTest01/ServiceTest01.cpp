
#include <iostream>
#include <map>
#include "../Service/ServiceBase.h"
#include "../Service/CData.h"
#include "../Service/GetServices.h"
#define CountRequest 8;

using namespace std;


int main()
{

  uint8_t* m = new uint8_t[10];

  std::cout << "Hello World!\n";
  uds::request_message request;
  const uint8_t response_m[] = {0x1, 0x15, 0x1, 0x5, 0x3, 0xC, 0xD };
  uds::response_message response{};
  response.length = sizeof(response_m);
  for (size_t i = 0; i < response.length; i++)
    response.m[i] = response_m[i];

  auto _get_service = uds::GetServices();
  _get_service.get_servise_request(&response, &request);

  int jj = 0;
//  auto _service = uds::ServiceBase();

  //request.length = 0xAA;
  //request.m = (byte*)calloc(0x3, sizeof(byte));
  //request.b[0] = 0x0;
  //request.b[1] = 0x1;
  //request.b[2] = 0x2;

  //case_request(&response, &request);

  //byte dfd = 0x0;

  //for (byte i = 0; i < request.length; i++)
  //{
  //  memcpy(&dfd, &request.m[i], 1);
  //}





//  _service.get_request(10); // тест
  

  //for (auto i=0; i<sizeof(request); i++)
  //{
  //  std::cout << request[i] << std::endl;
  //}


}
