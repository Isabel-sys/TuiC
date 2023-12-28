#include "tui.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
Buffer *new_buffer(int width, int height) {
  Buffer *buffer = malloc(sizeof(Buffer));
  buffer->width = width;
  buffer->height = height;
  buffer->screen = malloc(sizeof(Cell *) * height);
  for (int i = 0; i < height; i++)
    buffer->screen[i] = malloc(sizeof(Cell) * width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      buffer->screen[i][j] = space();
    }
  }
  return buffer;
}

Cell space() { return (Cell){' ', 0xF0}; }
Cell new_cell(char ch, BYTE colors) { return (Cell){ch, colors}; }

int put_string(Buffer *buffer, const char *str, int x, int y) {
  int length = strlen(str);
  if (length > buffer->width + x || y > buffer->height - 1) {
    return -1;
  }
  for (int i = 0; i < length; i++)
    buffer->screen[y][x + i].ch = str[i];
  return 1;
}
void print_cell(Cell cell) {
  BYTE foreground = cell.colors >> 4 & 0xF;
  BYTE background = cell.colors & 0xF;
  printf("\e[38;5;%dm\e[48;5;%dm%c\e[0m", foreground, background, cell.ch);
}

void print_buffer(Buffer *buffer) {
  for (int i = 0; i < buffer->height; i++) {
    for (int j = 0; j < buffer->width; j++) {
      print_cell(buffer->screen[i][j]);
    }
    printf("\n");
  }
}
void free_buffer(Buffer *buffer) {
  for (int i = 0; i < buffer->height; i++)
    free(buffer->screen[i]);
  free(buffer->screen);

  free(buffer);
}
