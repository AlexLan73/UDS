// Igor.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

template <class T, class E>
class my_calc
{
		template <class T, class E>
	struct line_func
	{
			line_func( tuple<T, E> z1, tuple<T, E> z2)
			{
					k = static_cast<double>((get<1>(z1) - get<1>(z2)) / (get<0>(z1) - get<0>(z2)));
					b = get<1>(z2) - k * get<0>(z2);
			}
			double fget(T x0)
			{
					return  static_cast<double>(k * x0) + b;
			}
			double k;
			double b;
	};
public:
		my_calc(vector<tuple<T, E>> *m)
		{
				for (int i =0; i< sizeof(m) - 1; i++)
				{
						_fun_line.insert(pair<int, line_func<T, E>>(i, line_func<T, E>(m->at(i), m->at(i + 1))));
//						line_func<T, E > __l = line_func<T, E>(m->at(i), m->at(i + 1));
						auto zz = get<0>(m->at(i));
						_x.push_back(zz);
				}
		}

		double get_calc(T x0)
		{
				
				auto itr = find_if(_x.begin(), _x.end(), [&](T v) { return (v > x0); });
				auto _ind = distance(_x.begin(), itr);
				_ind = _ind > 0 ? _ind - 1 : 0;
				auto _func = _fun_line[_ind];
				auto _rezul = static_cast<double>(_func.fget(x0));
				return _rezul;
		}



private:
		vector<T> _x;
		map<__int64, line_func<T, E>> _fun_line;
};


int main()
{

		vector<tuple<double, double>> mas = { {1.0, 1.6}, {2.0, 2.5}, {3.2, 3.1}, {8.0, 5.3}, {11.4, -1.2}, {12.0, -4.6}, {13.21, 2.24}, {15.0, 3.7} };
		my_calc<double, double> _calc = my_calc< double, double>(&mas);
//		my_calc<int, int> _calc = my_calc<int, int>(&mas);
//		auto _e = _calc<double, double>.get_calc(1.5);
		auto _e = _calc.get_calc(9.5);


		int x1 = 3;
		int y1 = 2;
		int x2 = -1;
		int y2 = -1;
		double k = (double) (y1 - y2) / (x1 - x2);
		double b = y2 - k * x2;
		double x0 = 1.5;
		double d = k * x0 + b;
		std::cout << x0 << "   "<< d << std::endl;

    std::cout << "Hello World!\n";
}

/*
 Получить значения координат первой точки и присвоить их переменным, например x1 и y1.
Получить значения координат (x2, y2) второй точки.
Вычислить значение k по формуле k = (y1 — y2) / (x1 — x2).
Вычислить значение b по формуле b = y2 — k * x2.
Вывести на экран полученное уравнение.

 А(3;2), а координаты B(-1;-1).
 */