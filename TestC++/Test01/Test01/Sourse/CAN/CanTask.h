#pragma once
#ifndef CANTASK_H
#define CANTASK_H


#include "CanBasa.h"

namespace CAN {
		class CanTask : public  CanBasa
		{
				public:
						CanTask();
						virtual int Run1(int i, int j);
		};
}

#endif // !CANTASK_H


