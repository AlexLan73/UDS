#pragma once
#include <cstdint>
#include <map>
#include <functional>
#include <string>
#include "CData.h"

namespace uds
{
		using namespace std;  // NOLINT(clang-diagnostic-header-hygiene)

		class ServiceBase
		{
		public:
				ServiceBase();
				virtual ~ServiceBase();

//				void get_servise_request(response_message* response, request_message* request);
				virtual void get_request(response_message* response, request_message* request);

		protected:

				typedef function<void()> lambda;
				struct read_dan_service01
				{
						uint8_t pid;
						uint8_t length;
						union result
						{
								uint8_t b[4];
								unsigned short w[2];
								unsigned long l;
						} result{};

				};
//				inline void add_lambda(uint8_t i, const lambda f);
//				virtual void f_request(uint8_t index, uint8_t pid);
//				virtual void f_request(uint8_t* index, uint8_t count, uint8_t pid);
				virtual void f_request(response_message* response, request_message* request, uint8_t pid);

				inline void form_data_for_can(struct request_message* request, uint8_t num_serv_return);

				map<uint8_t, lambda> maps_;
				read_dan_service01 rds_[6] = {};
				uint8_t i_rds_ = 0;
				uint8_t k_pid_ = 0;
				uint8_t count_byte_ = 0;
				string _name = "service";

		};
}

