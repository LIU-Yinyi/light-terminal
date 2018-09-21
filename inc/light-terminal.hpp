#ifndef __LIGHT_TERMINAL_HPP
#define __LIGHT_TERMINAL_HPP

#include <iostream>
#include <string>
#include <curses.h>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

namespace LgTerm
{
	/// interfaces
	bool init();
	void quit();

	char get_ch();
	string get_str();
	void print(const char* fmt, ...);

	/// in-block functions
	/*
	void thread_monitor();

	static std::atomic<bool> flag_moni;
	static std::thread thr_moni;

	static int win_row, win_col;
	static WINDOW *win_main, *win_output, *win_input;
	static string buf;
	*/
};

#endif /* __LIGHT_TERMINAL_HPP */
