Hello!!
This directory have ncurses test files.

Compile:
c++ -o test_exec file_name.cpp -lncursesw
or
c++ -o test_exec file_name.cpp -lncursesw `pkg-config sdl2 SDL2_mixer --cflags --libs`
