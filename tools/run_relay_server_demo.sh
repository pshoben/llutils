killall echo_server relay_server socket_client
sleep 5

echo "starting echo server on port 7575"
$LLUTILS_HOME/build/lls/echo_server -l 7575 &

echo "starting relay server on port 6565"
$LLUTILS_HOME/build/lls/relay_server -f $LLUTILS_HOME/lls/test_relay_server.cfg &

echo "sending 5 test messages from socket client (wait time 1000 nanos)"
$LLUTILS_HOME/build/lls/socket_client -p 6565 -s "test" -r 5 -w 1000 

echo "sending 5 test messages from socket client (wait time 999999999 nanos)"
$LLUTILS_HOME/build/lls/socket_client -p 6565 -s "test" -r 5 -w 999999999

echo "running  socket client in interactive mode:"
$LLUTILS_HOME/build/lls/socket_client -p 6565 -i

killall echo_server relay_server socket_client

