#include "can_tp_iso15765_initialization.h"

#include "can_pt_rx_id.h"
#include "can_pt_tx_id.h"



static void can_iso15765_parameters_init(struct can_tp_iso15765_parameter_s* parameter_p);
static void can_tp_iso15765_instances_init(struct can_tp_iso15765_instance_s* can_tp_instance_p);
static void clear_can_tp_iso15765_instance(struct iso15765_tp_s* can_tp_instance_p);
static void can_iso15765_parameters_init_config(struct can_tp_iso15765_parameter_s* parameter_p);

void can_tp_iso15765_initialization(void)
{
	//init can_tp_iso15765[0] instance

	//set default parameters
	can_iso15765_parameters_init_config(&server_parameter[0]);
	can_iso15765_parameters_init_config(&client_parameter[0]);

	// change parameters
	can_iso15765_parameters_init(&server_parameter[0]);

	//init instanses by zero
	can_tp_iso15765_instances_init(&can_tp_iso15765_request_instance[0]);
	can_tp_iso15765_instances_init(&can_tp_iso15765_response_instance[0]);
}

static void can_iso15765_parameters_init(struct can_tp_iso15765_parameter_s* parameter_p)
{
	enum iso15765_result result;
	//TODO need to think about the mapping function of the CAN ID and CAN TP
	//TODO need to initialize not just one instance
	result = set_iso15765_parameter(parameter_p, BLOCK_SIZE, MAX_BLOCK_SIZE );	// The BLOCK_SIZE parameter is described on @page 19 ISO 15765-2:2016
	if (result != N_OK) { /* need some action*/ }
	result = set_iso15765_parameter(parameter_p, SEPARATION_TIME, 10);			// The SEPARATION_TIME parameter is described on @page 19 ISO 15765-2:2016
	if (result != N_OK) { /* need some action*/ }
	result = set_iso15765_parameter(parameter_p, WFT_MAX, 5);						// The WFT_MAX parameter is described on @page 33 ISO 15765-2:2016
	if (result != N_OK) { /* need some action*/ }
	result = set_iso15765_parameter(parameter_p, PADDING_VALUE, 0x00);			// The PADDING_VALUE parameter is described on @pages 43-45 ISO 15765-2:2016
	if (result != N_OK) { /* need some action*/ }
	//	result = set_iso15765_parameter(REQ_MSG_MAX_NUM, 1); 			// TODO when I change the REQ_MSG_MAX_NUM parameter with the help of this function I should to correct
	if (result != N_OK) { /* need some action*/ }			//		this parameter in can_tp_iso15765_instances_init() (if REQ_MSG_MAX_NUM is not "#define REQ_MSG_MAX_NUM")
//	result = set_iso15765_parameter(RESP_MSG_MAX_NUM, 1); 			// TODO when I change the RESP_MSG_MAX_NUM parameter with the help of this function I should to correct
												 	 	 	//		this parameter in can_tp_iso15765_instances_init() (if RESP_MSG_MAX_NUM is not "#define REQ_MSG_MAX_NUM")
	if (result != N_OK) { /* need some action*/ }
	// Timeouts are described on @page37 ISO 15765-2:2016
	result = set_iso15765_parameter(parameter_p, AS_TIMEOUT, 25);
	if (result != N_OK) { /* need some action*/ }
	result = set_iso15765_parameter(parameter_p, BS_TIMEOUT, 250);
	if (result != N_OK) { /* need some action*/ }
	result = set_iso15765_parameter(parameter_p, CS_TIMEOUT, 25); //TODO If ST_min is set after this parameter
	if (result != N_OK) { /* need some action*/ }
	result = set_iso15765_parameter(parameter_p, AR_TIMEOUT, 25);
	if (result != N_OK) { /* need some action*/ }
	result = set_iso15765_parameter(parameter_p, BR_TIMEOUT, 25);
	if (result != N_OK) { /* need some action*/ }
	result = set_iso15765_parameter(parameter_p, CR_TIMEOUT, 250);
	if (result != N_OK) { /* need some action*/ }

	// address mapping
	result = set_iso15765_parameter(parameter_p, SERVER_ADDRESS, FRAME_Diag_To_ECU_ID);
	if (result != N_OK) { /* need some action*/ }
	result = set_iso15765_parameter(parameter_p, CLIENT_ADDRESS, FRAME_Diag_From_ECU_ID);
	if (result != N_OK) { /* need some action*/ }
	result = set_iso15765_parameter(parameter_p, BROADCAST_ADDRESS, FRAME_Diag_Functional_FromPT_ID);
}

