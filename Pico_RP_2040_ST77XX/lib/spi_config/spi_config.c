//----------------------------------------------------------------------------------------------------
//(C) 2025 YuriYuri (Yuriy Golovin)
//----------------------------------------------------------------------------------------------------
#include "spi_config.h"

void spi_config_init(void)
{
  spi_init(ST77XX_SPI_PORT, ST77XX_FREQUNCY_SPI);

  gpio_set_function(ST77XX_PIN_MISO,  GPIO_FUNC_SPI);
  gpio_set_function(ST77XX_PIN_CS,    GPIO_FUNC_SPI);
  gpio_set_function(ST77XX_PIN_SCK,   GPIO_FUNC_SPI);
  gpio_set_function(ST77XX_PIN_MOSI,  GPIO_FUNC_SPI);

  gpio_init(ST77XX_PIN_RST);
  gpio_init(ST77XX_PIN_DC);
  gpio_init(ST77XX_PIN_BLK);

  gpio_set_dir(ST77XX_PIN_CS,   GPIO_OUT);
  gpio_set_dir(ST77XX_PIN_RST,  GPIO_OUT);
  gpio_set_dir(ST77XX_PIN_DC,   GPIO_OUT);
  gpio_set_dir(ST77XX_PIN_BLK,  GPIO_OUT);

  gpio_put(ST77XX_PIN_CS,   1);
  gpio_put(ST77XX_PIN_RST,  1);
  gpio_put(ST77XX_PIN_DC,   1);
  gpio_put(ST77XX_PIN_BLK,  1);
}