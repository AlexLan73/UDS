#pragma once

#include "MyQueue.h"

namespace my_func 
{
		
		template <class T>
		my_func::MyQueue<T>::MyQueue()
		{
				ind = 10;
		};

		//template <class T>
		//void MyQueue<T>::add_dan(T x)
		//{
		//		_q_dan.push(x);
		//}

		//template <class T>
		//tuple<bool, T> MyQueue<T>::get_dan()
		//{
		//		T kk;
		//		if (!_q_dan.empty()) 
		//		{
		//				kk = _q_dan.front();
		//				_q_dan.pop();
		//				return std::make_tuple(true, kk);
		//		}

		//		return std::make_tuple(false, kk);
		//}

}
