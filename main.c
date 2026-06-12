#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
  if (argc < 2)
  {
    printf("Usage:\n\timage-viewer <imagepath>");

    return 1;
  }

  const char *imagepath = argv[1];
  FILE *image = fopen(imagepath, "rb");

  if (image == NULL)
  {
    printf("Failed to open image");
    return EXIT_FAILURE;
  }

  // TODO: Learn how to handle used before initialization
  //
  const char *pwindow_title = "Image Viewer";
  int window_width = 0;
  int window_height = 0;
  // int image_maximumcolorvalue = -1;

  // Read the header
  char *tempheaderbuf = malloc(sizeof(char) * 50);
  fgets(tempheaderbuf, 50, image);

  // Ignore the commented line
  fgets(tempheaderbuf, 50, image);

  // Get the image's dimensions
  fgets(tempheaderbuf, 50, image);
  sscanf(tempheaderbuf, "%d %d\n", &window_width, &window_height);

  // Get maximum color value
  fgets(tempheaderbuf, 50, image);

  // sscanf(tempheaderbuf, "%d\n", &image_maximumcolorvalue);

  free(tempheaderbuf);

  SDL_Window *p_window =
      SDL_CreateWindow(pwindow_title, window_width, window_height, 0);

  SDL_Surface *p_surface = SDL_GetWindowSurface(p_window);

  unsigned char r, g, b;
  r = g = b = 0;

  for (int y = 0; y < window_height; y++)
  {
    for (int x = 0; x < window_width; x++)
    {

      r = fgetc(image);
      g = fgetc(image);
      b = fgetc(image);

      const SDL_Rect rect = (SDL_Rect){x, y, 1, 1};

      Uint32 color = SDL_MapRGB(SDL_GetPixelFormatDetails(p_surface->format),
                                NULL, r, g, b);

      SDL_FillSurfaceRect(p_surface, &rect, color);
    }
  }

  SDL_UpdateWindowSurface(p_window);

  while (true)
  {

    SDL_Event event;

    while (SDL_WaitEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        SDL_DestroyWindow(p_window);
        SDL_Quit();

        exit(0);
      }
    }
  }

  return 0;
}
