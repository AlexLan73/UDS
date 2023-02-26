#pragma once
#include <cstdint>
#include <map>
#include <functional>

using namespace std;  // NOLINT(clang-diagnostic-header-hygiene)

class ServiceBase
{
public:
		ServiceBase();
		virtual ~ServiceBase();
		virtual void get_request(uint8_t index);
		
private:
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
		inline void add_lambda(uint8_t i, const lambda& f);
		map<uint8_t, lambda> maps_;
		read_dan_service01 rds_[6]={};
		uint8_t i_rds_ = 0;
		uint8_t k_pid_ = 0;
		uint8_t count_byte_ = 0;
};


