#!/bin/sh
#
# tinydnsd: an init script to start & stop the tinydns service daemon.
#
# chkconfig: 35 20 80
# description: tinydns is a DNS server program.
#              tinydns server maps & serves IP addresses for a given domain
#              name from a local static database of domain names.
#

### BEGIN INIT INFO
# Provides:          tinydns
# Required-Start:    $network
# Required-Stop:     $network
# Default-Start:     3 5
# Default-Stop:      0 1 2 4 6
# Short-Description: start and stop tinydns daemon at boot time.
# Description:       tinydns is a DNS server program.
### END INIT INFO

# Source function library.
. /etc/init.d/functions

# Source networking configuration
. /etc/sysconfig/network

prog=PREFIX/bin/tinydns
logfile="/var/log/${prog##[a-z/.]*/}.log"
lockfile="/var/lock/subsys/${prog##[a-z/.]*/}"

start ()
{
    # Check if networking is up.
    [ "$NETWORKING" = "no" ] && exit 1

    [ -x $prog ] || exit 5

    # Start daemon.
    echo -n $"Starting ${prog##[a-z/.]*/}: "
    daemon $prog -d3 -D 2>> $logfile
    RETVAL=$?

    chmod og= $logfile
    echo
    [ $RETVAL -eq 0 ] && touch $lockfile

    return $RETVAL
}

stop ()
{
    echo -n $"Shutting down ${prog##[a-z/.]*/}: "
    killproc $prog
    RETVAL=$?
    echo
    [ $RETVAL -eq 0 ] && rm -f $lockfile

    return $RETVAL
}


cmd="${0##[a-z/.]*/}"

# See how we were called.
case "$1" in
  start)
    if [ `id -u` -ne 0 ]; then
        echo "$cmd: you must be root to \`$1' this service."
        exit -1
    fi
    start
    ;;
  stop)
    if [ `id -u` -ne 0 ]; then
        echo "$cmd: you must be root to \`$1' this service."
        exit -1
    fi
    stop
    ;;
  status)
    status $prog
    ;;
  restart)
    if [ `id -u` -ne 0 ]; then
        echo "$cmd: you must be root to \`$1' this service."
        exit -1
    fi
    stop
    start
    ;;
  reload)
    exit 3
    ;;
  *)
    echo $"Usage: $cmd {start|stop|status|restart}"
    exit 2
esac
