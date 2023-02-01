// Test01.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <string>
#include "Sourse/CAN/CanBasa.h"
#include "Sourse/CAN/CanTask.h"
#include <queue>
//https://codelessons.ru/cplusplus/ochered-queue-v-c-realizaciya-i-chto-eto-voobshhe-takoe.html

#include "Sourse/MyQueue.h"



using namespace std;
using namespace my_func;

class coms
{
public:
  coms()
  {
    //// рабочая
    //mTestMap["loop"] = &coms::loopper;
    //mTestMap["woop"] = &coms::woopper;
    //int kk0 = (this->*mTestMap["loop"])(10, 1);
    //int kk1 = (this->*mTestMap["woop"])(11, 32);

    mTestMap["loop"] = &coms::loopper;
    mTestMap["woop"] = &coms::woopper;
    int kk0 = (this->*mTestMap["loop"])(10, 1);
    int kk1 = (this->*mTestMap["woop"])(11, 32);

  }

  int loopper(int k0, int k1)
  {
    cout << "Loopper strick!!!\n";
    return k0;
  }
  int woopper(int k0, int k1)
  {
    cout << "Woopper strick!!!\n";
    return k1;
  }
  
  typedef int (coms::*myfunc)(int, int);
//  map<string, int (coms::*)(int, int)> mTestMap; // рабочая
  map<string, myfunc> mTestMap;

};

int main()
{
  setlocale(LC_ALL, "rus");


    MyQueue<int> _my_queeue;
    _my_queeue.add_dan(2);
    _my_queeue.add_dan(12);
    _my_queeue.add_dan(22);
    _my_queeue.add_dan(32);
    for (size_t i = 0; i < 6; i++)
    {
      int _x = 0;
      auto zz = _my_queeue.get_dan();
      auto _is = get<0>(zz);
      if (get<0>(zz))
        _x = get<1>(zz);
      auto sss = zz;
      std::cout << i << "   "<< get<0>(zz) << "   " << _x << std::endl;
    }

    coms _coms;
    //_coms.comlist["loop"]();

    std::cout << "Hello World!\n";

    CAN::CanTask _can_task1 = CAN::CanTask();
    auto jj1 = _can_task1.Run0(3, 5);


    int add(int, int);
    int subtract(int, int);
    int multiply(int, int);

    int a = 20;
    int b = 3;

    int (*operations[3])(int, int) = { add, subtract, multiply };


    //int result;
    //int (*operation)(int a, int b);

    //operation = add;
    //result = operation(a, b);

    int length = sizeof(operations) / sizeof(operations[0]);

    for (int i = 0; i < length; i++)
    {
      auto k = operations[i](a, b);    // вызов функции по указателю
      std::cout << k << std::endl;
    }


    map<string, int> first;

    first["add"] = 10;
    first["sub"] = 20;
    first["mul"] = 30;

    map<string, int>::iterator it;
    for (it = first.begin(); it != first.end(); ++it) {
      cout << it->first << " => " << it->second << '\n';
    }

    typedef int operations00(int, int);
    typedef operations00* myfuncptr;
//    myfuncptr add, subtract, multiply

//    typedef int operations(int, int) myFunc;

    map<string, myfuncptr> m0;

    m0["add"] = add;
    m0["sub"] = subtract;
    m0["mul"] = multiply;

    map<string, myfuncptr>::iterator itm0;
    for (itm0 = m0.begin(); itm0 != m0.end(); ++itm0) 
    {
      cout << itm0->first << " => " << itm0->second(a,b) << '\n';
    }






//    CAN::CanBasa _can_basa = CAN::CanBasa();
//    _can_basa.Run0();
//    auto k = _can_basa.Run0(100, 200);
    CAN::CanTask _can_task = CAN::CanTask();
    auto jj = _can_task.Run0(3, 5);

}

int add(int x, int y)
{
  return x + y;
}

int subtract(int x, int y)
{
  return x - y;
}
int multiply(int x, int y)
{
  return x * y;
}


//class A
//{
//public:
//  std::map< std::string, std::function<void()> > comlist;
//  A()
//  {
//    comlist = { {"loop", std::bind(&A::looper, this)},
//               {"woop", std::bind(&A::wooper, this)} };
//  }
//
//  void looper()
//  {
//    std::cout << "Looper!\n";
//  }
//
//  void wooper()
//  {
//    std::cout << "Wooper!\n";
//  }
//};
//
//int main()
//{
//  A a;
//  a.comlist["loop"]();
//  a.comlist["woop"]();
//}
