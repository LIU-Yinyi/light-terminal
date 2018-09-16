#include "light-terminal.hpp"

std::atomic<bool> LgTerm::flag_moni(false);

int LgTerm::win_row = 0;
int LgTerm::win_col = 0;

WINDOW LgTerm::*win_main;
WINDOW LgTerm::*win_output;
WINDOW LgTerm::*win_input;

string LgTerm::buf;

///////////////////

LgTerm::LgTerm()
{
}

LgTerm::~LgTerm()
{
}

///////////////////

bool LgTerm::init()
{
	if(flag_moni)
		return false;

	/// curses config
	win_main = initscr();
	getmaxyx(win_main, win_row, win_col);

	cbreak();
	noecho();

	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);
	refresh();

	/// thread config
	flag_moni = true;
	thr_moni = std::thread(thread_monitor);

	return true;
}

void LgTerm::quit()
{
	flag_moni = false;
	thr_moni.join();
}

///////////////////

char LgTerm::get_ch()
{
}

string LgTerm::get_str()
{
}

void LgTerm::print(const char* fmt, ...)
{
	touchwin(win_main);

	va_list ap;
	va_start(ap, fmt);
	vm_printw(win_output, fmt, ap);
	va_end(ap);

	wrefresh(win_output);
}

///////////////////

void LgTerm::thread_monitor()
{
	while(flag_moni)
	{
		char ch = getch();

		if(ch != '\r')
		{
			touchwin(win_main);
			buf += x;
			waddch(win_output, x);
		}
		else
		{
			touchwin(win_input);
			wclear(win_input);
		}

		wrefresh(win_input);
	}
}
