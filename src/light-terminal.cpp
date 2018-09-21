#include "light-terminal.hpp"

std::atomic<bool> flag_moni(false);
std::thread *thr_moni;

int win_row = 0;
int win_col = 0;

WINDOW *win_main;
WINDOW *win_output;
WINDOW *win_input;

string buf;

void thread_monitor();

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

	win_output = subwin(win_main, win_row - 1, win_col, 0, 0);
	win_input = subwin(win_main, 1, win_col, win_row - 1, 0);
	scrollok(win_output, true);

	/// thread config
	flag_moni = true;
	thr_moni = new std::thread(thread_monitor);

	return true;
}

void LgTerm::quit()
{
	flag_moni = false;
	thr_moni->join();
	delete thr_moni;
	endwin();
}

///////////////////

char LgTerm::get_ch()
{
	return '\r';
}

string LgTerm::get_str()
{
	return "quit";
}

void LgTerm::print(const char* fmt, ...)
{
	touchwin(win_main);

	va_list ap;
	va_start(ap, fmt);
	vw_printw(win_output, fmt, ap);
	va_end(ap);

	wrefresh(win_output);
}

///////////////////

void thread_monitor()
{
	//LgTerm::print("[monitor] thread start...");

	while(flag_moni)
	{
		char ch = getch();

		if(ch != '\r')
		{
			touchwin(win_main);
			buf += ch;
			waddch(win_input, ch);
		}
		else
		{
			touchwin(win_input);
			wclear(win_input);
		}

		wrefresh(win_input);
		
	}

	//LgTerm::print("[monitor] thread end.");
}
