#ifndef __LIGHT_TERMINAL_HPP
#define __LIGHT_TERMINAL_HPP

#include <iostream>
#include <string>
#include <curses.h>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

class LgTerm
{
public:
	LgTerm();
	~LgTerm();

	static bool init();
	static void quit();

	static char get_ch();
	static string get_str();
	static void print(const char* fmt, ...);

private:
	static void thread_monitor();

private:
	static std::atomic<bool> flag_moni;
	static std::thread thr_moni;
	
	static int win_row, win_col;
	static WINDOW *win_main, *win_output, *win_input;
	static string buf;
};

#endif /* __LIGHT_TERMINAL_HPP */
