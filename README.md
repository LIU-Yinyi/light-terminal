## Light Terminal Library for C++ Project
- **Author**: Champion-Liu
- **Revised**: Champion-Liu
- **Version**: 1.1.0
- **Date**: 2018-10-03
- **Abstract**: A light-terminal library based on curses, which can show user input text fixed at the bottom of the terminal in case of flushing out by program output information.

---

### Introduction
Q: `Why did I want to start this tiny project?`  
A: `Sometimes people may meet the problems below:`

You want to get the sensor data while your program keeps refreshing.  
For example, you want to input `get <enter>`

```
>>> ./run_program
[program] sensor of Laser init ... done
[program] sensor of Sonar init ... done
ge[program] self-check ... ok
t<enter>
[program] everything is ready.
...
```

You can see that the program information interrupt the user input which makes the console seem terrible, so I use curse to try to code a light terminal library to solve that problems. The expected:

```
[program] sensor of Laser init ... done
[program] sensor of Sonar init ... done
[program] self-check ... ok
[program] everything is ready.
...
get<enter> /*The input line is always here*/
```

---

### Install Dependent Libraries
For Ubuntu:  

```
sudo apt-get install libcurses5-dev
```

For MacOSX:  

```
brew install ncurses
```

---

### Usages
For Test:  

```bash
cd light-terminal
mkdir build
cd build
cmake ..
make -j2
../bin/lgtest
```

For Develop:

```cpp
/// contain header
#include <light-terminal.hpp>

/// initialize
LgTerm::init();

/// block print
LgTerm::print(const char *format, ...);

/// block scan
char LgTerm::get_ch(); //!< get char each key
vector<string> LgTerm::get_strs(); //!< get array of strings until enter key

/// quit
LgTerm::quit();
```

---

### Performance
I use `condition_variable` with `mutex` so monitor thread is usually sleeping.

```
Processes: 427 total, 2 running, 425 sleeping, 1492 threads                                                    14:59:44
Load Avg: 1.83, 2.09, 2.16  CPU usage: 9.33% user, 7.41% sys, 83.25% idle
SharedLibs: 280M resident, 54M data, 88M linkedit.
MemRegions: 121738 total, 2868M resident, 116M private, 2211M shared. PhysMem: 16G used (4772M wired), 64M unused.
VM: 1888G vsize, 1099M framework vsize, 18545828(0) swapins, 19067334(0) swapouts.
Networks: packets: 28371614/29G in, 17732965/6239M out. Disks: 5953869/170G read, 5978235/177G written.

PID    COMMAND      %CPU  TIME     #TH   #WQ  #PORTS MEM    PURG   CMPRS  PGRP  PPID  STATE    BOOSTS            %CPU_ME
82339  lgtest       0.0   00:00.01 3     0    13     600K   0B     0B     82339 60392 sleeping *0[1]             0.00000
```

---

### New Features
In version `1.1.0`, I add:

+ add `std::vector<string> get_strs()` for acquiring `argc argv` look-like variables;

So the old function `string get_str()` is *depreciated*.

---

### Further Features
I will add some useful features for the further version:

+ add `spdlog` look-like debug with quick color decoration;
+ add `cpp-readline` look-like console with helpdesk and history record.
