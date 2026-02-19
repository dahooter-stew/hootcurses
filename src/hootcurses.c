#include "hootcurses.h"

#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static render_context* CURRENT_CONTEXT = NULL;

screen_surface* create_surface(int width, int height)
{
  screen_surface* surface = malloc(sizeof(screen_surface));
  surface->data = malloc(width * height * sizeof(fragment));
  surface->width = width;
  surface->height = height;

  return surface;
}

render_context* create_context(screen_surface* surface, char* title)
{
  resizable_array_char* buffer = allocate_array_char(surface->width * surface->height * 30);

  render_context* context = malloc(sizeof(render_context));
  context->surface = surface;
  context->ansi_string = buffer;
  context->title = title;

  return context;
}

void set_current_context(render_context* context)
{
  if (!context)
  {
    CURRENT_CONTEXT = NULL;
    return;
  }

  CURRENT_CONTEXT = context;
}

void init_hootcurses(void)
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

  screen_surface* surface = create_surface(w.ws_col, w.ws_row);
  render_context* context = create_context(surface, "wow");
  set_current_context(context);
}

static void push_string_resizable_char(resizable_array_char* ansi_string, char* str)
{
  int i = 0;
  while (str[i])
  {
    push_char(ansi_string, str[i]);
    i++;
  }
}

void blit_surface(void)
{
  static char TEMP_BUFFER[25];
 
  CURRENT_CONTEXT->ansi_string->length = 0; 
  push_string_resizable_char(CURRENT_CONTEXT->ansi_string, "\033[H");

  for (int i = 0; i < CURRENT_CONTEXT->surface->width * CURRENT_CONTEXT->surface->height; i++)
  {
    sprintf(TEMP_BUFFER, "\x1b[38;2;%d;%d;%dm", CURRENT_CONTEXT->surface->data[i].r, CURRENT_CONTEXT->surface->data[i].g, CURRENT_CONTEXT->surface->data[i].b);

    push_string_resizable_char(CURRENT_CONTEXT->ansi_string, TEMP_BUFFER);
    push_char(CURRENT_CONTEXT->ansi_string, CURRENT_CONTEXT->surface->data[i].chr);
    push_string_resizable_char(CURRENT_CONTEXT->ansi_string, "\x1b[0m");
  }
}

void display_context(void)
{
  write(1, CURRENT_CONTEXT->ansi_string->data, CURRENT_CONTEXT->ansi_string->length);
}

void clear_surface(void)
{
  memset(CURRENT_CONTEXT->surface->data, ' ', CURRENT_CONTEXT->surface->width * CURRENT_CONTEXT->surface->height * sizeof(fragment));
}

void fill_surface(fragment frag)
{
  for (int i = 0; i < CURRENT_CONTEXT->surface->width * CURRENT_CONTEXT->surface->height; i++)
    CURRENT_CONTEXT->surface->data[i] = frag;
}

void put_at(int x, int y, fragment frag)
{
  CURRENT_CONTEXT->surface->data[y * CURRENT_CONTEXT->surface->width + x] = frag;
}
