#!/bin/bash
if python2 exploit.py | grep 33C3_; then
	echo OK
	exit 0
else
	echo KO
	exit 1
fi
