// Show01.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

union NumericType
{
  short       iValue;
  long        lValue;
  double      dValue;
};

typedef unsigned char uint8;
typedef unsigned int uint32;

struct can_message_s {
  uint32		id;
  uint8		length;

  union d_u {
    uint32	word[2];
    uint8	byte[8];
  } data;
};


int main()
{
    std::cout << "Hello World!\n";

    union NumericType Values = { 10 };   // iValue = 10
    cout << Values.iValue << endl;
    Values.dValue = 3.1416;
    cout << Values.dValue << endl;

    can_message_s m = { 10 };
    can_message_s m1 = { 11 };
    m1.data = { 0xF0FFAA01, 0xA0FFAA01 };
//    m1.data = { 0, 1};
//    m1.data = { 2 };
    auto x = m1.data.byte[1];
    
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
