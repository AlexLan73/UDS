#ifndef ERR_FLAGS_H
#define ERR_FLAGS_H

typedef struct {
	uint8 NoMsg :1;   //message not received
    uint8 RCErr :1;  //rolling counter error
    uint8 CRCErr:1;  //crc error
    uint8 reserved:1;
    uint8 reserved1:3;
    uint8 firstMsg:1;
} rx_Err_flags_Bits;

typedef union {
    /** \brief Unsigned access */
    uint8            U;
    /** \brief Bitfield access */
    rx_Err_flags_Bits B;
} rx_Err_flags;

#endif /* ERR_FLAGS_H */
