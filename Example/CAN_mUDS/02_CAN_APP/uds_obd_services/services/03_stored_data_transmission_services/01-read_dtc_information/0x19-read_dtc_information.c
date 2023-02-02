#include "read_dtc_information_private.h"

//---------------------------------------------------------------------------------------------------------------
// GLOBAL
//---------------------------------------------------------------------------------------------------------------

uint8 read_dtc_information(struct iso15765_tp_s* response_message, struct iso15765_tp_s*  request_message)
{
	uint8 sub_function = request_message->pdu.iso15765_service_data.data[1] & 0x7F;
	response_message->pdu.iso15765_service_data.buffer_idx = 0;

	switch (sub_function) {
	//------------------------------------------------------
	//RNODTCBSM - reportNumberOfDTCByStatusMask
	//------------------------------------------------------
	case LEV_RNODTCBSM:
		if (request_message->pdu.iso15765_protocol_data.length == RNODTCBSM_LEN) {
			uint8 dtc_status_mask = request_message->pdu.iso15765_service_data.data[2];
			if (status_mask_is_supported(dtc_status_mask)) {
				dtc_count.u = counting_dtc(dtc_status_mask);
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = RDTCIPR;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = dtc_status_availability_mask;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = dtcfid_14229_1dtcf;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = dtc_count.b.high;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = dtc_count.b.low;

				response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
			} else {
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
			}
		} else {
			return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
		}
		break;
	//------------------------------------------------------
	//RDTCBSM - reportDTCByStatusMask
	//------------------------------------------------------
	case LEV_RDTCBSM:
		if (request_message->pdu.iso15765_protocol_data.length == RDTCBSM_LEN) {
			uint8 dtc_status_mask = request_message->pdu.iso15765_service_data.data[2];
			if (status_mask_is_supported(dtc_status_mask)) {
				//Positive responce format is described @on page 200, 14229-1 2013 into table 272

				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = RDTCIPR;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = dtc_status_availability_mask;

				response_message->pdu.iso15765_service_data.buffer_idx = get_dtc_code_and_status(
						response_message,
						response_message->pdu.iso15765_service_data.buffer_idx,
						dtc_status_mask
						);
				response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
			} else {
				response_message->pdu.iso15765_service_data.data[0] = RDTCIPR;
				response_message->pdu.iso15765_service_data.data[1] = sub_function;
				response_message->pdu.iso15765_service_data.data[2] = dtc_status_availability_mask;
				response_message->pdu.iso15765_protocol_data.length = 3;
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
			}
		} else {
			return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
		}
		break;
	//------------------------------------------------------
	//	RDTCSSI - reportDTCSnapshotIdentification
	//------------------------------------------------------
	case LEV_RDTCSSI:
		if (response_message->pdu.iso15765_protocol_data.length == RDTCSSI_LEN) {
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = RDTCIPR;
			response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;

			response_message->pdu.iso15765_service_data.buffer_idx = get_the_snapshot_number_to_the_dtc_number(
					response_message,
					response_message->pdu.iso15765_service_data.buffer_idx
					);

			response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
			return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
		} else {
			return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
		}
		break;
	//------------------------------------------------------
	//RDTCSSBDTC - reportDTCSnapshotRecordByDTCNumber
	//------------------------------------------------------
	case LEV_RDTCSSBDTC:
		if (response_message->pdu.iso15765_protocol_data.length == RDTCSSBDTC_LEN) {
			struct dtc_mask_record_s dtc_record;
			dtc_record.mask.B.high = response_message->pdu.iso15765_service_data.data[2];
			dtc_record.mask.B.middle = response_message->pdu.iso15765_service_data.data[3];
			dtc_record.mask.B.low = response_message->pdu.iso15765_service_data.data[4];
			dtc_record.mask.B.reserved = 0;
			dtc_record.snapshot_number = response_message->pdu.iso15765_service_data.data[5];

//			uint32 dtc_mask_temp = ( ((uint32)dtc_mask.dtcmrec_dtchb)<<16 )+( ((uint16)dtc_mask.dtcmrec_dtcmb)<<8 )+(  dtc_mask.dtcmrec_dtchb );

			if (is_dtc_exists(dtc_record.mask.U)) {
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = RDTCIPR;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = sub_function;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = dtc_record.mask.B.high;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = dtc_record.mask.B.middle;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = dtc_record.mask.B.low;
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = get_status_by_dtc_number(dtc_record.mask.U);
				response_message->pdu.iso15765_service_data.data[response_message->pdu.iso15765_service_data.buffer_idx++] = dtc_record.snapshot_number;
//				response_message->pdu.iso15765_service_data.data[6] = dtcedrn;
//				response_message->pdu.iso15765_service_data.data[7] = dtcssrni;
//				response_message->pdu.iso15765_service_data.data[8] = didb1;//todo
//				response_message->pdu.iso15765_service_data.data[9] = didb2;//todo
//
//				response_message->pdu.iso15765_service_data.data[10] = ed_1;
//				response_message->pdu.iso15765_service_data.data[11] = ed_2;
//				response_message->pdu.iso15765_service_data.data[12] = ed_3;
				response_message->pdu.iso15765_service_data.buffer_idx = get_snapshot_record_by_dtc_number(
						response_message,
						response_message->pdu.iso15765_service_data.buffer_idx,
						dtc_record
						);
				response_message->pdu.iso15765_protocol_data.length = response_message->pdu.iso15765_service_data.buffer_idx;
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_PR;
			} else {
				return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_ROOR;
			}
		} else {
			return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_IMLOIF;
		}
		break;
	//------------------------------------------------------
	//RDTCSDRBRN - reportDTCStoredDataByRecordNumber
	//------------------------------------------------------
//	case LEV_RDTCSDBRN:
//		if (response_message->pdu.iso15765_protocol_data.length == RDTCI_LEN) {
//			uint8 dtcsdrn = response_message->pdu.iso15765_service_data.data[2];
//			if (record_exists(dtcsdrn)) {
//				if (dtcsdrn != 0xFF) {
//					struct kasjdlkajsd;
//					collect_dtc_stored_data(&kasjdlkajsd);
//
//					response_message->pdu.iso15765_service_data.data[0] = RDTCIPR;
//					response_message->pdu.iso15765_service_data.data[1] = sub_function;
//					response_message->pdu.iso15765_service_data.data[2] = dtcsdrn;
//					if (sodtc) {
//						response_message->pdu.iso15765_service_data.data[3] = dtc_and_status[i].dtcasr_dtchb;	// DTCHighByte
//						response_message->pdu.iso15765_service_data.data[4] = dtc_and_status[i].dtcasr_dtcmb;	// DTCMiddleByte
//						response_message->pdu.iso15765_service_data.data[5] = dtc_and_status[i].dtcasr_dtclb;	// DTCLowByte
//						response_message->pdu.iso15765_service_data.data[6] = dtc_and_status[i].dtcasr_sodtc;	// statusOfDTC
//						response_message->pdu.iso15765_service_data.data[7] = dtcssrni;				// DTCSnapshotRecordNumberOfIdentifiers
//
//						uint8 i, n;
//
//						uint8 m = i*n;
//						for ( i = 0; i < dtcssrni; i++ ) {
//							response_message->pdu.iso15765_service_data.data[(8+m)] = didb1;  	// DataIdentifier
//							response_message->pdu.iso15765_service_data.data[(9+m)] = didb2;
//
//							response_message->pdu.iso15765_service_data.data[(10+m)] = ed_1;
//							response_message->pdu.iso15765_service_data.data[(11+m)] = ed_2;
//							response_message->pdu.iso15765_service_data.data[(12+m)] = ed_3;
//						}
//						response_message->pdu.iso15765_protocol_data.length = 6;//TODO now is not correct
//						return NRC_PR;
//					} else {
//						return NRC_PR;
//					}
//				} else {
//					return RDTCIPR;
//				}
//			} else {
//				return NRC_ROOR;
//			}
//		} else {
//			return NRC_IMLOIF;
//		}
//		break;
	//------------------------------------------------------
	//RDTCEDRBDN - reportDTCExtDataRecordByDTCNumber
	//------------------------------------------------------
//	case LEV_RDTCEDRBDN:
//		if (response_message->pdu.iso15765_protocol_data.length == RDTCI_LEN) {
//			dtc_mask.dtcmrec_dtchb = response_message->pdu.iso15765_service_data.data[2];
//			dtc_mask.dtcmrec_dtcmb = response_message->pdu.iso15765_service_data.data[3];
//			dtc_mask.dtcmrec_dtclb = response_message->pdu.iso15765_service_data.data[4];
//
//			uint8 dtcedrn = response_message->pdu.iso15765_service_data.data[5]; // DTCExtDataRecordNumber
//
//			uint32 dtc_mask_temp = ( ((uint32)dtc_mask.dtcmrec_dtchb)<<16 )+( ((uint16)dtc_mask.dtcmrec_dtcmb)<<8 )+(  dtc_mask.dtcmrec_dtchb );
//
//			if (record_exists(dtcedrn)) {
//				response_message->pdu.iso15765_service_data.data[0] = RDTCIPR;
//				response_message->pdu.iso15765_service_data.data[1] = sub_function;
//				response_message->pdu.iso15765_service_data.data[2] = dtc_mask.dtcmrec_dtchb;
//				response_message->pdu.iso15765_service_data.data[3] = dtc_mask.dtcmrec_dtcmb;
//				response_message->pdu.iso15765_service_data.data[4] = dtc_mask.dtcmrec_dtclb;
//
//				if (dtcedrn != 0xFF) {
//					response_message->pdu.iso15765_service_data.data[5] = dtcedrn;
//					response_message->pdu.iso15765_service_data.data[6] = ed_1;
//				} else {
//					uint8 number_data_records = get_ext_data_record_number();
//					for(i = 0; i< number_data_records; i++) {
//						response_message->pdu.iso15765_service_data.data[(5+(2*i))] = dtcedrn[i];
//						response_message->pdu.iso15765_service_data.data[(6+(2*i))] = ed[i];
//					}
//				}
//				response_message->pdu.iso15765_protocol_data.length = 6;//TODO now is not correct
//			}
//		} else {
//			return NRC_IMLOIF;
//		}
//		break;
	default:
		return response_message->pdu.iso15765_protocol_data.result[APPLICATION_LAYER] = NRC_SFNS;
	}
}
//---------------------------------------------------------------------------------------------------------------







