#include <stdint.h>

typedef struct
{
  const uint8_t width;
  const uint8_t height;
  const uint8_t x_origin;
  const uint8_t y_origin;
  const uint16_t x_end;
  const uint16_t y_end;
  const uint8_t pixel_size;
} AspectRatio;

AspectRatio calculate_aspect_ratio(int image_width, int image_height);
