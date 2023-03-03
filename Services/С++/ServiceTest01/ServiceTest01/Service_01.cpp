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
								read_dan_service01 rds;
								rds.pid = 0x0;
								rds.length = 1;
								rds.result.b[0] = 1;
								return rds;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x1, [this]()
						{
								read_dan_service01 rds;
								rds.pid = 0x1;
								rds.length = 4;
								rds.result.b[0] = 0x10;
								rds.result.b[1] = 0x11;
								rds.result.b[2] = 0x12;
								rds.result.b[3] = 0x13;
								return rds;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x3, [this]()
						{
								read_dan_service01 rds;
								rds.pid = 0x3;
								rds.length = 3;
								rds.result.b[0] = 3;
								rds.result.b[1] = 13;
								rds.result.b[2] = 23;
								return rds;

						}));

				maps_.insert(pair<uint8_t, lambda>(0x5, [this]()
						{
								read_dan_service01 rds;
								rds.pid = 0x5;
								rds.length = 1;
								rds.result.b[0] = 5;
								return rds;
						}));

				maps_.insert(pair<uint8_t, lambda>(0xC, [this]()
						{
								read_dan_service01 rds;
								rds.pid = 0xC;
								rds.length = 4;
								rds.result.l = 0xC;
								rds.result.b[0] = 5;
								return rds;
						}));

				maps_.insert(pair<uint8_t, lambda>(0xD, [this]()
						{
								read_dan_service01 rds;
								rds.pid = 0xD;
								rds.length = 4;
								rds.result.l = 0xD;
								return rds;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x15, [this]()
						{
								read_dan_service01 rds;
								rds.pid = 0x15;
								rds.length = 2;
								rds.result.w[0] = 0x15;
								return rds;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x19, [this]()
						{
								read_dan_service01 rds;
								rds.pid = 0x19;
								rds.length = 2;
								rds.result.b[0] = 0x19;
								rds.result.b[1] = 0x1A;
								return rds;
						}));

				maps_.insert(pair<uint8_t, lambda>(0x20, [this]()
						{
								read_dan_service01 rds;
								rds.pid = 0x20;
								rds.length = 4;
								rds.result.b[0] = 0x20;
								rds.result.b[1] = 0x21;
								rds.result.b[2] = 0x22;
								rds.result.b[3] = 0x23;
								return rds;
						}));
		}


		//void Service_01::get_request(response_message* response, request_message* request) 
		//{
		//		f_request(response, request, 0x41);
		//}

		

}
