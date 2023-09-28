#!/bin/bash

status() {
  echo "Status"
  if ps -p $(cat /tmp/cudp.pid) > /dev/null
  then
    echo "Server is running"
  else
    echo "Server is stopped"
  fi
}

start() {
  echo "Start"
  /root/cudp/Server &
}

stop() {
  echo "Stop"
  kill -9 $(cat /tmp/cudp.pid)
}

case "$1" in
  'start')
    start
    ;;
  'stop')
    stop
    ;;
  'restart')
    stop ; echo "Sleeping..."; sleep 1 ;
    start
    ;;
  'status')
    status
    ;;
  *)
    echo
    echo "Usage: $0 { start | stop | restart | status }"
    echo
    exit 1
    ;;
esac

exit 0