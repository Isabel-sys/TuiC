#include "tui.h"

Canvas new_canvas(int width, int height) {
  Cell **screen = malloc(sizeof(Cell *) * height);
  for (int i = 0; i < height; i++) {
    screen[i] = malloc(sizeof(Cell) * width);
    for (int j = 0; j < width; j++)
      screen[i][j] = space();
  }
  return (Canvas){width, height, screen};
}

int put_string(Canvas canvas, const char *string, int x, int y) {
  for (int i = 0; string[i] != '\0'; i++) {
    if (x > (canvas.width - 1)) {

      if (++y > (canvas.height) - 1) {
        return -1;
      }
      x = 0;
    }
    canvas.screen[y][x++].ch = string[i];
  }
  return 0;
}

void print_canvas(Canvas canvas) {
  for (int i = 0; i < canvas.height; i++) {
    for (int j = 0; j < canvas.width; j++) {
      print_cell(canvas.screen[i][j]);
    }
    printf("\n");
  }
}

void free_canvas(Canvas canvas) {
  for (int i = 0; i < canvas.height; i++) {
    free(canvas.screen[i]);
  }
  free(canvas.screen);
}

void print_cell(Cell cell) {
  byte fore = cell.color >> 4 & 0xF;
  byte back = cell.color & 0xF;
  printf("\x1b[38;5;%dm\x1b[48;5;%dm", fore, back);
  printf("%c", cell.ch);
  printf("\x1b[0m");
}

Cell space() { return (Cell){' ', 0x0F, 0x00}; }
