#include "global.h"

void gb_draw_board(cairo_t *cr);
void gb_draw_x(cairo_t *cr, int pos);
void gb_draw_o(cairo_t *cr, int pos);
void gb_add_mark(int loc, char m);
void gb_draw_marks(cairo_t *cr);
void gb_click(GtkWidget *widget, GdkEventButton *button, gpointer data);
void gb_gameover();
