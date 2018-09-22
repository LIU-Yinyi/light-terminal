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
		string cmd = LgTerm::get_str();
		
		if(cmd == "quit")
			isquit = true;
		else
			LgTerm::print("[sys] your input cmd: < %s >\n", cmd.c_str());
	}

	flag_show = false;
	LgTerm::print("[sys] quit.");

	ts.join();
	LgTerm::quit();

	return 0;
}
