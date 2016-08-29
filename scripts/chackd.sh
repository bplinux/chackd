#!/bin/bash

PID_FILE=/var/run/chackd.pid

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
	echo "starting chackd"
	if [[ $(/usr/bin/chackd) -eq 0 ]];
	then
		echo "daemon started"
	fi
	;;
stop)
	if [[ $(test -e ${PID_FILE}) ]]; 
	then
		echo "chackd is not running"
	fi
		echo "stopping daemon..."
		cat ${PID_FILE} | xargs kill -s SIGUSR1
	;;
esac
