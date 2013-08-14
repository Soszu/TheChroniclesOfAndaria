#!/bin/bash

# -f	force building whole project from beginning
# -p	pack game (compress) to given file, (don't run game after process)
# -i	ignore fact that binary file is not up-to-date
# -c	clean this directory
# -r	run the game
# -b	build the project (only what needs to be built)

# by default (if there is no arguments given) -br is chosen.

#TODO make it more professional by using  GETOPTS

# for now vim-like interface should do :)
# it is not comlete and competent script but for my use it is OK.

#	ACTUAL POSSIBLE ARGUMENTS
# r		- just run game
# br		- (DEFAULT) build what needs to be build and run
# fr		- force building whole project from beginning
# c		- clean this directory

# ------------------------------------
shopt -s extglob

if [ "$#" -eq 0 -o "$1" = 'br' ]; then
	if [ ! -d build ]; then
		mkdir build
	fi
	cd build
	cmake ..
	make
	cp Planszowka ..
	cd ..
	./Planszowka &
else
	case "$1" in
		"c") rm -r !(CMakeLists.txt|runTool.sh|img|src|data|.gitignore) ;;
		"r") ./Planszowka & ;;
		"fr") rm -r build ; ./runTool.sh br ;;
		"qt") cp ./build/Planszowka . ; ./Planszowka ;;
		*) echo 'unknown option'
	esac
fi
