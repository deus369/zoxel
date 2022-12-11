#!/bin/bash


cd ..

echo "Inside ($PWD)"

running=true
quit_command="q"
run_command="r"
quit_time=3

while [ $running ]; do
	sleep 0.5
	echo "Developing Zoxel Loop"
	sleep 0.5
	echo "	-> $run_command (or any) to build & run"
	sleep 0.5
	echo "	-> $quit_command to quit"
	sleep 0.5
	read -p "Enter a command: " command
	if [ $command = $quit_command ]; then
		echo "Quiting Development in $quit_time seconds."
		sleep $quit_time
		exit
	else
		echo "Making dev"
		sleep 0.5
		make dev
		echo "Running dev"
		sleep 0.5
		make run-dev
	fi
done

	# elif [ $command = $run_command ]; then
	# else
	#	echo "Incorrect command given."
