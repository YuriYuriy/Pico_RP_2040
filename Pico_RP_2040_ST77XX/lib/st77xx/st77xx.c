//----------------------------------------------------------------------------------------------------
//(C) 2025 YuriYuri (Yuriy Golovin)
//----------------------------------------------------------------------------------------------------
#include "st77xx.h"
#include "commands_st7789v.h"
#include "commands_st7735s.h"

//----------------------------------------------------------------------------------------------------
// Implemented only for Pico RP2040
// If you want to use a other microcontroller. This function need to be implemented
//----------------------------------------------------------------------------------------------------
void st77xx_write(uint8_t *st77xx_data_buff, uint32_t st77xx_size_buff)
{
  spi_write_blocking(ST77XX_SPI_PORT, st77xx_data_buff, st77xx_size_buff);
}
void st77xx_delay_ms(uint16_t st77xx_delay)
{
  sleep_ms(st77xx_delay);
}
void st77xx_reset_hardware(void)
{
  gpio_put(ST77XX_PIN_RST, 0);
  sleep_ms(10);
  gpio_put(ST77XX_PIN_RST, 1);
}
void st77xx_dc(bool st77xx_dc_data)
{
  gpio_put(ST77XX_PIN_DC, st77xx_dc_data);
}
//----------------------------------------------------------------------------------------------------
// This function don't need to be implemented
//----------------------------------------------------------------------------------------------------
void st77xx_send_command(uint8_t st77xx_command)
{
  st77xx_dc(ST77XX_DC_COMMAND);
  st77xx_write(&st77xx_command, 1);
}
void st77xx_send_data(uint8_t st77xx_data)
{
  st77xx_dc(ST77XX_DC_DATA);
  st77xx_write(&st77xx_data, 1);
}
void st77xx_init(void)
{
  st77xx_reset_hardware();

  #ifdef ST7735S
    st77xx_send_command(ST7735S_SWRESET);
    st77xx_delay_ms(120);

    st77xx_send_command(ST7735S_SLPOUT);
    st77xx_delay_ms(120);

    st77xx_send_command(ST7735S_INVOFF);

    st77xx_send_command(ST7735S_MADCTL);
    st77xx_send_data(0x00);

    st77xx_send_command(ST7735S_COLMOD);
    st77xx_send_data(0x55);

    st77xx_send_command(ST7789V_GAMSET);
    st77xx_send_data(0x08);

    st77xx_send_command(ST7735S_NORON);
    st77xx_send_command(ST7735S_DISPON);
  #endif
  #ifdef ST7789V
    st77xx_send_command(ST7789V_SWRESET);
    st77xx_delay_ms(120);

    st77xx_send_command(ST7789V_SLPOUT);
    st77xx_delay_ms(120);

    st77xx_send_command(ST7789V_INVOFF);

    st77xx_send_command(ST7789V_MADCTL);
    st77xx_send_data(0x00);

    st77xx_send_command(ST7789V_COLMOD);
    st77xx_send_data(0x55);

    st77xx_send_command(ST7789V_GAMSET);
    st77xx_send_data(0x08);

    st77xx_send_command(ST7789V_NORON);
    st77xx_send_command(ST7789V_DISPON);
  #endif
  st77xx_clear_screen(ST77XX_BLACK);
}
void st77xx_set_col_row_addr(uint16_t st77xx_x_start, uint16_t st77xx_y_start, uint16_t st77xx_x_stop, uint16_t st77xx_y_stop)
{
  #ifdef ST7735S
    st77xx_send_command(ST7735S_CASET);
    uint8_t st77xx_col_row_buff[4];
    st77xx_col_row_buff[0] = st77xx_x_start >> 8;
    st77xx_col_row_buff[1] = st77xx_x_start;
    st77xx_col_row_buff[2] = st77xx_x_stop >> 8;
    st77xx_col_row_buff[3] = st77xx_x_stop;
    st77xx_dc(ST77XX_DC_DATA);
    st77xx_write(st77xx_col_row_buff, 4);
    st77xx_send_command(ST7735S_RASET);
    st77xx_col_row_buff[0] = st77xx_y_start >> 8;
    st77xx_col_row_buff[1] = st77xx_y_start;
    st77xx_col_row_buff[2] = st77xx_y_stop >> 8;
    st77xx_col_row_buff[3] = st77xx_y_stop;
    st77xx_dc(ST77XX_DC_DATA);
    st77xx_write(st77xx_col_row_buff, 4);
    st77xx_send_command(ST7735S_RAMWR);
  #endif
  #ifdef ST7789V
    st77xx_send_command(ST7789V_CASET);
    uint8_t st77xx_col_row_buff[4];
    st77xx_col_row_buff[0] = st77xx_x_start >> 8;
    st77xx_col_row_buff[1] = st77xx_x_start;
    st77xx_col_row_buff[2] = st77xx_x_stop >> 8;
    st77xx_col_row_buff[3] = st77xx_x_stop;
    st77xx_dc(ST77XX_DC_DATA);
    st77xx_write(st77xx_col_row_buff, 4);
    st77xx_send_command(ST7789V_RASET);
    st77xx_col_row_buff[0] = st77xx_y_start >> 8;
    st77xx_col_row_buff[1] = st77xx_y_start;
    st77xx_col_row_buff[2] = st77xx_y_stop >> 8;
    st77xx_col_row_buff[3] = st77xx_y_stop;
    st77xx_dc(ST77XX_DC_DATA);
    st77xx_write(st77xx_col_row_buff, 4); 
    st77xx_send_command(ST7789V_RAMWR);
  #endif
  st77xx_dc(ST77XX_DC_DATA);
}