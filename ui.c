#include "global.h"
#include "ui.h"
#include "logic.h"

void gb_draw_board(cairo_t *cr)
{
	/* draw white background*/
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_rectangle(cr, 0, 0, 480, 480);
	cairo_set_line_width(cr, 1);
	cairo_fill(cr);
	
	/* draw vertical lines */
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_set_line_width(cr, 14);
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	cairo_move_to(cr, 160, 20);
	cairo_line_to(cr, 160, 460);
	cairo_stroke(cr);
	
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_set_line_width(cr, 14);
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	cairo_move_to(cr, 320, 20);
	cairo_line_to(cr, 320, 460);
	cairo_stroke(cr);
	
	/* draw horizontal lines */
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_set_line_width(cr, 14);
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	cairo_move_to(cr, 20, 160);
	cairo_line_to(cr, 460, 160);
	cairo_stroke(cr);
	
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_set_line_width(cr, 14);
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	cairo_move_to(cr, 20, 320);
	cairo_line_to(cr, 460, 320);
	cairo_stroke(cr);
}

void gb_draw_x(cairo_t *cr, int pos)
{
	int x=0, y=0;
	switch(pos)
	{
		case 1: x=20; y=20; break;
		case 2: x=185; y=20; break;
		case 3: x=349; y=20; break;
		case 4: x=20; y=185; break;
		case 5: x=185; y=185; break;
		case 6: x=349; y=185; break;
		case 7: x=20; y=349; break;
		case 8: x=185; y=349; break;
		case 9: x=349; y=349; break;
		default: x=-500; y=-500; break;
	}
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.85);
	cairo_set_line_width(cr, 14);
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	cairo_move_to(cr, x, y);
	cairo_line_to(cr, x+110, y+110);
	cairo_stroke(cr);
	
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.85);
	cairo_set_line_width(cr, 14);
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	cairo_move_to(cr, x+110, y);
	cairo_line_to(cr, x, y+110);
	cairo_stroke(cr);
}

void gb_draw_o(cairo_t *cr, int pos)
{
	int x=0, y=0;
	switch(pos)
	{
		case 1: x=75; y=75; break;
		case 2: x=240; y=75; break;
		case 3: x=404; y=75; break;
		case 4: x=75; y=241; break;
		case 5: x=240; y=241; break;
		case 6: x=404; y=241; break;
		case 7: x=75; y=404; break;
		case 8: x=240; y=404; break;
		case 9: x=404; y=404; break;
	}
	cairo_set_source_rgb(cr, 0.85, 0.0, 0.0);
	cairo_arc(cr, x, y, 
			  70-10, 0, 2 * G_PI);
	cairo_stroke(cr);
}

void gb_add_mark(int loc, char m)
{
	mark[loc] = m;
}

void gb_draw_marks(cairo_t *cr)
{
	int i;
	for(i=0; i<9; i++)
	{
		if(mark[i] == 'x')
			gb_draw_x(cr, i+1);
		else if(mark[i] == 'o')
			gb_draw_o(cr, i+1);
	}
}

void gb_click(GtkWidget *widget, GdkEventButton *button, gpointer data)
{
	int signal_return_value;
	if(!gameover)
	{
		int loc=0;
		/* Row 1 */
		if( button->x <= 150 && button->y <= 150)
			loc = 1;
		else if( button->x >= 170 && button->x <= 310 &&
					button->y <= 150)
			loc = 2;
		else if( button->x >= 329 && button->y <= 150)
			loc = 3;
		
		/* Row 2 */
		else if( button->x <= 150 && button->y >= 170 && 
					button->y <= 312)
			loc = 4;
		else if( button->x >= 170 && button->x <= 310 &&
					button->y >= 170 && button->y <= 312)
			loc = 5;
		else if( button->x >= 329 && button->y >= 170 &&
					button->y <= 312)
			loc = 6;
		
		/* Row 3 */
		else if( button->x <= 150 && button->y >= 329)
			loc = 7;
		else if( button->x >= 170 && button->x <= 310 && 
					button->y >= 329)
			loc = 8;
		else if( button->x >= 329 && button->y >= 329)
			loc = 9;
		
		if(loc != 0 && (mark[loc-1] != 'x' && mark[loc-1] != 'o'))
		{
			gb_add_mark(loc-1, 'x');
			if( gb_win_check() == 0)
				gb_logic();
		}
	} else {
		int i;
		for(i=0; i<9; i++)
			mark[i] = 'k';
		gameover = FALSE;
	}
	
	g_signal_emit_by_name(area, "expose_event", NULL, &signal_return_value);
}

void gb_gameover(int wc)
{
	if( wc%10 == 0)	/* O wins */
		cairo_set_source_rgb(cr, 0.85, 0.0, 0.0);
	else	/* X wins */
		cairo_set_source_rgb(cr, 0.0, 0.0, 0.85);
		
	cairo_set_line_width(cr, 14);
	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	
	if( wc/10 == 1)
	{
		cairo_move_to(cr, 20, 75);
		cairo_line_to(cr, 440, 75);
	}
	else if( wc/10 == 2)
	{
		cairo_move_to(cr, 20, 241);
		cairo_line_to(cr, 440, 241);
	}
	else if( wc/10 == 3)
	{
		cairo_move_to(cr, 20, 404);
		cairo_line_to(cr, 440, 404);
	}
	else if( wc/10 == 4)
	{
		cairo_move_to(cr, 75, 75);
		cairo_line_to(cr, 75, 404);
	}
	else if( wc/10 == 5)
	{
		cairo_move_to(cr, 240, 75);
		cairo_line_to(cr, 240, 404);
	}
	else if( wc/10 == 6)
	{
		cairo_move_to(cr, 404, 75);
		cairo_line_to(cr, 404, 440);
	}
	else if( wc/10 == 7)
	{
		cairo_move_to(cr, 20, 20);
		cairo_line_to(cr, 440, 440);	
	}
	else if( wc/10 == 8)
	{
		cairo_move_to(cr, 460, 20);
		cairo_line_to(cr, 20, 460);
	}
	
	cairo_stroke(cr);
}
