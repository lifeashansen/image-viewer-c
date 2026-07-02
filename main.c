#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <complex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sysexits.h>

#include "aspectratio.h"
#include "image.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DOT_CHAR_ASCII 46

const char *get_img_ext(const char *image_path);

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    printf("Usage:\n\timage-viewer <imagepath>");

    return 1;
  }

  const char *imagepath = argv[1];

  get_img_ext(imagepath);

  FILE *image_file = fopen(imagepath, "rb");

  if (image_file == NULL) {
    printf("Failed to open image");
    return EXIT_FAILURE;
  }

  Image *img = parse_ppm_image(image_file);

  if (img->height <= 0 || img->width <= 0) {
    printf("Invalid image dimensions");

    return 1;
  }

  SDL_Window *p_window =
      SDL_CreateWindow("Image Viewer", img->width, img->height, 0);

  SDL_Surface *p_window_surface = SDL_GetWindowSurface(p_window);

  draw_ppm(p_window, p_window_surface, img, image_file);

  free(img);

  while (true) {
    SDL_Event event;

    while (SDL_WaitEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        SDL_DestroyWindow(p_window);
        SDL_Quit();

        exit(0);
      }
    }
  }

  return 0;
}

Image *parse_ppm_image(FILE *image) {
  int width = 0;
  int height = 0;
  uint32_t maximum_color_value = 0;
  char *tempheaderbuf = malloc(sizeof(char) * 50);

  // Read the image type
  fgets(tempheaderbuf, 50, image);
  // Skip line 2
  fgets(tempheaderbuf, 50, image);
  // Get the image's dimensions
  fgets(tempheaderbuf, 50, image);
  sscanf(tempheaderbuf, "%d %d\n", &width, &height);
  // Get maximum color value
  fgets(tempheaderbuf, 50, image);
  sscanf(tempheaderbuf, "%d\n", &maximum_color_value);
  // Free buf
  free(tempheaderbuf);

  if (width <= 0 || height <= 0 || maximum_color_value <= 0) {
    perror("Failed to parse image: ");
    exit(1);
  }

  Image *img = malloc(sizeof(Image));

  img->width = width;
  img->height = height;
  img->maximum_color_value = maximum_color_value;

  return img;
}

void draw_ppm(SDL_Window *p_window, SDL_Surface *p_window_surface, Image *img,
              FILE *image_file) {
  unsigned char r, g, b;
  r = g = b = 0;

  for (int y_idx = 0; y_idx < img->height; y_idx++) {
    for (int x_idx = 0; x_idx < img->width; x_idx++) {
      r = fgetc(image_file);
      g = fgetc(image_file);
      b = fgetc(image_file);

      const SDL_Rect rect = (SDL_Rect){x_idx, y_idx, 1, 1};

      Uint32 color = SDL_MapRGB(
          SDL_GetPixelFormatDetails(p_window_surface->format), 0, r, g, b);

      SDL_FillSurfaceRect(SDL_GetWindowSurface(p_window), &rect, color);
    }
  }

  SDL_UpdateWindowSurface(p_window);
}

// AspectRatio calculate_aspect_ratio(int image_width, int image_height)
// {
//   // TODO: Base aspect ratio on 400
//   if (image_width <= 0 || image_height <= 0)
//   {
//     printf("Invalid image dimensions");

//     exit(EXIT_FAILURE);
//   }

//   return (AspectRatio){
//       image_width * (4 / 5),
//       image_height * (4 / 5),
//       image_width * (4 / 5),

//   };
// }

void destroy_image(Image *img) { free(img); }

const char *get_img_ext(const char *path) {
  char *ext = strrchr(path, DOT_CHAR_ASCII);

  if (ext == NULL) {
    printf("Failed to get extension");
    exit(EXIT_FAILURE);
  }

  char *extension = malloc(sizeof(char) * 3);

  sscanf(extension, "%d", (uint8_t)ext[1]);
  printf("Eextension: %s\n", extension);

  // free(extension);

  // TODO: Always free extension
  return extension;
}
