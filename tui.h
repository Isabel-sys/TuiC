#ifndef TUI_H_
#define TUI_H_ 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

typedef unsigned char byte;
typedef struct {
  char ch; 
  byte color; 
  byte attributes; 
} Cell; 

typedef struct {
  int width; 
  int height; 
  Cell** screen;
} Canvas; 


Canvas new_canvas(int width, int height);
int put_string(Canvas canvas, const char* string,int x, int y); 
void print_canvas(Canvas canvas);
void free_canvas(Canvas canvas);

Cell space(); 
Cell new_cell(char ch, byte fore, byte back, byte attributes); 
void print_cell(Cell cell);
#endif
