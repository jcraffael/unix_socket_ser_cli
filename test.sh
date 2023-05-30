#!/bin/bash

export LD_LIBRARY_PATH=$(pwd)/libshared

err() { echo "$1"; exit 1; }
#test1
echo "Now running test1"

[ -f "$(pwd)/build/server" ] || err "Missing server, please compile"

cd build
./server &
sleep 1
PID_SERV=$(ps aux | grep /server$ | grep -v "grep" | awk '{print $2}')
PID_PORT=$(lsof -i -P -n | grep 12345 | awk '{print $2}' | cut -d "/" -f 1)
echo "Server's PID is $PID_SERV"
if [ "$PID_SERV" != "$PID_PORT" ]; then
        echo "Error in launching server"
        exit 1
else
        echo "Server launched correctly!"
fi
kill -9 $PID_SERV
if [ ! -z "$(ps aux | grep /server$ | grep -v "grep" | awk '{print $2}')" ] || [ ! -z $(lsof -i -P -n | grep 12345 | awk '{print $NF}') ]; then
        echo "Error in killing server"
        exit 1
else
        echo "Server killed correctly!"
fi


#test2
sleep 3
echo
echo "Now running test2"
[ -f "client" ] || err "Missing client, please compile"
#chmod 755  /tmp/example.ini

#./server &
gnome-terminal -- ./server 
./client --load /tmp/example.ini 

RET=$(echo $?)
if [ $RET -ne 0 ]; then
        echo "Error loading file"
else
        echo "File loaded correctly"
fi
echo "foo.bar : YES" > /tmp/example.ini

./client --get foo.bar
RET=$(echo $?)
if [ $RET -ne 0 ]; then
        echo "Error getting value"
else
        echo "Get value correctly"
fi

./client --get foo.tar
# RET=$(echo $?)
# if [ $RET -ne -3 ]; then
#        echo "Error getting error code"
# else
#         echo "Get value correctly"
# fi

./client --set color.red "roses are red"
RET=$(echo $?)
if [ $RET -ne 0 ]; then
        echo "Error setting value"
else
        echo "Set value correctly"
fi

pkill server
if [ $(echo $?) -eq 0 ]; then
        echo "Server killed correctly"
else
        echo "Error killing server"
fi
