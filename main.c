#include "global.h"
#include "ui.h"
#include "logic.h"

void gb_expose(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
	cr = gdk_cairo_create(area->window);
	gb_draw_board(cr);
	gb_draw_marks(cr);
	if( gb_win_check() > 0)
	{
		/* WINNER! */
		/* draw winner's line */
		gameover = TRUE;
		gb_gameover( gb_win_check() );
	}
	else if(gb_get_spaces() == 0)
	{
		gameover = TRUE;
	}
}

int main(int argc, char *argv[])
{
	int i;
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	area = gtk_drawing_area_new();
	for(i=0; i<9; i++)
		mark[i] = 'k';
	gameover = FALSE;
	
	gtk_window_set_title(GTK_WINDOW(window), "Tic-Tac-Toe");
	gtk_widget_set_size_request(GTK_WIDGET(window), 480, 480);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	
	gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);
	g_signal_connect(window, "button_press_event",
		G_CALLBACK(gb_click), NULL);
	
	gtk_container_add(GTK_CONTAINER(window), area);
	
	g_signal_connect(area, "expose_event",
		G_CALLBACK(gb_expose), NULL);
	g_signal_connect(window, "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_widget_show_all(window);
	
	gtk_main();
	
	return 0;
}
