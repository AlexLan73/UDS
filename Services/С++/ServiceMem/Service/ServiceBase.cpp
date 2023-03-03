#include "ServiceBase.h"

namespace uds
{

		ServiceBase::ServiceBase()
		{
		};


		ServiceBase::~ServiceBase()
				= default;

		void  ServiceBase::get_request(shared_ptr<response_message> response, shared_ptr<request_message> request)
		{
				auto count_byte = response->length;  // NOLINT(clang-diagnostic-implicit-int)
				count_byte_ = 1;
				k_pid_ = 0;
				for (uint8_t i = 1; i < count_byte; i++)  // NOLINT(clang-diagnostic-implicit-int)
				{
						k_pid_ = i - 1;
						maps_[response->m[i]]();
						count_byte_ = count_byte_ + rds_[k_pid_].length;
				}
				k_pid_ = response->length-1;
				request->length = count_byte_;
				form_data_for_can(request, cod_servise_);
		}

		inline void ServiceBase::form_data_for_can(shared_ptr<request_message> request, uint8_t num_serv_return)
		{
				delete request->m;
				request->m = new uint8_t[request->length];
				memcpy(&request->m[0], &num_serv_return, 1);
				int k = 1;
				int i = 0;
				while (i < k_pid_)
				{
						memcpy(&request->m[k], &rds_[i].pid, 1);
						k++;
						memcpy(&request->m[k], &(rds_[i].result.b[0]), rds_[i].length);
						k = k + rds_[i].length;
						i++;
				}
		}

}

