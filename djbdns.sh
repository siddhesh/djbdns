#!/bin/sh
#
# djbdns: script is to start/stop the djbdns service daemon.
#
# chkconfig: 35 20 80
# description: djbdns is a Domain Name System(DNS for short) daemon. \
#              A DNS is a program used to map the given domain name to it's \
#              IP address or vice versa.
#

### BEGIN INIT INFO
# Provides: djbdns
# Required-Start: $network
# Required-Stop: $network
#
# Short-Description: start and stop djbdns daemon.
# Description: djbdns is a Domain Name System(DNS for short) daemon.
#              A DNS is a program used to map the given domain name to it's
#              IP address or vice versa.
#
### END INIT INFO

# Source function library.
. /etc/init.d/functions

# Source networking configuration
. /etc/sysconfig/network

prog=PREFIX/bin/dnscache
logfile="/var/log/`basename $prog`.log"
lockfile=/var/lock/subsys/`basename $prog`

start ()
{
    # Check if networking is up.
    [ "$NETWORKING" = "no" ] && exit 1

    [ -x $prog ] || exit 5

    # Start daemon.
    echo -n $"Starting `basename $prog`: "
    daemon $prog -d3 -D 2>> $logfile
    RETVAL=$?

    chmod og= $logfile
    echo
    [ $RETVAL -eq 0 ] && touch $lockfile

    return $RETVAL
}

stop ()
{
    echo -n $"Shutting down `basename $prog`: "
    killproc $prog
    RETVAL=$?
    echo
    [ $RETVAL -eq 0 ] && rm -f $lockfile

    return $RETVAL
}


cmd="`basename $0`"

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
