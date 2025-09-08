//----------------------------------------------------------------------------------------------------
//(C) 2025 YuriYuri (Yuriy Golovin)
//----------------------------------------------------------------------------------------------------
#include "st77xx_graph.h"

void st77xx_draw_buff(uint16_t st77xx_buff_x0, uint16_t st77xx_buff_y0, uint16_t st77xx_buff_x1, uint16_t st77xx_buff_y1, uint16_t *st77xx_point_buff, bool flag_img)
{
  uint32_t st77xx_buff_size = 0;
  uint32_t st77xx_buff_area = (st77xx_buff_x1 - st77xx_buff_x0) * (st77xx_buff_y1 - st77xx_buff_y0);

  if (st77xx_buff_area < ST77XX_SIZE_BUFF_SCREEN / 2)
  {
    st77xx_buff_size = 2 * st77xx_buff_area;
  } 
  else
  {
    st77xx_buff_size = ST77XX_SIZE_BUFF_SCREEN;
  }
  
  uint8_t st77xx_buff[st77xx_buff_size];
  uint32_t st77xx_buff_quantity = (uint32_t)(2 * st77xx_buff_area / st77xx_buff_size);
  uint32_t st77xx_buff_remains =  (uint32_t)(2 * st77xx_buff_area % st77xx_buff_size);

  st77xx_set_col_row_addr(st77xx_buff_x0 + ST77XX_X_OFFSET, st77xx_buff_y0 + ST77XX_Y_OFFSET, st77xx_buff_x1 + ST77XX_X_OFFSET - 1,  st77xx_buff_y1 + ST77XX_Y_OFFSET - 1);

  if(flag_img == true)
  {
    for (uint32_t i = 0; i < st77xx_buff_quantity; i++)
    {
      for (uint32_t j = 0; j < st77xx_buff_size / 2; j++)
      {
          uint16_t buff_img = st77xx_point_buff[(i * (st77xx_buff_size / 2)) + j];
          st77xx_buff[2 * j]     = buff_img >> 8;
          st77xx_buff[2 * j + 1] = buff_img;
      }
      st77xx_write(st77xx_buff, st77xx_buff_size);
    }
    if (st77xx_buff_remains)
    {
      for (uint32_t j = 0; j < st77xx_buff_remains / 2; j++)
      {
          uint16_t buff_color = st77xx_point_buff[(st77xx_buff_quantity * (st77xx_buff_size / 2)) + j];
          st77xx_buff[2 * j]     = buff_color >> 8;
          st77xx_buff[2 * j + 1] = buff_color;
      }
      st77xx_write(st77xx_buff, st77xx_buff_remains);
    }
  }
  else
  {
    uint16_t buff_color = *st77xx_point_buff;
    for (uint32_t i = 0; i < st77xx_buff_size / 2; i++)
    {
      st77xx_buff[2 * i]     = buff_color >> 8;
      st77xx_buff[2 * i + 1] = buff_color;
    }

    for(uint32_t j = 0; j < st77xx_buff_quantity; j++) 
    {
      st77xx_write(st77xx_buff, st77xx_buff_size);
    }
    if (st77xx_buff_remains)
    {
      st77xx_write(st77xx_buff, st77xx_buff_remains);
    }
  }
}
void st77xx_clear_screen(uint16_t clear_color)
{
  st77xx_draw_buff(0, 0, ST77XX_X_SIZE, ST77XX_Y_SIZE, &clear_color, false);
}
void st77xx_draw_rect(uint16_t rect_x0, uint16_t rect_y0, uint16_t rect_x1, uint16_t rect_y1, uint16_t rect_color)
{
  st77xx_draw_buff(rect_x0, rect_y0, rect_x1, rect_y1, &rect_color, false);
}
void st77xx_draw_pixel(uint16_t pixel_x, uint16_t pixel_y, uint16_t pixel_color)
{
  uint8_t pixel_color_buff[2];
  pixel_color_buff[0] = pixel_color >> 8;
  pixel_color_buff[1] = pixel_color;

  st77xx_set_col_row_addr(pixel_x + ST77XX_X_OFFSET, pixel_y + ST77XX_Y_OFFSET, pixel_x + 1 + ST77XX_X_OFFSET, pixel_y + 1 + ST77XX_Y_OFFSET);
  st77xx_write(pixel_color_buff, 2);
}
void st77xx_draw_line(uint16_t line_x0, uint16_t line_y0, uint16_t line_x1, uint16_t line_y1, uint16_t line_color)
{
  int16_t dx = abs(line_x1 - line_x0);
  int16_t dy = abs(line_y1 - line_y0);

  int16_t sx;
  if (line_x0 < line_x1)
    sx = 1;
  else
    sx = -1;

  int16_t sy;
  if (line_y0 < line_y1)
    sy = 1;
  else
    sy = -1;

  int16_t err = dx - dy;

  while (1)
  {
    st77xx_draw_pixel(line_x0, line_y0, line_color);
    if (line_x0 == line_x1 && line_y0 == line_y1)
      break;

    int16_t err2 = 2 * err;

    if (err2 >= (- dy) )
    {
      err -= dy;
      line_x0 += sx;
    }
    if (err2 <= dx)
    {
      err += dx;
      line_y0 += sy;
    }
  }
}
void st77xx_draw_poly(uint8_t facets_poly, uint16_t radius_poly, uint16_t degree_poly, uint16_t facets_color_poly)
{
  float offset_x = (int)((ST77XX_X_SIZE - ST77XX_X_OFFSET) / 2);
  float offset_y = (int)((ST77XX_Y_SIZE - ST77XX_Y_OFFSET) / 2);

  for (uint8_t n = 0; n < facets_poly; n++)
  {
    float radians = cos((M_PI * (degree_poly + (n * 360 / facets_poly)) / 180));
    uint16_t x0 = (int)(radius_poly * radians) + offset_x;    

    radians = sin((M_PI * (degree_poly + (n * 360 / facets_poly)) / 180));
    uint16_t y0 = (int)(radius_poly * radians) + offset_y;   

    radians = cos((M_PI * (degree_poly + ((n + 1) * 360 / facets_poly)) / 180));
    int x1 = (int)(radius_poly * radians) + offset_x;    
   
    radians = sin((M_PI * (degree_poly + ((n + 1) * 360 / facets_poly)) / 180));
    int y1 = (int)(radius_poly * radians) + offset_y; 

    st77xx_draw_line(x0, y0, x1, y1, facets_color_poly);
  }
}
void st77xx_draw_circle(uint16_t radius_circle, uint16_t color_circle)
{
  float offset_x = (ST77XX_X_SIZE - ST77XX_X_OFFSET) / 2;
  float offset_y = (ST77XX_Y_SIZE - ST77XX_Y_OFFSET) / 2;

  for (uint16_t t = 0; t < (4 * 90); t++)
  {
      int t0 = t;
      int t1 = t + 1;

      float radians = sin(M_PI * t0 / 180);
      int x0 = (int)((radius_circle * radians) + offset_x);

      radians = sin(M_PI * t1 / 180);
      int x1 = (int)((radius_circle * radians) + offset_x);

      radians = cos(M_PI * t0 / 180);
      int y0 = (int)((radius_circle * radians) + offset_y);

      radians = cos(M_PI * t1 / 180);
      int y1 = (int)((radius_circle * radians) + offset_y);
      
      st77xx_draw_line(x0, y0, x1, y1, color_circle);
  }
}
void st77xx_draw_heart(uint16_t heart_color)
{
    float offset_x = (ST77XX_X_SIZE - ST77XX_X_OFFSET) / 2;
    float offset_y = (ST77XX_Y_SIZE - ST77XX_Y_OFFSET) / 2;

    float amplitude_x = 3 * offset_x / 50;
    float amplitude_y = -2  * offset_x / 50;

    for (uint16_t t = 0; t < (4 * 90); t++)
    {
      float radians = 12 * sin(M_PI * t / 180) * sin(M_PI * t / 180) * sin(M_PI * t / 180);
      int x0 = (int)((amplitude_x * radians) + offset_x);

      radians = 12 * sin(M_PI * (t + 1) / 180) * sin(M_PI * (t + 1) / 180) * sin(M_PI * (t + 1) / 180);
      int x1 = (int)((amplitude_x * radians) + offset_x);

      radians = 13 * cos(M_PI * t / 180) - 5 * cos(2 * M_PI * t / 180) - 2 * cos(3 * M_PI * t / 180) - cos(4 * M_PI * t / 180);
      int y0 = (int)((amplitude_y * radians) + offset_y);

      radians = 13 * cos(M_PI * (t + 1) / 180) - 5 * cos(2 * M_PI * (t + 1) / 180) - 2 * cos(3 * M_PI * (t + 1) / 180) - cos(4 * M_PI * (t + 1) / 180);
      int y1 = (int)((amplitude_y * radians) + offset_y);

      st77xx_draw_line(x0, y0, x1, y1, heart_color);
    }
}
void st77xx_draw_curveLissajous(uint16_t curveLissajous_color)
{
  float offset_x = (ST77XX_X_SIZE - ST77XX_X_OFFSET) / 2;
  float offset_y = (ST77XX_Y_SIZE - ST77XX_Y_OFFSET) / 2;
  
  int phase_shift = 0;

  float amplitude_x = 1 * (ST77XX_X_SIZE - ST77XX_X_OFFSET) / 3;
  int frequency_x = 11;

  float amplitude_y = 1 * (ST77XX_X_SIZE - ST77XX_X_OFFSET) / 3;
  int frequency_y = 12;

  for (uint16_t t = 0; t < (4 * 90); t++)
  {
    float radians = sin((M_PI * t * frequency_x / 180) + (M_PI * phase_shift / 180));
    int x0 = (int)((amplitude_x * radians) + offset_x);

    radians = sin((M_PI *(t + 1) * frequency_x / 180) + (M_PI * phase_shift / 180));
    int x1 = (int)((amplitude_x * radians) + offset_x);

    radians = sin(M_PI * t  * frequency_y / 180);
    int y0 = (int)((amplitude_y * radians) + offset_y);

    radians = sin(M_PI * (t + 1) * frequency_y / 180);
    int y1 = (int)((amplitude_y * radians) + offset_y);
      
    st77xx_draw_line(x0, y0, x1, y1, curveLissajous_color);
  }
}
void st77xx_draw_img(uint16_t img_x0, uint16_t img_y0, uint16_t img_x1, uint16_t img_y1, uint16_t *img_buff)
{
  st77xx_draw_buff(img_x0, img_y0, img_x1, img_y1, img_buff, true);
}