//---------------------------------------------------------------------------------------------------------------
// STATIC
//---------------------------------------------------------------------------------------------------------------

static uint16 counting_dtc(uint8 dtc_status_mask)
{
	/*  dsw_0_aaa(channel) Ц массив (256 элементов),
	 *  содержащий результаты диагностики от
	 *  диагностических моделей
	 */

	/*  p_28_statusOfDTC() Ц массив (50 элементов),
	 *  содержащий статусы ошибок
	 */

	/*  Channel Ц указатель на элементы массивов dsw_0_aaa */

	/*  p_28_chHistory () Ц массив (50 элементов),
	 *  содержащий номера каналов (channel),
	 *  в которых диагностика зафиксировала ошибку.
	 *  ≈сли система исправна, все ошибки стерты,
	 *  этот массив будет пустым
	 */

	/*  p_28_dtcHistory() Ц массив (50 элементов),
	 *  содержащий коды неисправностей дл€ каналов,
	 *  в которых диагностика зафиксировала ошибку.
	 *  ≈сли система исправна, все ошибки стерты,
	 *  этот массив будет пустым
	 */

	uint8 number_of_dtc = 0;
	uint8 array_idx;

	for (array_idx = 0; array_idx < 50; array_idx++) {
		if (p_28_chHistory[array_idx] != 0) {
			if ((p_28_statusDTC[array_idx]&dtc_status_mask) == dtc_status_mask) {
				number_of_dtc++;
			}
		}
	}

	return number_of_dtc;
}


