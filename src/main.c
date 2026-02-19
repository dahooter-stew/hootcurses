#include "hootcurses.h"

int main(void)
{
  init_hootcurses();

  while (1)
  {
    clear_surface();
    // put_at(10, 10, (fragment){.r = 255, .b = 255, .g = 255, .chr = 'O'});
    fill_surface((fragment){.r = 100, .g = 100, .b = 100, .chr = 'K'});

    blit_surface();
    display_context();
  }
}
