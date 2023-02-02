#include "security_access_private.h"


//https://ru.wikipedia.org/wiki/Digital_Signature_Standard
//https://docs.microsoft.com/ru-ru/dotnet/framework/app-domains/how-to-create-a-public-private-key-pair
//https://docs.microsoft.com/ru-ru/dotnet/api/system.security.cryptography.asymmetricalgorithm?view=netframework-4.7.2
//https://ru.wikipedia.org/wiki/%D0%AD%D0%BB%D0%B5%D0%BA%D1%82%D1%80%D0%BE%D0%BD%D0%BD%D0%B0%D1%8F_%D0%BF%D0%BE%D0%B4%D0%BF%D0%B8%D1%81%D1%8C


//https://ru.wikipedia.org/wiki/PKCS
//
//ГОСТ
//https://ru.wikipedia.org/wiki/%D0%93%D0%9E%D0%A1%D0%A2_%D0%A0_34.10-2012

uint8 security_access(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message)
{
	static uint32 seed = 0;
	static uint32 key = 0;

	response_message->pdu.iso15765_service_data.buffer_idx = 0;

	if (security_access_counter < MAX_SECURITY_COUNTER) {
		uint8 sub_function = request_message->pdu.iso15765_service_data.data[1];
		switch (sub_function) {
		//--------------------------------
		//seed и key 0 - access_level_00 - default
		//--------------------------------
		case LEV_SAT_RSD_00:
			if ((request_message->pdu.iso15765_protocol_data.length) == ER_RDS_LENGTH) {
				if (uds_active_security_level == access_level_00) {
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = SAPR;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = 0;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = 0;

					response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;

					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
				} else {
					security_access_counter++;

					seed = generate_seed_for_uds_security_level(); //TODO
					key = calculate_scu_key(seed);

					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = SAPR;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = ( (uint8)( (seed >> 24) & 0xFF) );
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = ( (uint8)( (seed >> 16) & 0xFF) );
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = ( (uint8)( (seed >> 8) & 0xFF) );
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = ( (uint8)( (seed     ) & 0xFF) );

					response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
					response_message->pdu.iso15765_protocol_data.target_address_type = physical_address_type;

					security_access_flag.seed_0_is_requested = 1;

					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
				}
			} else {
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
			}

		case LEV_SAT_SK_00:
			if ((request_message->pdu.iso15765_protocol_data.length) == ER_SK_LENGTH) {
				if (security_access_flag.seed_0_is_requested) {
					security_access_flag.seed_0_is_requested = 0;

					uint32 client_key = ((((uint32)request_message->pdu.iso15765_service_data.data[2] )<< 24 ) & 0xFF000000) +
							((((uint32)request_message->pdu.iso15765_service_data.data[3]) << 16) & 0x00FF0000) +
							((((uint32)request_message->pdu.iso15765_service_data.data[4]) << 8) & 0x0000FF00) +
							((((uint32)request_message->pdu.iso15765_service_data.data[5])) & 0x000000FF)
							;

					security_access_flag.key_is_valid = ((key == client_key)?1:0);

					if (security_access_flag.key_is_valid) {
						security_access_flag.key_is_valid = 0;
						security_access_counter = 0;
						uds_active_security_level = access_level_00;

						response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = SAPR;
						response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;

						response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;

						return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
					} else {
						return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IK;
					}
				} else {
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_RSE;
				}
			} else {
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
			}
			break;
		//--------------------------------
		//seed и key 1 - access_level_01
		//--------------------------------
		case LEV_SAT_RSD_01:
			if ((request_message->pdu.iso15765_protocol_data.length) == ER_RDS_LENGTH) {
				if (uds_active_security_level == access_level_01) {
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = SAPR;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = 0;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = 0;

					response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;

					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
				} else {
					security_access_counter++;

					seed = generate_seed_for_uds_security_level(); //TODO
					key = calculate_scu_key(seed);

					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = SAPR;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = ( (uint8)( (seed >> 24) & 0xFF) );
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = ( (uint8)( (seed >> 16) & 0xFF) );
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = ( (uint8)( (seed >> 8) & 0xFF) );
					response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = ( (uint8)( (seed     ) & 0xFF) );

					response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
					security_access_flag.seed_1_is_requested = 1;

					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
				}
			} else {
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
			}
		case LEV_SAT_SK_01:
			if ((request_message->pdu.iso15765_protocol_data.length) == ER_SK_LENGTH) {
				if (security_access_flag.seed_1_is_requested) {
					security_access_flag.seed_1_is_requested = 0;

					uint32 client_key = ((((uint32)request_message->pdu.iso15765_service_data.data[2] )<< 24 ) & 0xFF000000) +
							((((uint32)request_message->pdu.iso15765_service_data.data[3]) << 16) & 0x00FF0000) +
							((((uint32)request_message->pdu.iso15765_service_data.data[4]) << 8) & 0x0000FF00) +
							((((uint32)request_message->pdu.iso15765_service_data.data[5])) & 0x000000FF)
							;

					security_access_flag.key_is_valid = (key == client_key)?1:0;

					if (security_access_flag.key_is_valid) {
						security_access_flag.key_is_valid = 0;

						security_access_counter = 0;
						uds_active_security_level = access_level_01;

						response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = SAPR;
						response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;

						response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
						response_message->pdu.iso15765_protocol_data.target_address_type = physical_address_type;

						return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
					} else {
						return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IK;
					}
				} else {
					return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_RSE;
				}
			} else {
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
			}
		default:
			return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_SFNS;
		}
	} else if (security_access_counter == MAX_SECURITY_COUNTER) {
		// достигнут максимум последовательных запросов на получения любого уровня безопасности, оставленных без ответа
		return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ENOA;
	} else {
		return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_RTDNE; // ???? не уверен что при этом условии TODO
	}
}

static uint32 generate_seed_for_uds_security_level(void)
{
	//todo
	return 0x853A08FB;
}
