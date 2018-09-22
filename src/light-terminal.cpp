#include "light-terminal.hpp"
#include "config.h"

std::atomic<bool> flag_moni(false);
std::thread *thr_moni;
std::mutex scan_mtx;
std::condition_variable enter_cv;

int win_row = 0;
int win_col = 0;

WINDOW *win_main;
WINDOW *win_output;
WINDOW *win_input;

bool is_enter(false);
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
	return getch();
}

string LgTerm::get_str()
{
	std::unique_lock<std::mutex> lk(scan_mtx);
	while(!is_enter)
	{
		enter_cv.wait(lk);
	}
	string str = buf;

#ifdef DEBUG
	LgTerm::print("[str] %s\n", str.c_str());
#endif

	buf.clear();
	is_enter = false;
	return str;
}

void LgTerm::print(const char* fmt, ...)
{
	touchwin(win_output);

	va_list ap;
	va_start(ap, fmt);
	vw_printw(win_output, fmt, ap);
	va_end(ap);

	wrefresh(win_output);
}

///////////////////

void thread_monitor()
{
	while(flag_moni)
	{
		std::unique_lock<std::mutex> lk(scan_mtx);
		char ch = getch();

		if(ch == '\r')
		{
			touchwin(win_input);
			wclear(win_input);
			is_enter = true;
			enter_cv.notify_one();
		}
		else if(ch == '\b' || ch == 0x7F)
		{
			buf.pop_back();

#ifdef DEBUG
			LgTerm::print("[sys] you input a backspace button.\n");
			LgTerm::print("[sys] buf length: %d\n", buf.length());
#endif
			
			touchwin(win_input);
			//wdelch(win_input);
			wclear(win_input);
			waddstr(win_input, buf.c_str());

#ifdef DEBUG
			LgTerm::print("[sys] buf: < %s >\n", buf.c_str());
#endif
		}
		else if(ch >= 0x20 && ch < 0x7F)
		{
			touchwin(win_input);
			buf += ch;
			waddch(win_input, ch);

#ifdef DEBUG
			LgTerm::print("[sys] buf: < %s >\n", buf.c_str());
#endif
		}

		wrefresh(win_input);
		
	}
}
