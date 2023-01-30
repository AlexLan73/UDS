#include "CanBasa.h"

//using namespace std;

namespace CAN 
{

//		CanBasa::CanBasa(string str0, string* str1, string& str2)
		CanBasa::CanBasa(string str0, string* str1)
		{
				this->str0 = str0;
				this->str1 = str1;
				ind_i = 31;
				ind_j = 42;
		}


		CanBasa::CanBasa()
		{
				i = 1;
				j = 2;
				ind_i = 11; 
				ind_j = 22 ;
		}

		void CanBasa::Run0()
		{
				i = 10;
				j = 20;
		}

		int CanBasa::Run0(int i, int j)
		{
				this->i = this->i + i;
				this->j = +this->j + j;
				auto k = this->i + this->j;
				auto k0 = Run1(this->i, this->j);
				return k;
		}

		int  CanBasa::Run1(int i, int j) 
		{
				auto ii = run_inc(j);
				auto k = i * j+ii;
				return k;
		}

		int CanBasa::run_inc(int l) 
		{
				return i + l;
		}

}



/*
namespace CAN {

		#include <string>

		using namespace std;

		class CanBasa
		{
		public:
				CanBasa(string str0, string *str1, string& str2);
				void Run0();
				int Run0(int i, int j);
		private:
				int i, j;
				string str0;
				string* str1;
				string& str2;
		};
}

*/
