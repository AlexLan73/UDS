#include "calc_chksum_XOR8.h"
uint8 calc_chksum_XOR8(uint8* buffer_pu8, uint8 dlc_u8, uint8 bitpos_u8)
{
	sint8  cnt_s8=0;
    uint8  data_u8=0;
    uint8  chksum_u8=0;
    uint8  chksumbyte_u8=0;
                // CRC initial value
    chksum_u8 = 0x00;

                // get position of checksum in buffer
    chksumbyte_u8=bitpos_u8/8;

    for (cnt_s8 = 0; (uint8)cnt_s8 < dlc_u8; cnt_s8++) {

        if((uint8)cnt_s8 != chksumbyte_u8) {
            data_u8 = buffer_pu8[(uint8)cnt_s8];
            chksum_u8   = chksum_u8 ^ data_u8;
        }

    }
    return (chksum_u8);
}



