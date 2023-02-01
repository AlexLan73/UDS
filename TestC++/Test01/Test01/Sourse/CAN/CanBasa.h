#pragma once
#ifndef CANBASA_H
#define CANBASA_H


//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//
//#ifdef __cplusplus
//}
//#endif

#include <string>
#include <map>
#include <functional>

using namespace std;

namespace CAN {


		class CanBasa
		{
				public:
						CanBasa();
						CanBasa(string str0, string* str1);
						void Run0();
						int Run0(int i, int j);
						virtual int Run1(int i, int j);

						int ind_i, ind_j;
				private:
						void inicial_params();
						int run_inc(int l);
						int add(int x, int y);
						int subtract(int x, int y);
						void add0(int x, int y);
						void subtract0(int x, int y);
						int multiply(int x, int y);

						typedef int (CanBasa::* myfunc)(int, int);
						map<string, myfunc> m0;


//						typedef double (A::* MemFunPtr)();
//						typedef int (CanBasa::* actions00)(int, int);
//						typedef actions00 actionfuncptr;
//						typedef function < int (int, int)> actions00;
//						typedef actions00 actionfuncptr;
//						map<string, std::function < int(int, int)>> m0;
//						typedef int (CanBasa::*actions00(int, int));
//						map<string, actions00*> m0;

						int i, j;
						string str0;  
						string* str1;  
//						string& str2=NULL;
		};
}

#endif // !CANBASA_H


/*

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

int add(int x, int y)
int subtract(int x, int y)
int multiply(int x, int y)


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


*/