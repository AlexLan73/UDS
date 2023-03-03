#include "ServiceBase.h"

namespace uds
{

		ServiceBase::ServiceBase()
		{
				rds_[6] = {};
				i_rds_ = 0x0;
				k_pid_ = 0x0;
				count_byte_ = 0x0;
				_name = "service";
				cod_servise_ = 0xFF;

				//i_rds_ = 0;
				//add_lambda(0x0, [this]()
				//		{
				//				rds_[k_pid_].pid = 0x0;
				//				rds_[k_pid_].length = 1;
				//				rds_[k_pid_].result.b[0] = 1;
				//				count_byte_ = count_byte_ + rds_[k_pid_].length;
				//		});
				//add_lambda(0x1, [this]()
				//		{
				//				rds_[k_pid_].pid = 0x1;
				//				rds_[k_pid_].length = 2;
				//				rds_[k_pid_].result.b[0] = 2;
				//				count_byte_ = count_byte_ + rds_[k_pid_].length;
				//		});
				//add_lambda(0x2, [this]()
				//		{
				//				rds_[k_pid_].pid = 0x2;
				//				rds_[k_pid_].length = 3;
				//				rds_[k_pid_].result.b[0] = 3;
				//				count_byte_ = count_byte_ + rds_[k_pid_].length;
				//		});
		};

		//inline  void ServiceBase::add_lambda(uint8_t i, const lambda f)
		//{
		//		maps_.insert(pair<uint8_t, lambda>(i, f));
		//}

		ServiceBase::~ServiceBase()
				= default;

		void  ServiceBase::get_request(response_message* response, request_message* request)
		{
				auto count_byte = response->length;  // NOLINT(clang-diagnostic-implicit-int)
				count_byte_ = 1;
				for (uint8_t i = 1; i < count_byte; i++)  // NOLINT(clang-diagnostic-implicit-int)
				{
						auto k = i - 1;
						rds_[k] = maps_[response->m[i]]();
						count_byte_ = count_byte_ + rds_[k].length;
						int uu = 1;
				}
				k_pid_ = response->length-1;
				request->length = count_byte_;
				form_data_for_can(request, cod_servise_);

				int kk = 1;
		}

		inline void ServiceBase::form_data_for_can(request_message* request, uint8_t num_serv_return)
		{
				free(request->m);
				m = new uint8_t[10];
//				uint8_t* m = new uint8_t[request->length];
				request->m = (uint8_t*)calloc(request->length, sizeof(uint8_t));
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
				int hhh = 1;

		}

}

