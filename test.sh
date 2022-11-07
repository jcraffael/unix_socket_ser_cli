#!/bin/bash

#test1
chmod 755 server
./server

PID_SERV=$(ps aux | grep /server$ | grep -v "grep" | awk '{print $2}')
PID_PORT=$(netstat -putan | grep 12345 | awk '{print $NF}' | cut -d "/" -f 1)
if [ "$PID_SERV" -ne "$PID_PORT" ]; then
echo "Error in launching server"
exit -1
fi
kill -9 PID_SERV
if [ ! -z "$(ps aux | grep /server$ | grep -v "grep" | awk '{print $2}')" ] || [ ! -z $(netstat -putan | grep 12345 | awk '{print $NF}') ]; then
echo "Error in killing server"
        exit -2
fi


#test2

echo "foo.bar = YES" > /tmp/example.ini
chmod 755  /tmp/example.ini
chmod 755 client
./server
./client --load /tmp/example.ini
RET=$(echo $?)
if [ $RET -ne 0 ]; then
echo "Error loading file"
fi

./client --get foo.bar
RET=$(echo $?)
if [ $RET -ne 0 ]; then
        echo "Error getting value"
fi

./client --get foo.tar
RET=$(echo $?)
if [ $RET -ne -3 ]; then
       echo "Error getting error code"
fi
./client --set color.red "roses are red"
RET=$(echo $?)
if [ $RET -ne 0 ]; then
        echo "Error setting value"
fi

pkill server
