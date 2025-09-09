//----------------------------------------------------------------------------------------------------
// (C) 2025 YuriYuri (Yuriy Golovin)
//----------------------------------------------------------------------------------------------------
#include "sd_card.h"

//----------------------------------------------------------------------------------------------------
// Implemented only for Pico RP2040
// If you want to use a other microcontroller. This function need to be implemented
//----------------------------------------------------------------------------------------------------
void sd_card_write(uint8_t *sd_card_data_write, uint16_t sd_card_write_size)
{
  spi_write_blocking(SPI_PORT, sd_card_data_write, sd_card_write_size);
}
void sd_card_read(uint8_t *sd_card_data_read, uint16_t sd_card_read_size)
{
  spi_read_blocking(SPI_PORT, 0xFF, sd_card_data_read, sd_card_read_size);
}
void sd_card_send_command(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3, uint8_t arg4, uint8_t crc)
{
  uint8_t packet_cmd[6] = {cmd, arg1, arg2, arg3, arg4, crc};
  spi_write_blocking(SPI_PORT, packet_cmd, 6);
}
void sd_card_send_cs(bool cs_send)
{
  gpio_put(PIN_CS, cs_send);
}
uint32_t sd_card_get_tick(void)
{
  return to_ms_since_boot(get_absolute_time());
}
void sd_card_spi_frequency_work(uint32_t spi_frequency)
{
  spi_init(SPI_PORT, spi_frequency);
}
//----------------------------------------------------------------------------------------------------
// This function don't need to be implemented
//----------------------------------------------------------------------------------------------------
uint8_t sd_card_check_R1(void)
{
  uint8_t result_R1[] = {0xFF};
  uint32_t start_wait = sd_card_get_tick();

  while (sd_card_get_tick() - start_wait < 1000)
  {
    sd_card_read(result_R1, 1);
    if (result_R1[0] == 0x00 || result_R1[0] == 0x01) return result_R1[0];
  }
  return result_R1[0];  // Error
}
uint8_t sd_card_check_R3(void)
{
  uint8_t result_R3[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  result_R3[0] = sd_card_check_R1();

  if (result_R3[0] == 0x00 || result_R3[0] == 0x01)
  {
    uint8_t buff[1] = {0};
    for (uint8_t i = 1; i < 5; i++)
    {
      sd_card_read(buff, 1);
      result_R3[i] = buff[0];
    }
    //printf("R3 response: %02X %02X %02X %02X %02X\n", result_R3[0], result_R3[1], result_R3[2], result_R3[3], result_R3[4]);
    return result_R3[0];  // OK
  }
  return result_R3[0];  // Error
}
uint8_t sd_card_check_R7(void)
{
  uint8_t result_R7[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  result_R7[0] = sd_card_check_R1();

  if (result_R7[0] == 0x00 || result_R7[0] == 0x01)
  {
    uint8_t buff[1] = {0};
    for (uint8_t i = 1; i < 5; i++)
    {
      sd_card_read(buff, 1);
      result_R7[i] = buff[0];
    }
    return result_R7[4];  // OK
  }
  return result_R7[0];  // Error
}
bool sd_card_check_busy(void)
{
  uint8_t result_busy[] = {0};
  uint32_t start_wait = sd_card_get_tick();

  while (sd_card_get_tick() - start_wait < 1000)
  {
    sd_card_read(result_busy, 1);
    if (result_busy[0] == 0xFF) return true;
  }
  return false;
}
uint8_t sd_card_init(void)
{
  uint8_t result_init_sd_card = 0;
  uint8_t buff_start[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  uint8_t buff[] = {0xFF};

  sd_card_write(buff, 8);
  //----------SendCMD0----------------------------------------------------------------------------------
  sd_card_send_cs(0);
  sd_card_send_command(CMD0, 0x00, 0x00, 0x00, 0x00, 0x95);
  //----------CheckCMD0---------------------------------------------------------------------------------
  result_init_sd_card = sd_card_check_R1();
  sd_card_write(buff, 1);
  //printf("CMD0: %X\n", result_init_sd_card);
  //----------ErrorCMD0---------------------------------------------------------------------------------
  if (result_init_sd_card != 0x01) 
  {
    sd_card_send_cs(1);
    return 1;
  }
  //----------SendCMD8----------------------------------------------------------------------------------
  sd_card_send_command(CMD8, 0x00, 0x00, 0x01, 0xAA, 0x87);
  sleep_ms(10);
  //----------CheckCMD8---------------------------------------------------------------------------------
  result_init_sd_card = sd_card_check_R7();
  sd_card_write(buff, 1);
  //printf("CMD8: %X\n", result_init_sd_card);
  //----------ErrorCMD8---------------------------------------------------------------------------------
  if (result_init_sd_card != 0xAA) 
  {
    sd_card_send_cs(1);
    return 1;
  }
  //----------SendACMD58--------------------------------------------------------------------------------
  sd_card_send_command(CMD58, 0x00, 0x00, 0x00, 0x00, 0xFD);
  //----------CheckCMD58--------------------------------------------------------------------------------
  result_init_sd_card = sd_card_check_R3();
  sd_card_write(buff, 1);
  //----------ErrorCMD58--------------------------------------------------------------------------------
  if (result_init_sd_card > 0x01) 
  {
    sd_card_send_cs(1);
    return 1;
  }
  //----------SendACMD41--------------------------------------------------------------------------------
  uint32_t start_wait = sd_card_get_tick();

  while (sd_card_get_tick() - start_wait < 1000)
  {
    sd_card_send_command(CMD55, 0x00, 0x00, 0x00, 0x00, 0x65);
    result_init_sd_card = sd_card_check_R1();
    //printf("CMD55: %X\n", result_init_sd_card);
    sd_card_write(buff, 1);

    sd_card_send_command(ACMD41, 0x40, 0x00, 0x00, 0x00, 0x77);
    result_init_sd_card = sd_card_check_R1();
    //printf("CMD41: %X\n", result_init_sd_card);
    sd_card_write(buff, 1);
    if (result_init_sd_card == 0x00) break;
  }
  //----------SendCMD58---------------------------------------------------------------------------------
  if (result_init_sd_card == 0x00)
  {
    sd_card_send_command(CMD58, 0x00, 0x00, 0x00, 0x00, 0xFD);
    //----------CheckCMD58--------------------------------------------------------------------------------
    result_init_sd_card = sd_card_check_R3();
    sd_card_write(buff, 1);
    sd_card_send_cs(1);
    //printf("OK INIT: \n");
    sd_card_spi_frequency_work(SD_CARD_FREQUNCY_SPI);
    return 0;
  }
  sd_card_send_cs(1);
  //printf("ERROR ACMD41: \n");
  return 1;
}
uint8_t sd_card_write_fatfs(uint8_t *buff_write, uint8_t data_0, uint8_t data_1, uint8_t data_2, uint8_t data_3)
{
  uint8_t result_w[] = {0};
  uint8_t buff[] = {0};

  //----------SendCMD24---------------------------------------------------------------------------------
  sd_card_send_cs(0);
  sd_card_send_command(CMD24, data_0, data_1, data_2, data_3, 0xFF);
  //----------CheckCMD24----------------------------------- ---------------------------------------------
  result_w[0] = sd_card_check_R1();
  //printf("CMD24: %X\n", result_w[0]);
  //----------ErrorCMD24--------------------------------------------------------------------------------
  if (result_w[0] != 0x00) 
  {
    sd_card_send_cs(1);
    return 1;
  }
  //----------CheckBusyToken----------------------------------------------------------------------------
  if (sd_card_check_busy() == false)
  {
    return 1;
    //printf("ERROR wait");
  }
  //----------SendStartBlockToken-----------------------------------------------------------------------
  buff[0] = 0xFE;
  sd_card_write(buff, 1);
  //----------SendData----------------------------------------------------------------------------------
  sd_card_write(buff_write, 512);
  //----------SendCRC-----------------------------------------------------------------------------------
  buff[0] = 0xFF;
  sd_card_write(buff, 1);
  sd_card_write(buff, 1);
  //----------CheckResponseToken------------------------------------------------------------------------
  sd_card_read(result_w, 1);
  if (result_w[0] != 0xE5)
  {
    //printf("Data Response Token: %X\n", result_w[0]);
    //printf("ERROR write: %X\n", result_w[0]);
    sd_card_send_cs(1);
    return 1;
  } 
  //printf("Data Response Token: %X\n", result_w[0]);
  //----------CheckBusyToken----------------------------------------------------------------------------
  if (sd_card_check_busy() == false)
  {
    return 1;
    //printf("ERROR wait");
  }
  //printf("OK write:\n");
  sd_card_send_cs(1);
  return 0;
} 
uint8_t sd_card_read_fatfs(uint8_t *buff_read, uint8_t data_0, uint8_t data_1, uint8_t data_2, uint8_t data_3)
{
  uint8_t buf_CRC[2] = {0, 0};
  uint8_t result_r[] = {0};

  //----------SendCMD17-------------------------------------------------------------
  sd_card_send_cs(0);
  sd_card_send_command(CMD17, data_0, data_1, data_2, data_3, 0xFF);
  //----------CheckCMD17------------------------------------------------------------
  result_r[0] = sd_card_check_R1();
  //printf("CMD17: %X\n", result_r[0]);
  //----------ErrorCMD17------------------------------------------------------------
  if (result_r[0] != 0x00) 
  {
    sd_card_send_cs(1);
    return result_r[0];
  }
  //----------CheckStartBlockToken--------------------------------------------------
  uint32_t start_wait = sd_card_get_tick();

  while (sd_card_get_tick() - start_wait < 1000)
  {
    sd_card_read(result_r, 1); 
    if (result_r[0] == 0xFE) break;
  }
  if (result_r[0] != 0xFE)
  {
    //printf("ERROR read: %X\n", result_r[0]);
    sd_card_send_cs(1);
    return 1;
  } 
  //----------GetData---------------------------------------------------------------
  sd_card_read(buff_read, 512);
  //----------GetCRC----------------------------------------------------------------
  sd_card_read(buf_CRC, 2); 
  //printf("OK read:\n");
  sd_card_send_cs(1);
  return 0;
}