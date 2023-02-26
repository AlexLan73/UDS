
#include <iostream>
#include <map>
#include "../Service/ServiceBase.h"
#define CountRequest 8;

using namespace std;


void case_serves(uint8_t* m) 
{
  if (sizeof(m) < 2)
    return;
  

}

int main()
{
  auto func_lamd = [](int ix)
  {
    std::cout << ix << std::endl;
  };

  std::cout << "Hello World!\n";
  uint8_t request[] = {0x1, 0x15, 0x1, 0x5, 0x3, 0xC, 0xD };
  func_lamd(10);

  auto _service = ServiceBase();
  _service.get_request(10);

  //for (auto i=0; i<sizeof(request); i++)
  //{
  //  std::cout << request[i] << std::endl;
  //}


}
