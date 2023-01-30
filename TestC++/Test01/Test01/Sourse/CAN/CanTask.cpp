#include "CanTask.h"

namespace CAN
{
		CanTask::CanTask() :CanBasa() {
				ind_i = 55;
				ind_j = 66;
		}

		int CanTask::Run1(int i, int j) 
		{
				auto k = i - j;
				return k;
		}
}
