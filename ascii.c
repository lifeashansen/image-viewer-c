#include <stdio.h>

int main()
{
  // char *dot = ".";
  for (int i = 0; i <= 128; i++)
  {
    unsigned char letter = i;
    printf("Number: %d -> Char: %c\n", i, letter);
  }


  return 0;
}
