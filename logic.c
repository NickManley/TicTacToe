#include "global.h"
#include "ui.h"
#include "logic.h"

int gb_get_spaces()
{
	int i=0, count=0;
	for(i=0; i<9; i++)
	{
		if(mark[i] == 'k')
			count++;
	}
	return count;
}

int gb_get_x_count()
{
	int i=0, count=0;
	for(i=0; i<9; i++)
	{
		if(mark[i] == 'x')
			count++;
	}
	return count;
}

int gb_get_o_count()
{
	int i=0, count=0;
	for(i=0; i<9; i++)
	{
		if(mark[i] == 'o')
			count++;
	}
	return count;
}

int gb_line_check(int r, char m)
{
	int c = 0;
	char opp = 'x';
	if(m == 'x')
		opp = 'o';
	switch(r)
	{
		case 1:
			if(mark[0] == m) { c++; }
			if(mark[1] == m) { c++; }
			if(mark[2] == m) { c++; }
			if(mark[0] == opp) { c--; }
			if(mark[1] == opp) { c--; }
			if(mark[2] == opp) { c--; } break;
		case 2:
			if(mark[3] == m) { c++; }
			if(mark[4] == m) { c++; }
			if(mark[5] == m) { c++; }
			if(mark[3] == opp) { c--; }
			if(mark[4] == opp) { c--; }
			if(mark[5] == opp) { c--; } break;
		case 3:
			if(mark[6] == m) { c++; }
			if(mark[7] == m) { c++; }
			if(mark[8] == m) { c++; }
			if(mark[6] == opp) { c--; }
			if(mark[7] == opp) { c--; }
			if(mark[8] == opp) { c--; } break;
		case 4:
			if(mark[0] == m) { c++; }
			if(mark[3] == m) { c++; }
			if(mark[6] == m) { c++; }
			if(mark[0] == opp) { c--; }
			if(mark[3] == opp) { c--; }
			if(mark[6] == opp) { c--; } break;
		case 5:
			if(mark[1] == m) { c++; }
			if(mark[4] == m) { c++; }
			if(mark[7] == m) { c++; }
			if(mark[1] == opp) { c--; }
			if(mark[4] == opp) { c--; }
			if(mark[7] == opp) { c--; } break;
		case 6:
			if(mark[2] == m) { c++; }
			if(mark[5] == m) { c++; }
			if(mark[8] == m) { c++; }
			if(mark[2] == opp) { c--; }
			if(mark[5] == opp) { c--; }
			if(mark[8] == opp) { c--; } break;
		case 7:
			if(mark[0] == m) { c++; }
			if(mark[4] == m) { c++; }
			if(mark[8] == m) { c++; }
			if(mark[0] == opp) { c--; }
			if(mark[4] == opp) { c--; }
			if(mark[8] == opp) { c--; } break;
		case 8:
			if(mark[2] == m) { c++; }
			if(mark[4] == m) { c++; }
			if(mark[6] == m) { c++; }
			if(mark[2] == opp) { c--; }
			if(mark[4] == opp) { c--; }
			if(mark[6] == opp) { c--; } break;
	}
	return c;
}

