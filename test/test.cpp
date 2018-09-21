#include "light-terminal.hpp"

int main()
{
	LgTerm::init();
	
	bool isquit = false;
	while(!isquit)
	{
		/*
		string cmd = LgTerm::get_str();
		if(cmd == "quit")
			isquit = true;
		else
			LgTerm::print(cmd.c_str());
		*/
		static int i = 0;
		LgTerm::print("no.%d\n", i++);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	LgTerm::print("[sys] quit.");
	LgTerm::quit();

	return 0;
}
