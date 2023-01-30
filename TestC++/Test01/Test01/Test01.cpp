// Test01.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <string>
#include "Sourse/CAN/CanBasa.h"
#include "Sourse/CAN/CanTask.h"

int main()
{
  
    std::cout << "Hello World!\n";
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


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
