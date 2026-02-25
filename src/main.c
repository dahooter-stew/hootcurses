#include "hootcurses.h"

int main(void)
{
  init_hootcurses("TEST");

  char a = 'A';

  bool heh = false;

  while (1)
  {
    event e;
    while (poll_events(&e))
    {
      a = 'B';
      heh = true;
    }

    clear_surface(get_surface());
    fill_surface(get_surface(), (fragment){.r = 100, .g = 100, .b = 255, .chr = a});

    if (heh)
    {
      fragment* f = surface_at(get_surface(), 20, 20);
      if (f)
        *f = (fragment){.r = 255, .g = 255, .b = 255, .chr = 'X'};
    }

    display_context();
  }
}
