#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <stdint.h>
#include <stdio.h>

typedef struct
{
  const uint8_t r;
  const uint8_t g;
  const uint8_t b;

} Pixel;

typedef struct
{
  int width;
  int height;
  uint16_t maximum_color_value;
} Image;

Image *parse_ppm_image(FILE *image);

void draw_ppm(SDL_Window *p_window, SDL_Surface *p_window_surface, Image *img,
              FILE *image);

void destroy_image(Image *img);
