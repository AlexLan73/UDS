#include "ServiceBase.h"

namespace uds
{

		ServiceBase::ServiceBase()
		{
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

		}
/*
		void ServiceBase::f_request(uint8_t* index, uint8_t count, uint8_t pid)
		{
				count_byte_ = 0;
				for (uint8_t i = 0; i < count; i++)
				{
						k_pid_ = i;
						maps_[index[i]]();
				}
				//form_data_for_can(const struct read_dan_service* source, int count, request_message * request, uint8_t num_serv_return)

		}


		void ServiceBase::f_request(uint8_t index, uint8_t pid)
		{
				count_byte_ = 0;
				k_pid_=0;
				maps_[index]();
				k_pid_++;
				//form_data_for_can(const struct read_dan_service* source, int count, request_message * request, uint8_t num_serv_return)
		}
*/

		void ServiceBase::f_request(response_message* response, request_message* request, uint8_t pid) 
		{
				struct read_dan_service rds[6];
				auto count_byte = response->length;  // NOLINT(clang-diagnostic-implicit-int)
				int k_pid = 0;
				count_byte_ = 0;
				for (auto i = 1; i < response->length; i++)  // NOLINT(clang-diagnostic-implicit-int)
				{
						k_pid_ = i;
						maps_[i]();
				}
				int kk = 1;
				//form_data_for_can(const struct read_dan_service* source, int count, request_message * request, uint8_t num_serv_return)

		}



		//inline void ServiceBase::form_data_for_can(const struct read_dan_service* source, int count, request_message* request, uint8_t num_serv_return)
		inline void ServiceBase::form_data_for_can(request_message* request, uint8_t num_serv_return)
		{
				//rds_
				//k_pid_

				free(request->m);
				request->m = (uint8_t*)calloc(request->length, sizeof(uint8_t));
				memcpy(&request->m[0], &num_serv_return, 1);
				int k = 1;
				int i = 0;
				while (i < k_pid_)
				{
						//struct read_dan_service xx = source[i];
						//memcpy(&request->m[k], &xx.pid, 1);
						//k++;
						//memcpy(&request->m[k], &(xx.result.b[0]), xx.length);
						//k = k + xx.length;
						//i++;

		//				auto xx = rds_[i];
						memcpy(&request->m[k], &rds_[i].pid, 1);
						k++;
						memcpy(&request->m[k], &(rds_[i].result.b[0]), rds_[i].length);
						k = k + rds_[i].length;
						i++;

				}


		}

}

