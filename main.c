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
  const char *windowtitle = "Image Viewer";
  int windowwidth = -1;
  int windowheight = -1;
  // int image_maximumcolorvalue = -1;

  // Read the header
  char *tempheaderbuf = malloc(sizeof(char) * 50);
  fgets(tempheaderbuf, 50, image);

  // Ignore the commented line
  fgets(tempheaderbuf, 50, image);

  // Get the image's dimensions
  fgets(tempheaderbuf, 50, image);
  sscanf(tempheaderbuf, "%d %d\n", &windowwidth, &windowheight);

  // Get maximum color value
  fgets(tempheaderbuf, 50, image);

  // sscanf(tempheaderbuf, "%d\n", &image_maximumcolorvalue);

  free(tempheaderbuf);

  SDL_Window *pwindow =
      SDL_CreateWindow(windowtitle, windowwidth, windowheight, 0);

  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  unsigned char r, g, b;
  r = g = b = 0;

  for (int y = 0; y < windowheight; y++)
  {
    for (int x = 0; x < windowwidth; x++)
    {

      r = fgetc(image);
      g = fgetc(image);
      b = fgetc(image);

      const SDL_Rect rect = (SDL_Rect){x, y, 1, 1};

      Uint32 color = SDL_MapRGB(SDL_GetPixelFormatDetails(psurface->format),
                                NULL, r, g, b);

      SDL_FillSurfaceRect(psurface, &rect, color);
    }
  }

  SDL_UpdateWindowSurface(pwindow);

  Uint8 windowshouldclose = 0;

  while (!windowshouldclose)
  {
    SDL_Event pevent;
    while (SDL_PollEvent(&pevent))
    {
      if (pevent.type == SDL_EVENT_QUIT)
      {
        windowshouldclose = 1;
      }
    }
  }

  SDL_DestroyWindow(pwindow);
  SDL_Quit();

  return 0;
}
