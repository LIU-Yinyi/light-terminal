## Light Terminal Library for C++ Project
- **Author**: Champion-Liu
- **Revised**: Champion-Liu
- **Version**: 0.1.0
- **Date**: 2018-09-21
- **Abstract**: A light-terminal library based on curses, which can show user input text fixed at the bottom of the terminal in case of flushing out by program output information.

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
LgTerm::get_ch(); //!< get char each key
LgTerm::get_str(); //!< get string until enter key

/// quit
LgTerm::quit();
```
