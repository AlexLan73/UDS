
#include <iostream>
#include <map>
#define CountRequest 8;

using namespace std;

map<uint8_t, > line_;


void case_serves(uint8_t* m) 
{
  if (sizeof(m) < 2)
    return;
  

}

int main()
{
  std::cout << "Hello World!\n";
  uint8_t request[] = {0x1, 0x15, 0x1, 0x5, 0x3, 0xC, 0xD };
  for (auto i=0; i<sizeof(request); i++)
  {
    std::cout << request[i] << std::endl;
  }
}
