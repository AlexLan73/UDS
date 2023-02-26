#include "ServiceBase.h"

ServiceBase::ServiceBase()
{
		i_rds_ = 0;
		add_lambda(0x0, [this]()
						{
						rds_[k_pid_].pid = 0x0;
						rds_[k_pid_].length = 1;
						rds_[k_pid_].result.b[0] = 1;
						count_byte_ = count_byte_ + rds_[k_pid_].length;
						});
		add_lambda(0x1, [this]()
						{
						rds_[k_pid_].pid = 0x1;
						rds_[k_pid_].length = 2;
						rds_[k_pid_].result.b[0] = 2;
						count_byte_ = count_byte_ + rds_[k_pid_].length;
						});
		add_lambda(0x2, [this]()
						{
						rds_[k_pid_].pid = 0x2;
						rds_[k_pid_].length = 3;
						rds_[k_pid_].result.b[0] = 3;
						count_byte_ = count_byte_ + rds_[k_pid_].length;
						});
};

inline  void ServiceBase::add_lambda(uint8_t i, const lambda& f)
{
		maps_.insert(pair<uint8_t, lambda>(i, f));
}

ServiceBase::~ServiceBase()
= default;

void ServiceBase::get_request(uint8_t index)
{
		count_byte_ = 0;
		for (uint8_t i=0; i<3; i++)
		{
				k_pid_ = i;
				maps_[i]();
				// ReSharper disable once CppDeclaratorNeverUsed
				auto xxx = count_byte_;
		}
  
}
