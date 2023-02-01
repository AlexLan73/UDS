#pragma once

#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <tuple>
#include <queue>
//https://codelessons.ru/cplusplus/ochered-queue-v-c-realizaciya-i-chto-eto-voobshhe-takoe.html

// кортеж
// https://qosys.info/tuple-cpp

using namespace std;

namespace my_func 
{
		template <class T>
		class MyQueue
		{
				public:
						MyQueue()
						{
						}
								
								
//						void add_dan(T x);
//						template <class T>
						void add_dan(T x)
						{
								_q_dan.push(x);
						}

//						tuple<bool, T> get_dan();
//						template <class T>
						tuple<bool, T> get_dan()
						{
								T kk;
								if (!_q_dan.empty()) 
								{
										kk = _q_dan.front();
										_q_dan.pop();
										return std::make_tuple(true, kk);
								}

								return std::make_tuple(false, kk);
						}

						int ind=0;
				private:
						queue<T> _q_dan;
		};
}

#endif // !MYQUEUE_H

/*
		//template <class T>

						void add_dan(T x);
						tuple<bool, T> get_dan();
				private:
						queue<T> _q_dan;

*/