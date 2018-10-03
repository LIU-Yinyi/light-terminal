/*************************************
 * Light Terminal Project Header
 *
 * It is a slight script for console
 * to optimize output style.
 *
 * @author:		Champion-Liu
 * @revised:	Champion-Liu
 * @email:		liuyinyi@vip.qq.com
 * @version:	1.1.0.0
 * @date:		2018-10-03
 ************************************/

#ifndef __LIGHT_TERMINAL_HPP
#define __LIGHT_TERMINAL_HPP

#include <iostream>
#include <string>
#include <curses.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <condition_variable>

using namespace std;

/**
 * @brief	LgTerm in-use function
 */
namespace LgTerm
{
	/// interfaces
	bool init();
	void quit();

	char get_ch();
	string get_str();	//!< Depreciate
	std::vector<string>  get_strs();	//!< New Feature
	void print(const char* fmt, ...);

	/**
	 * @brief	standard ostream output by redefining operator
	 */
	template<typename T>
	std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
	{
		os << "[\t";
		for(const auto& e : v)
		{
			os << e << "\t";
		}
		os << "]" << std::endl;
	}
	};

#endif /* __LIGHT_TERMINAL_HPP */
