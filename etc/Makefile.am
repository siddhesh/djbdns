##
## Process this file with automake to produce 'Makefile.in'
##
## To create the configure script using this file follow these steps
## in order
## 1. write Makefile.am
## 2. autoscan
## 3. aclocal
## 4. autoheader
## 5. autoconf
## 6. automake -ac --foreign
##

SUBDIRS = ip servers

confdir = $(sysconfdir)/djbdns
conf_DATA = dnscache.conf tinydns.conf

$(conf_DATA): dnscache-conf tinydns-conf
	sed -e 's:PREFIX:${confdir}:' dnscache-conf > dnscache.conf
	sed -e 's:PREFIX:${confdir}:' tinydns-conf > tinydns.conf


CLEANFILES = $(conf_DATA)
EXTRA_DIST = dnscache-conf tinydns-conf dnsroots.global
