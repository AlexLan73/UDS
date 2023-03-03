#include "../Service/GetServices.h"
#include "Service_01.h"
//#include "../Service/Service_01.h"
//#include "../Service/Service_02.h"

namespace uds
{
		GetServices::GetServices() 
		{
//				(pair<int, tuple<double, double>>(i, make_tuple(k, b)));
// 	map<uint8_t, ServiceBase> maps_service;				
//				maps_service.insert(pair<uint8_t, ServiceBase>(0x1, Service_01()));
//				maps_service.insert(pair<uint8_t, ServiceBase>(0x2, Service_02()));
				maps_service.insert(pair<uint8_t, shared_ptr<ServiceBase>>(0x1, make_shared<Service_01>()));

		}

		void GetServices::get_servise_request(shared_ptr<response_message> response, shared_ptr<request_message> request)
		{
				if (response->length < 2 || response->length > 7)
						return;

				auto _service = maps_service[response->m[0]];
				_service->get_request(response, request);
		

		}

}
