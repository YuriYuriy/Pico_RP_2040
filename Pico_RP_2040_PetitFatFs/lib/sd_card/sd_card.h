//----------------------------------------------------------------------------------------------------
// (C) 2025 YuriYuri (Yuriy Golovin)
//----------------------------------------------------------------------------------------------------
#ifndef _SD_CARD
#define _SD_CARD

#include "main.h"

//----------------------------------------------------------------------------------------------------
// Commands SD Card
//----------------------------------------------------------------------------------------------------
#define CMD0    0x40 + 0   // GO_IDLE_STATE 
#define CMD8    0x40 + 8   // SEND_IF_COND проверки рабочего состояния интерфейса SD-карты
#define CMD10   0x40 + 10  // READ_CSD
#define CMD17   0x40 + 17  // READ_SINGLE_BLOCK
#define CMD24   0x40 + 24  // 
#define CMD55   0x40 + 55  // APP_CMD 
#define CMD58   0x40 + 58  // READ_OCR 
#define ACMD41  0x40 + 41  // SD_SEND_OP_COND инициализации и проверки, завершена ли 

//----------------------------------------------------------------------------------------------------
// Function lib
//----------------------------------------------------------------------------------------------------
uint8_t sd_card_init(void);
uint8_t sd_card_write_fatfs(uint8_t *buff_write, uint8_t data_0, uint8_t data_1, uint8_t data_2, uint8_t data_3);
uint8_t sd_card_read_fatfs(uint8_t *buff_read, uint8_t data_0, uint8_t data_1, uint8_t data_2, uint8_t data_3);

#endif
