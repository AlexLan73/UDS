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

				virtual void get_request(shared_ptr<response_message> response, shared_ptr<request_message> request);

//		protected:

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
//				typedef function<read_dan_service01()> lambda;
				typedef function<void()> lambda;

				inline void form_data_for_can(shared_ptr<request_message> request, uint8_t num_serv_return);

				map<uint8_t, lambda> maps_;
				read_dan_service01 rds_[6] = {};
				uint8_t i_rds_ = 0x0;
				uint8_t k_pid_ = 0x0;
				uint8_t count_byte_ = 0x0;
				string _name = "service";
				uint8_t cod_servise_ = 0xFF;
				uint8_t* m = nullptr;
		};
}

