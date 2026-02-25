#pragma once
#ifndef TYPES
#define TYPES

#include "resizable_array.h"
#include "screen_surface.h"

typedef struct 
{
  screen_surface* surface;
  screen_surface* previous_frame;
  resizable_array_char* ansi_string;
  char* title;
} render_context;

typedef enum
{
  INIT = 0,
  WINDOW_RESIZE
} EVENT_TYPE;

typedef union
{
  int type;
} event;

#endif
