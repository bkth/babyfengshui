#!/bin/sh
socat tcp-l:$1,reuseaddr,fork EXEC:"runuser fengshui -c ./babyfengshui" &
