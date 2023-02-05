
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

class my_calc
{

public:
	explicit my_calc(const vector<tuple<double, double>>* m)
		{
				for (auto i = 0; i < sizeof(m) - 1; i++)  // NOLINT(clang-diagnostic-sign-compare, bugprone-sizeof-expression)
				{
						double k = (get<1>(m->at(i)) - get<1>(m->at(static_cast<std::vector<std::tuple<double, double>, std::allocator<std::tuple<double, double>>>::size_type>(i) + 1)))
																								/ (get<0>(m->at(i)) - get<0>(m->at(static_cast<std::vector<std::tuple<double, double>, std::allocator<std::tuple<double, double>>>::size_type>(i) + 1)));
						double b = get<1>(m->at(static_cast<std::vector<std::tuple<double, double>, std::allocator<std::tuple<double, double>>>::size_type>(i) + 1)) - k * get<0>(m->at(static_cast<std::vector<std::tuple<double, double>, std::allocator<std::tuple<double, double>>>::size_type>(i) + 1));
						line_.insert(pair<int, tuple<double, double>>(i, make_tuple(k, b)));
						x_.push_back(get<0>(m->at(i)));
				}
		}

		double get_calc(const double x0)
		{
				const auto itr = find_if(x_.begin(), x_.end(), [&](const double v) { return (v > x0); });
				const auto ind =distance(x_.begin(), itr);
				const auto kof = line_[ind > 0 ? ind - 1 : 0];
				return get<0>(kof) * x0 + get<1>(kof);
		}
		private:
				vector<double> x_;
				map<int, tuple<double, double>> line_;
};

int main()
{
		setlocale(LC_ALL, "rus");  // NOLINT(concurrency-mt-unsafe)

		vector<tuple<double, double>> mas = { {1.0, 1.6}, {2.0, 2.5}, {3.2, 3.1}, {8.0, 5.3}, {11.4, -1.2}, {12.0, -4.6}, {13.21, 2.24}, {15.0, 3.7} };
		auto calc = my_calc(&mas);
		double x0 = 9.5;
		auto e = calc.get_calc(x0);

	cout << " x0= "<< x0<< "  результат = "<< e << endl;

		std::cout << " Все !!!!\n";
}

