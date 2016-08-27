#!/bin/bash

PID_FILE=/var/run/challackd.pid

if [[ ${EUID} -ne 0 ]]; 
then
	echo "must be run as root, quitting!"
	exit 1
fi

if [[ $# -eq 0 ]];
then
	echo "$0 start stop"
fi

case "$1" in
start)	
	echo "starting challack daemon"
	if [[ $(./challackd) -eq 0 ]];
	then
		echo "daemon started"
	fi
	;;
stop)
	if [[ $(test -e ${PID_FILE}) ]]; 
	then
		echo "challack daemon is not running"
	fi
		echo "stopping challack daemon..."
		cat ${PID_FILE} | xargs kill -s SIGUSR1
	;;
esac
