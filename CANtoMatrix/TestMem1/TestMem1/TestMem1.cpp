// TestMem1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <memory>
 
using namespace std;

typedef unsigned char byte;
class MyMem
{
public:
		MyMem();
		~MyMem();
		void run();
private:
		byte _m[31] = {0, 12, 2, 3, 4, 5, 6, 7, 8, 39, 40, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
		byte* _m_prt;

};

MyMem::MyMem()
{
		byte _m0[4] = { 0,0,0,0 };
		auto _count = size(_m);
		_m_prt = &*_m;
		auto x0 = _m_prt[0];
		auto x1 = _m_prt[1];
		auto x10 = _m_prt[10];
		memcpy(&_m0, &_m[9], sizeof(_m0));
}

MyMem::~MyMem()
{
}

void MyMem::run()
{

}

int main()
{
    std::cout << "Hello World!\n";
				shared_ptr<MyMem> _my_mem = make_shared<MyMem>();
				_my_mem->run();

}
