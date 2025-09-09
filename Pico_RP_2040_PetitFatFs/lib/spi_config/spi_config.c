//----------------------------------------------------------------------------------------------------
//(C) 2025 YuriYuri (Yuriy Golovin)
//----------------------------------------------------------------------------------------------------
#include "spi_config.h"

void spi_config_init(void)
{
  spi_init(SPI_PORT, 300*1000);

  gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
  gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
  gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
  gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

  gpio_set_dir(PIN_CS, GPIO_OUT);
  gpio_put(PIN_CS, 1);
}