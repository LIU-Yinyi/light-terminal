/*************************************
 * Light Terminal Project Test Program
 *
 * This is a test also a tutorial for
 * light-terminal library.
 *
 * @author:		Champion-Liu
 * @revised:	Champion-Liu
 * @email:		liuyinyi@vip.qq.com
 * @version:	1.1.0.0
 * @date:		2018-10-03
 ************************************/

#include <light-terminal.hpp>

std::atomic<bool> flag_show(false);

void show()
{
	while(flag_show)
	{
		static int i = 0;
		LgTerm::print("no.%d\n", i++);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main()
{
	LgTerm::init();
	
	flag_show = true;
	std::thread ts(show);

	bool isquit = false;
	while(!isquit)
	{
		std::vector<string> cmds = LgTerm::get_strs();
		if(cmds.size() < 1)
			continue;

		string cmd = cmds.at(0);

		if(cmd == "quit")
			isquit = true;
		else
		{
			LgTerm::print("[sys] your input cmd: < %s >\n", cmd.c_str());
			for(int i = 1; i < cmds.size(); i++)
				LgTerm::print("params[%d]: %s\n", i, cmds.at(i).c_str());
		}
	}

	flag_show = false;
	LgTerm::print("[sys] quit.");

	ts.join();
	LgTerm::quit();

	return 0;
}
