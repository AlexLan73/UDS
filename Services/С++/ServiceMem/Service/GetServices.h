#pragma once
#include "CData.h"
#include <map>
#include <memory>
#include "ServiceBase.h"

// #include "ServiceBase.h"

namespace uds
{

		class GetServices
		{
		public:
				GetServices();
				virtual void get_servise_request(shared_ptr<response_message> response, shared_ptr<request_message> request);
		private:

			map<uint8_t, shared_ptr<ServiceBase>> maps_service;

		};
}

//shared_ptr<uds::response_message> _response = make_shared<uds::response_message>();
//shared_ptr<uds::request_message> _request = make_shared<uds::request_message>();
