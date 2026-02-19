#pragma once
#ifndef HOOTCURSES
#define HOOTCURSES

#include "resizable_array.h"

/* ================================================
 * TYPES
 * ================================================
 */

typedef union 
{
  char c[4];
  int data;
  struct {
    unsigned char r;
    unsigned char b;
    unsigned char g;
    unsigned char chr;
  };
} fragment;

typedef struct 
{
  fragment* data;
  int width;
  int height;
} screen_surface;

typedef struct 
{
  screen_surface* surface;
  resizable_array_char* ansi_string;
  char* title;
} render_context;


typedef enum
{
  WINDOW_RESIZE
} EVENT_TYPE;

typedef union
{
  int type;
} event;

screen_surface* create_surface(int width, int height);
render_context* create_context(screen_surface* surface, char* title);
void set_current_context(render_context* context);

void init_hootcurses(void);

void blit_surface(void);
void display_context(void);

void clear_surface(void);
void fill_surface(fragment frag);
void put_at(int x, int y, fragment frag);


void test(void);
#endif
