all:main.cpp
			g++ -g -o main main.cpp `pkg-config --cflags gio-2.0` `pkg-config --libs gio-2.0` 