//compare status masks, fills structure info_about_dtc; return the number of DTC
static uint16 get_dtc_code_and_status(struct iso15765_tp_s* response_message, uint16 response_message_data_index, uint8 dtc_status_mask)
{
	struct dtc_record_t dtc_record;

	/*  dsw_0_aaa(channel) Ц массив (256 элементов),
	 *  содержащий результаты диагностики от
	 *  диагностических моделей
	 */

	/*  p_28_statusOfDTC() Ц массив (50 элементов),
	 *  содержащий статусы ошибок
	 */

	/*  Channel Ц указатель на элементы массивов dsw_0_aaa */

	/*  p_28_chHistory () Ц массив (50 элементов),
	 *  содержащий номера каналов (channel),
	 *  в которых диагностика зафиксировала ошибку.
	 *  ≈сли система исправна, все ошибки стерты,
	 *  этот массив будет пустым
	 */

	/*  p_28_dtcHistory() Ц массив (50 элементов),
	 *  содержащий коды неисправностей дл€ каналов,
	 *  в которых диагностика зафиксировала ошибку.
	 *  ≈сли система исправна, все ошибки стерты,
	 *  этот массив будет пустым
	 */
	//--------------------------------------------------------------------------------------------
	uint8 array_idx;
	for (array_idx = 0; array_idx < 50; array_idx++) {
		if (p_28_chHistory[array_idx] != 0) {
			if ((p_28_statusDTC[array_idx]&dtc_status_mask) == dtc_status_mask) {
				dtc_record.code.u = p_28_dtcHistory[array_idx];
				dtc_record.status.u = p_28_statusDTC[array_idx];
				response_message->pdu.iso15765_service_data.data[response_message_data_index++] = dtc_record.code.b.high;
				response_message->pdu.iso15765_service_data.data[response_message_data_index++] = dtc_record.code.b.middle;
				response_message->pdu.iso15765_service_data.data[response_message_data_index++] = 00;//dtc_record.code.b.low;
				response_message->pdu.iso15765_service_data.data[response_message_data_index++] = dtc_record.status.u;
			}
		}
	}

	return response_message_data_index;
}

