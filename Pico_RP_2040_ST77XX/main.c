//----------------------------------------------------------------------------------------------------
//(C) 2025 YuriYuri (Yuriy Golovin)
//----------------------------------------------------------------------------------------------------
#include "main.h"

int main()
{
  spi_config_init();
  st77xx_init();
  st77xx_clear_screen(ST77XX_BLACK);
  
  while (1)
  {
    st77xx_draw_poly(3, 90, 90, ST77XX_WHITE);
    sleep_ms(1000);
    st77xx_clear_screen(ST77XX_BLACK);

    st77xx_draw_poly(7, 90, 90, ST77XX_CYAN);
    sleep_ms(1000);
    st77xx_clear_screen(ST77XX_BLACK);

    st77xx_draw_circle(90, ST77XX_YELLOW);
    sleep_ms(1000);
    st77xx_clear_screen(ST77XX_BLACK);

    st77xx_draw_heart(ST77XX_MAGENTA);
    sleep_ms(1000);
    st77xx_clear_screen(ST77XX_BLACK);

    st77xx_draw_curveLissajous(ST77XX_GREEN);
    sleep_ms(1000);
    st77xx_clear_screen(ST77XX_BLACK);

    st77xx_print_line(5, 00, "СЪЕШЬ ЖЕ ЕЩЕ", ST77XX_WHITE, ST77XX_BLACK);
    st77xx_print_line(5, 10, "ЭТИХ МЯГКИХ", ST77XX_WHITE, ST77XX_BLACK);
    st77xx_print_line(5, 20, "ФРАНЦУЗСКИХ", ST77XX_WHITE, ST77XX_BLACK);
    st77xx_print_line(5, 30, "БУЛОК", ST77XX_WHITE, ST77XX_BLACK);
    st77xx_print_line(5, 40, "ДА", ST77XX_WHITE, ST77XX_BLACK);
    st77xx_print_line(5, 50, "ВЫПЕЙ ЧАЮ", ST77XX_WHITE, ST77XX_BLACK);

    st77xx_print_line(5, 70, "в чащах юга", ST77XX_WHITE, ST77XX_BLACK);
    st77xx_print_line(5, 80, "жил бы цитрус", ST77XX_WHITE, ST77XX_BLACK);
    st77xx_print_line(5, 90, "да", ST77XX_WHITE, ST77XX_BLACK);
    st77xx_print_line(5, 100, "но фальшивый", ST77XX_WHITE, ST77XX_BLACK);
    st77xx_print_line(5, 110, "экземпляр", ST77XX_WHITE, ST77XX_BLACK);
    sleep_ms(1000);
    st77xx_clear_screen(ST77XX_BLACK);

    st77xx_draw_img(0, 0, 150, 150, image_data_Asuka);
    sleep_ms(1000);
    st77xx_clear_screen(ST77XX_BLACK);
  }
}