static void can_tp_iso15765_instances_init(struct can_tp_iso15765_instance_s* can_tp_instance_p)
{
	can_tp_instance_p->is_free = TRUE;
	clear_can_tp_iso15765_instance(&can_tp_instance_p->can_tp);
}

static void clear_can_tp_iso15765_instance(struct iso15765_tp_s* can_tp_instance_p)
{
	uint32 data_idx;

	can_tp_instance_p->can_frame.id = 0;
	can_tp_instance_p->can_frame.length = 0;

	can_tp_instance_p->can_frame.data.word[0] = 0;
	can_tp_instance_p->can_frame.data.word[1] = 0;

	can_tp_instance_p->pdu.iso15765_protocol_data.source_address = 0x00; /*TODO from CAN ID*/
	can_tp_instance_p->pdu.iso15765_protocol_data.target_address = 0x00; /*TODO from CAN ID*/
	can_tp_instance_p->pdu.iso15765_protocol_data.target_address_type = 5; //random value
	can_tp_instance_p->pdu.iso15765_protocol_data.remote_address = 0;
	can_tp_instance_p->pdu.iso15765_protocol_data.id_type = ID_CAN_11BIT;

	can_tp_instance_p->pdu.iso15765_protocol_data.message_type[DATA_LAYER] = unknown_message;
	can_tp_instance_p->pdu.iso15765_protocol_data.message_type[NETWORK_LAYER] = unknown_message;
	can_tp_instance_p->pdu.iso15765_protocol_data.message_type[APPLICATION_LAYER] = unknown_message;

	can_tp_instance_p->pdu.iso15765_protocol_data.format_type = unknown_addressing_format;
	can_tp_instance_p->pdu.iso15765_protocol_data.length = 0;

	can_tp_instance_p->pdu.iso15765_protocol_data.result[DATA_LAYER] = N_OK;
	can_tp_instance_p->pdu.iso15765_protocol_data.result[NETWORK_LAYER] = N_OK;
	can_tp_instance_p->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = N_OK;

	for (data_idx=0; data_idx<CAN_TP_BUFFER_SIZE; data_idx++) {
		can_tp_instance_p->pdu.iso15765_service_data.data[data_idx] = 0;
	}
	can_tp_instance_p->pdu.iso15765_service_data.buffer_idx = 0;

	can_tp_instance_p->rx_fsm.current_rx_signal = rx_default_signal;
	can_tp_instance_p->rx_fsm.current_rx_state = RX_DEFAULT_STATE;
	can_tp_instance_p->rx_fsm.new_rx_signal = rx_default_signal;

	can_tp_instance_p->tx_fsm.current_tx_signal = tx_default_signal;
	can_tp_instance_p->tx_fsm.current_tx_state = DEFAULT_TX_STATE;
	can_tp_instance_p->tx_fsm.new_tx_signal = tx_default_signal;

	can_tp_instance_p->timer.current_signal = DEFAULT_TP_TIMER_SIGNAL;
	can_tp_instance_p->timer.current_state = DEFAULT_STATE;
	can_tp_instance_p->timer.new_signal = DEFAULT_TP_TIMER_SIGNAL;
	can_tp_instance_p->timer.first_tp_time_measurement = 0;

	can_tp_instance_p->number_of_unprocessed_bytes = 0;
	can_tp_instance_p->sequence_number_counter = 0;
	can_tp_instance_p->handled_message_counter = 0;
	can_tp_instance_p->wait_frame_counter = 0;
}