int gb_table_check(char m)
{
	if( gb_line_check(1, m) == 2)
	{
		if(mark[0] == 'k') { return 0; }
		else if(mark[1] == 'k') { return 1; }
		else if(mark[2] == 'k') { return 2; }
	}
	else if( gb_line_check(2, m) == 2)
	{
		if(mark[3] == 'k') { return 3; }
		else if(mark[4] == 'k') { return 4; }
		else if(mark[5] == 'k') { return 5; }
	}
	else if( gb_line_check(3, m) == 2)
	{
		if(mark[6] == 'k') { return 6; }
		else if(mark[7] == 'k') { return 7; }
		else if(mark[8] == 'k') { return 8; }
	}
	else if( gb_line_check(4, m) == 2)
	{
		if(mark[0] == 'k') { return 0; }
		else if(mark[3] == 'k') { return 3; }
		else if(mark[6] == 'k') { return 6; }
	}
	else if( gb_line_check(5, m) == 2)
	{
		if(mark[1] == 'k') { return 1; }
		else if(mark[4] == 'k') { return 4; }
		else if(mark[7] == 'k') { return 7; }
	}
	else if( gb_line_check(6, m) == 2)
	{
		if(mark[2] == 'k') { return 2; }
		else if(mark[5] == 'k') { return 5; }
		else if(mark[8] == 'k') { return 8; }
	}
	else if( gb_line_check(7, m) == 2)
	{
		if(mark[0] == 'k') { return 0; }
		else if(mark[4] == 'k') { return 4; }
		else if(mark[8] == 'k') { return 8; }
	}
	else if( gb_line_check(8, m) == 2)
	{
		if(mark[2] == 'k') { return 2; }
		else if(mark[4] == 'k') { return 4; }
		else if(mark[6] == 'k') { return 6; }
	}
	return -1;
}

/*  Simple AI:

	1. If AI can win with the following move, make it.
	2. If human can win with the following move, block it.
	3. Otherwise, random spot.
*/
void gb_logic()
{
	int i;
	if( gb_get_spaces() > 0)
	{
		i = gb_table_check('o');
		if( i >= 0)
			gb_add_mark(i, 'o');
		else
		{
			i = gb_table_check('x');
			if(i >= 0)
				gb_add_mark(i, 'o');
			else
			{
				gboolean done = FALSE;
				GRand *r = g_rand_new();
				while(!done)
				{
					i = g_rand_int(r)%9;
					if( mark[i] == 'k')
					{
						gb_add_mark(i, 'o');
						done = TRUE;
					}
				}
				g_rand_free(r);
			}
		}
	}
}

/* winner combos are represented by int
   first digit is the winning combo
   second digit is the player who won */
int gb_win_check()
{
	int combo = 0;
	/* horizontal */
	if((mark[0] == mark[1]) && (mark[0] == mark[2]) && mark[1] == 'o')
		combo = 10;
	else if((mark[0] == mark[1]) && (mark[0] == mark[2]) && mark[1] == 'x')
		combo = 12;
	else if((mark[3] == mark[4]) && (mark[3] == mark[5]) && mark[4] == 'o')
		combo = 20;
	else if((mark[3] == mark[4]) && (mark[3] == mark[5]) && mark[4] == 'x')
		combo = 22;
	else if((mark[6] == mark[7]) && (mark[6] == mark[8]) && mark[7] == 'o')
		combo = 30;
	else if((mark[6] == mark[7]) && (mark[6] == mark[8]) && mark[7] == 'x')
		combo = 32;
	/* vertical */
	else if((mark[0] == mark[3]) && (mark[0] == mark[6]) && mark[3] == 'o')
		combo = 40;
	else if((mark[0] == mark[3]) && (mark[0] == mark[6]) && mark[3] == 'x')
		combo = 42;
	else if((mark[1] == mark[4]) && (mark[1] == mark[7]) && mark[4] == 'o')
		combo = 50;
	else if((mark[1] == mark[4]) && (mark[1] == mark[7]) && mark[4] == 'x')
		combo = 52;
	else if((mark[2] == mark[5]) && (mark[2] == mark[8]) && mark[5] == 'o')
		combo = 60;
	else if((mark[2] == mark[5]) && (mark[2] == mark[8]) && mark[5] == 'x')
		combo = 62;
	/* diaginal */
	else if((mark[0] == mark[4]) && (mark[0] == mark[8]) && mark[4] == 'o')
		combo = 70;
	else if((mark[0] == mark[4]) && (mark[0] == mark[8]) && mark[4] == 'x')
		combo = 72;
	else if((mark[2] == mark[4]) && (mark[2] == mark[6]) && mark[4] == 'o')
		combo = 80;
	else if((mark[2] == mark[4]) && (mark[2] == mark[6]) && mark[4] == 'x')
		combo = 82;
	
	return combo;
}
