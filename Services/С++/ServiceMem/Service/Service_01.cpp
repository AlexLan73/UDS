#include "../Service/Service_01.h"

namespace uds
{
		Service_01::Service_01()
		{
				_name = "service_0x1";
				cod_servise_ = 0x41;
				i_rds_ = 0;
				k_pid_ = 0;
				maps_.insert(pair<uint8_t, lambda>(0x0, [this]()
						{
								rds_[k_pid_].pid = 0x0;
								rds_[k_pid_].length = 1;
								rds_[k_pid_].result.b[0] = 1;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x1, [this]()
						{
								rds_[k_pid_].pid = 0x1;
								rds_[k_pid_].length = 4;
								rds_[k_pid_].result.b[0] = 0x10;
								rds_[k_pid_].result.b[1] = 0x11;
								rds_[k_pid_].result.b[2] = 0x12;
								rds_[k_pid_].result.b[3] = 0x13;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x3, [this]()
						{
								rds_[k_pid_].pid = 0x3;
								rds_[k_pid_].length = 3;
								rds_[k_pid_].result.b[0] = 3;
								rds_[k_pid_].result.b[1] = 13;
								rds_[k_pid_].result.b[2] = 23;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x5, [this]()
						{
								rds_[k_pid_].pid = 0x5;
								rds_[k_pid_].length = 1;
								rds_[k_pid_].result.b[0] = 5;
						}));

				maps_.insert(pair<uint8_t, lambda>(0xC, [this]()
						{
								rds_[k_pid_].pid = 0xC;
								rds_[k_pid_].length = 4;
								rds_[k_pid_].result.l = 0xC;
								rds_[k_pid_].result.b[0] = 5;
						}));

				maps_.insert(pair<uint8_t, lambda>(0xD, [this]()
						{
								rds_[k_pid_].pid = 0xD;
								rds_[k_pid_].length = 4;
								rds_[k_pid_].result.l = 0xD;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x15, [this]()
						{
								rds_[k_pid_].pid = 0x15;
								rds_[k_pid_].length = 2;
								rds_[k_pid_].result.w[0] = 0x15;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x19, [this]()
						{
								rds_[k_pid_].pid = 0x19;
								rds_[k_pid_].length = 2;
								rds_[k_pid_].result.b[0] = 0x19;
								rds_[k_pid_].result.b[1] = 0x1A;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x20, [this]()
						{
								rds_[k_pid_].pid = 0x20;
								rds_[k_pid_].length = 4;
								rds_[k_pid_].result.b[0] = 0x20;
								rds_[k_pid_].result.b[1] = 0x21;
								rds_[k_pid_].result.b[2] = 0x22;
								rds_[k_pid_].result.b[3] = 0x23;
						}));

		}

}