static uint8 get_status_by_dtc_number(uint32 dtc)
{
	uint8 array_idx;
	for (array_idx = 0; array_idx < 50; array_idx++) {
		if (p_28_chHistory[array_idx] != 0) {
			if (p_28_dtcHistory[array_idx] == dtc) {
				return p_28_statusDTC[array_idx];
			}
		}
	}
	return 0;//todo
}

static boolean is_dtc_exists(uint32 dtc)
{
	uint8 array_idx;
	for (array_idx = 0; array_idx < 50; array_idx++) {
		if (p_28_chHistory[array_idx] != 0) {
			if (p_28_dtcHistory[array_idx] == dtc) {
				return TRUE;
			}
		}
	}
	return FALSE;
}

static boolean status_mask_is_supported(uint8 received_status_mask)
{
	if ((dtc_status_availability_mask & received_status_mask) == received_status_mask) {
		return TRUE;
	}
	return FALSE;
}

static uint16 get_snapshot_record_by_dtc_number(struct iso15765_tp_s* response_message, uint16 response_message_data_index, struct dtc_mask_record_s record)
{
//	uint8 array_idx;
//	for (array_idx = 0; array_idx < 50; array_idx++) {
//		if (p_28_chHistory[array_idx] != 0) {
//			if (p_28_dtcHistory[array_idx] == record.mask.U) {
//				if (record.snapshot_number == 1) {
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelSysStatus2FF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelSysStatusFF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelTrimLT2FF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelTrimLTFF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelTrimST2FF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelTrimSTFF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_loadFF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_mafFF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_mapFF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_rvmFF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_spAng0FF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_tairFF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_thrPosFF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_twatFF1[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_vhcSpdFF1[array_idx];
//				} else if (record.snapshot_number == 2) {
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelSysStatus2FF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelSysStatusFF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelTrimLT2FF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelTrimLTFF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelTrimST2FF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_fuelTrimSTFF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_loadFF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_mafFF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_mapFF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_rvmFF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_spAng0FF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_tairFF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_thrPosFF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_twatFF2[array_idx];
//					response_message->pdu.iso15765_service_data.data[response_message_data_index++] = p_28_vhcSpdFF2[array_idx];
//				}
//			}
//		}
//	}

	return response_message_data_index;
}


static uint16 get_the_snapshot_number_to_the_dtc_number(struct iso15765_tp_s* response_message, uint16 response_message_data_index)
{
//	struct dtc_record_t dtc_record;
//	uint8 array_idx;
//	for (array_idx = 0; array_idx < 50; array_idx++) {
//		if (p_28_chHistory[array_idx] != 0) {
//			dtc_record.code.u = p_28_dtcHistory[array_idx];
//			response_message->pdu.iso15765_service_data.data[response_message_data_index++] = dtc_record.code.b.high;
//			response_message->pdu.iso15765_service_data.data[response_message_data_index++] = dtc_record.code.b.middle;
//			response_message->pdu.iso15765_service_data.data[response_message_data_index++] = dtc_record.code.b.low;
//			response_message->pdu.iso15765_service_data.data[response_message_data_index++] = 0x01;
//			// cnt_28_quant = хранит количество возникновени€ ошибки
//			if (cnt_28_quant[array_idx] > 1) {
//				response_message->pdu.iso15765_service_data.data[response_message_data_index++] = dtc_record.code.b.high;
//				response_message->pdu.iso15765_service_data.data[response_message_data_index++] = dtc_record.code.b.middle;
//				response_message->pdu.iso15765_service_data.data[response_message_data_index++] = dtc_record.code.b.low;
//				response_message->pdu.iso15765_service_data.data[response_message_data_index++] = 0x02;
//			}
//		}
//	}

	return response_message_data_index;
}

