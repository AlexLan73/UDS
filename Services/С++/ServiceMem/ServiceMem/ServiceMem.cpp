
#include <iostream>
#include <memory>
#include <map>
#include "../Service/CData.h"
#include "../Service/GetServices.h"


using namespace std;

int main()
{
		std::cout << "Hello World!\n";

		shared_ptr<uds::response_message> _response = make_shared<uds::response_message>();
		shared_ptr<uds::request_message> _request = make_shared<uds::request_message>();

		const uint8_t response_m[] = { 0x1, 0x15, 0x1, 0x5, 0x3, 0xC, 0xD };
//		uds::response_message response{};
		_response->length = sizeof(response_m);
		for (size_t i = 0; i < _response->length; i++)
				_response->m[i] = response_m[i];


		shared_ptr<uds::GetServices> _get_servises = make_shared<uds::GetServices>();
		_get_servises->get_servise_request(_response, _request);
		int kkk = 1;
}

/*

		struct response_message
		{
				uint8_t length;
				uint8_t m[7];
		};

		struct request_message
		{
				uint8_t length;
				uint8_t b[100];
				uint8_t* m;
		};

*/