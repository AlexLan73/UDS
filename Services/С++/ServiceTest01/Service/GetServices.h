#pragma once
#include "CData.h"
#include <map>
#include "ServiceBase.h"

namespace uds
{

		class GetServices
		{
		public:
				GetServices();
				virtual void get_servise_request(response_message* response, request_message* request);
		private:

				map<uint8_t, ServiceBase> maps_service;

		};
}

