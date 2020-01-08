
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/* screen size - adapt to console size */
#define NUM_COLUMNS 80
#define NUM_ROWS 25

/* screen buffer */
/*COLUMNS = x, ROWS = y */
char screen[NUM_COLUMNS][NUM_ROWS];


/* initialize buffer by setting all pixels to spaces */
void initialize_buffer()
{
    for(int i=0; i<NUM_ROWS; i++)
        for(int j=0; j<NUM_COLUMNS; j++)
            screen[j][i] = ' ';
}


/* update screen by copying buffer to console window */
void update_screen()
{
    for(int i=0; i<NUM_ROWS; i++)
    {
        for(int j=0; j<NUM_COLUMNS; j++)
            putchar(screen[j][i]);
        putchar('\n');
    }
    fflush(stdout);
}

/* ---- part 1 ---- */

/* checks whether a given point (x,y) is within the screen */
/* returns 1 if point is within the screen -1 if not */
unsigned in_screen(int x, int y){
    if((0 <= x && x <= NUM_COLUMNS - 1) && (0 <= y && y <= NUM_ROWS - 1))
        return 1;
    else
        return -1;
}

/* draw a single point at given position (x,y) and with given character */
void draw_pixel(int x, int y, char c){
    if (in_screen(x, y) == 1)
        screen[x][y] = c;
}

/* clear a single pixel at position (x,y) */
void clear_pixel(int x, int y){
    if (in_screen(x, y) == 1)
        screen[x][y] = ' ';
}

/* ---- part 2 ---- */

/* draw a text at given position (x,y) */
void draw_text(int x, int y, char* s){
    while((*s != '\0') && (x <= NUM_COLUMNS - 1)){
        screen[x][y] = *s;
        s++;
        x++;
    }

}

/* ---- part 3 ---- */

/* draw a horizontal line (x1,y)-(x2,y) with dashes (-) */
void draw_horizontal_line(int x1, int x2, int y){
    if((in_screen(x1, y) == 1 && in_screen(x2, y) == 1) && x2 >= x1) {
        while (x1 != x2 + 1) {
            screen[x1][y] = '-';
            x1++;
        }
    } else if ((in_screen(x1, y) == 1 && in_screen(x2, y) == 1) && x1 >= x2){
        while (x2 != x1 + 1){
            screen[x2][y] = '-';
            x2++;
        }
    }

}


/* draw a vertical line (x,y1)-(x,y2) with vertical bars (|) */
void draw_vertical_line(int x, int y1, int y2){
    if((in_screen(x, y1) == 1 && in_screen(x, y2) == 1) && y2 >= y1) {
        while (y1 != y2 + 1) {
            screen[x][y1] = '|';
            y1++;
        }
    } else if ((in_screen(x, y1) == 1 && in_screen(x, y2) == 1) && y1 >= y2){
        while (y2 != y1 + 1) {
            screen[x][y2] = '|';
            y2++;
        }
    }
}


/* draw a horizontal arrow (x1,y)-(x2,y) */
void draw_horizontal_arrow(int x1, int x2, int y)
{
    draw_horizontal_line(x1, x2, y);
    if (x1<x2)
        draw_pixel(x2, y, '>');
    else
        draw_pixel(x2, y, '<');
}

/* draw a vertical arrow (x,y1)-(x,y2) */
void draw_vertical_arrow(int x, int y1, int y2)
{
    draw_vertical_line(x, y1, y2);
    if (y1<y2)
        draw_pixel(x, y2, 'v');
    else
        draw_pixel(x, y2, '^');
}

/* draw a rectangle (x1,y1)-(x2,y1)-(x2,y2)-(x1,y2) with plus, dashes and vertical bars */
void draw_rectangle(int x1, int y1, int x2, int y2)
{
    draw_horizontal_line(x1, x2, y1);
    draw_horizontal_line(x1, x2, y2);
    draw_vertical_line(x1, y1, y2);
    draw_vertical_line(x2, y1, y2);
    draw_pixel(x1, y1, '+');
    draw_pixel(x2, y1, '+');
    draw_pixel(x1, y2, '+');
    draw_pixel(x2, y2, '+');
}


/* ---- part 4 ---- */

/* draw a general line (x1,y1)-(x2,y2) with character c */
void draw_line(int x1, int y1, int x2, int y2, char c);

/* ---- part 5 ---- */

/* flood fill an area starting at given position with character c */
void flood_fill(int x, int y, char c);


/* main program: entry point */

int main(int argc, const char * argv[]) {
    initialize_buffer();
    update_screen();

    /*
     draw_rectangle(25, 2, 68, 8);
    draw_line(0,NUM_ROWS-1,NUM_COLUMNS-1,0,'*');
    flood_fill(2,2,'.');
    draw_pixel(30, 10, '1');
    draw_pixel(20, 15, '2');
    draw_pixel(75, 20, '3');
    draw_line(8,8, 45, 15, '+');
    draw_text(35, 5, "Hello World!");
    draw_horizontal_arrow(0, NUM_COLUMNS-1, 0);
    draw_vertical_arrow(0, 1, NUM_ROWS-1);

    update_screen();
    */

    char resp;
    scanf("%c", &resp);
    return 0;
}