enum iso15765_result set_iso15765_parameter(struct can_tp_iso15765_parameter_s* parameter_p, enum can_tp_parameter parameter_name, unsigned int value)
{
	switch (parameter_name) {
	case BLOCK_SIZE:
		if(value <= MAX_BLOCK_SIZE) {
			parameter_p->block_size = value;
			return N_OK;
		} else {
			parameter_p->block_size = MAX_BLOCK_SIZE;
			return N_ERROR;
		}
	case SEPARATION_TIME:
		if (value <= 0x7F) {
			// TODO n_timeout_parameters.max_time_c_sender = calculate_max_time_c_sender(value)

			//value - milliseconds
			parameter_p->separation_time = value;
			return N_OK;
		} else if ((value >= 0xF1 && value <=0xF9)) {
			//microseconds range 0xF1- 0xF9: F1 represents 100, F9 represents 900
			//uds_parameter->separation_time = calculate_st_time(value);TODO

			//n_timeout_parameters.max_time_c_sender = calculate_max_time_c_sender(value)
			return N_OK;
		} else {
			//n_timeout_parameters.max_time_c_sender = calculate_max_time_c_sender(value)

			//set max value
			return N_ERROR;
		}
	case WFT_MAX:
		if (value <= 0xFF) {
			parameter_p->wtf_max = value;
			return N_OK;
		} else {
			parameter_p->wtf_max = 5;
			return N_ERROR;
		}
		break;
	case PADDING_VALUE:
		if (value <= 0xFF) {
			parameter_p->padding_value = value;
			return N_OK;
		} else {
			parameter_p->padding_value = 0x55;
			return N_ERROR;
		}
		break;
		//--------------------------------TIMEOUTS
	case AS_TIMEOUT:
		if (value <= 0x4E20) { //TODO timeout min
			parameter_p->max_time_value.a_sender = value;
			return N_OK;
		} else {
			parameter_p->max_time_value.a_sender = 25;
			return N_ERROR;
		}
	case BS_TIMEOUT:
		if (value <= 0x4E20)  { //TODO timeout min
			parameter_p->max_time_value.b_sender = value;
			return N_OK;
		} else {
			parameter_p->max_time_value.b_sender = 250;
			return N_ERROR;
		}
	case CS_TIMEOUT:
		if (value <= 0x4E20)  { //TODO timeout min
			if (value >= parameter_p->separation_time) { // TODO if separation_time is not initialized(eq zero or defaul value)
				parameter_p->max_time_value.c_sender = value;
			} else {
				parameter_p->max_time_value.c_sender = parameter_p->separation_time;
			}
			return N_OK;
		} else {
			parameter_p->max_time_value.c_sender = 25;
			return N_ERROR;
		}
	case AR_TIMEOUT:
		if (value <= 0x4E20) //TODO timeout min
		{ //TODO timeout min
			parameter_p->max_time_value.a_receiver = value;
			return N_OK;
		} else {
			parameter_p->max_time_value.a_receiver = 25;
			return N_ERROR;
		}
	case BR_TIMEOUT:
		if (value <= 0x4E20) { //TODO timeout min
			parameter_p->max_time_value.b_receiver = value;
			return N_OK;
		} else {
			parameter_p->max_time_value.b_receiver = 25;
			return N_ERROR;
		}
	case CR_TIMEOUT:
		if (value <= 0x4E20) { //TODO timeout min
			parameter_p->max_time_value.c_receiver = value;
			return N_OK;
		} else {
			parameter_p->max_time_value.c_receiver = 250;
			return N_ERROR;
		}
	case SERVER_ADDRESS:
		//need to search in can_initialization.c this ID
		if (value <= 0x1FFFFFFF) {
			parameter_p->server_address = value;
			return N_OK;
		} else {
			parameter_p->server_address = 0x7E0;
			return N_ERROR;
		}
	case CLIENT_ADDRESS:
		//need to search in can_initialization.c this ID
		if (value <= 0x1FFFFFFF) {
			parameter_p->client_address = value;
			return N_OK;
		} else {
			parameter_p->client_address = 0x7E8;
			return N_ERROR;
		}
	case BROADCAST_ADDRESS:
		//need to search in can_initialization.c this ID
		if (value <= 0x1FFFFFFF) {
			parameter_p->broadcast_address = value;
			return N_OK;
		} else {
			parameter_p->broadcast_address = 0x7DF;
			return N_ERROR;
		}
	case API_VERSION:
	case J1939_PRIORITY:
	default:
		return N_ERROR;
	}
}

static void can_iso15765_parameters_init_config(struct can_tp_iso15765_parameter_s* parameter_p)
{
	parameter_p->block_size = 10;
	parameter_p->wtf_max = 5;
	parameter_p->separation_time = 10;
	parameter_p->padding_value = 0x55;
	parameter_p->max_time_value.a_receiver = 25;
	parameter_p->max_time_value.b_receiver = 25;
	parameter_p->max_time_value.c_receiver = 250;
	parameter_p->max_time_value.a_sender = 25;
	parameter_p->max_time_value.b_sender = 250;
	parameter_p->max_time_value.c_sender = 25;
	parameter_p->server_address  = 0x7E0;
	parameter_p->client_address = 0x7E8;
	parameter_p->broadcast_address = 0x7DF;
}
