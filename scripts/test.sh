#!/bin/bash

while [ 1 ]
do 
	sysctl net.ipv4.tcp_challenge_ack_limit
	sleep 2
done
