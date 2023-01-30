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
						int run_inc(int l);
						int i, j;
						string str0;  
						string* str1;  
//						string& str2=NULL;
		};
}

#endif // !CANBASA_H


