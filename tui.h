#include <stdlib.h> 
#ifndef TUI_H_
#define TUI_H_
#define BYTE unsigned char
typedef struct {
  char ch; 
  BYTE colors; 
} Cell; 

typedef struct {
  int width; 
  int height; 
  Cell** screen;
} Buffer; 

Cell space(); 
Cell new_cell(char,BYTE);
void print_cell(Cell);


Buffer* new_buffer(int,int); 
int put_string(Buffer*, const char*,int,int);
void print_buffer(Buffer*);

void free_buffer(Buffer*);
#endif
