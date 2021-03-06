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

AM_CFLAGS=-g -O2 -Wall -Wextra -D PREFIX=\"${prefix}\" \
                               -D SYSCONFDIR=\"${sysconfdir}\"

SUBDIRS = etc

bin_PROGRAMS = dnscache dnsip dnsipq dnsq dnsmx dnsname dnstxt dnsqr \
	dnsfilter dnstrace tinydns tinydns-data tinydns-edit tinydns-get

noinst_PROGRAMS = axfrdns axfrdns-conf axfr-get dnscache-conf tinydns-conf \
	pickdns pickdns-conf pickdns-data random-ip rbldns rbldns-conf \
	rbldns-data walldns walldns-conf

bin_SCRIPTS = dnscached tinydnsd dnstracesort

noinst_MANS = dnscache.ms dnsip.ms dnsq.ms dnsfilter.ms djbdns.ms \
	tinydns-data.ms tinydns-edit.ms tinydns-get.ms tinydns.ms

nodist_man1_MANS = dnscache.1 dnsip.1 dnsq.1 dnsfilter.1 djbdns.1 \
	tinydns-data.1 tinydns-edit.1 tinydns-get.1 tinydns.1

CLEANFILES = $(bin_SCRIPTS) $(nodist_man1_MANS)
EXTRA_DIST = dnstracesort.sh dnscache.sh tinydns.sh readme.ms README \
	INSTALL TODO ChangeLog COPYING $(noinst_MANS)

axfrdns_SOURCES = axfrdns.c iopause.c droproot.c tdlookup.c response.c \
	qlog.c prot.c timeoutread.c timeoutwrite.c \
	droproot.h timeoutread.h timeoutwrite.h qlog.h response.h select.h \
	prot.h hasshsgr.h
axfrdns_LDADD = libdns.a libtai.a liballoc.a libenv.a \
	libbuffer.a libunix.a libbyte.a

axfrdns_LDFLAGS = -lcdb

axfrdns_conf_SOURCES = axfrdns-conf.c generic-conf.c auto_home.c \
	auto_home.h generic-conf.h
axfrdns_conf_LDADD = libbuffer.a libunix.a libbyte.a

axfr_get_SOURCES = axfr-get.c iopause.c timeoutread.c timeoutwrite.c \
	timeoutread.h timeoutwrite.h select.h
axfr_get_LDADD = libdns.a libtai.a liballoc.a libbuffer.a libunix.a libbyte.a

# an init script for dnscache service.
dnscached: dnscache.sh
	sed -e 's:PREFIX:${prefix}:' dnscache.sh > dnscached

djbdns.1: djbdns.ms
	cp djbdns.ms djbdns.1

dnscache_SOURCES = dnscache.c droproot.c okclient.c log.c cache.c query.c \
	response.c dd.c roots.c iopause.c prot.c common.c \
	response.h select.h prot.h roots.h query.h cache.h log.h okclient.h \
	dd.h direntry.h hasshsgr.h version.h common.h
dnscache_LDADD = libdns.a libenv.a liballoc.a libbuffer.a libtai.a \
	libunix.a libbyte.a

dnscache.1: dnscache.ms
	sed -e 's:PREFIX:${sysconfdir}:' dnscache.ms > dnscache.1

dnscache_conf_SOURCES = dnscache-conf.c generic-conf.c auto_home.c \
	auto_home.h generic-conf.h hasdevtcp.h
dnscache_conf_LDADD = libtai.a libbuffer.a libunix.a libbyte.a

dnsfilter_SOURCES = dnsfilter.c iopause.c select.h
dnsfilter_LDADD = libgetopt.a libdns.a libenv.a libtai.a liballoc.a \
	libbuffer.a libunix.a libbyte.a

dnsfilter.1: dnsfilter.ms
	cp dnsfilter.ms dnsfilter.1

dnsip_SOURCES = dnsip.c iopause.c select.h version.h
dnsip_LDADD = libdns.a libenv.a libtai.a liballoc.a libbuffer.a \
	libunix.a libbyte.a

dnsip.1: dnsip.ms
	cp dnsip.ms dnsip.1

dnsipq_SOURCES = dnsipq.c iopause.c select.h
dnsipq_LDADD = libdns.a libenv.a libtai.a liballoc.a libbuffer.a \
	libunix.a libbyte.a

dnsmx_SOURCES = dnsmx.c iopause.c select.h
dnsmx_LDADD = libdns.a libenv.a libtai.a liballoc.a libbuffer.a \
	libunix.a libbyte.a

dnsname_SOURCES = dnsname.c iopause.c select.h
dnsname_LDADD = libdns.a libenv.a libtai.a liballoc.a libbuffer.a \
	libunix.a libbyte.a

dnsq_SOURCES = dnsq.c iopause.c printrecord.c printpacket.c parsetype.c \
	select.h printpacket.h parsetype.h printrecord.h
dnsq_LDADD = libdns.a libenv.a libtai.a libbuffer.a liballoc.a \
	libunix.a libbyte.a

dnsq.1: dnsq.ms
	cp dnsq.ms dnsq.1

dnsqr_SOURCES = dnsqr.c iopause.c printrecord.c printpacket.c parsetype.c \
	select.h printpacket.h parsetype.h printrecord.h
dnsqr_LDADD = libdns.a libenv.a libtai.a libbuffer.a liballoc.a \
	libunix.a libbyte.a

dnstrace_SOURCES = dnstrace.c dd.c iopause.c printrecord.c parsetype.c \
	select.h dd.h parsetype.h printrecord.h
dnstrace_LDADD = libdns.a libenv.a libtai.a liballoc.a libbuffer.a \
	libunix.a libbyte.a

dnstracesort: dnstracesort.sh
	cp dnstracesort.sh dnstracesort

dnstxt_SOURCES = dnstxt.c iopause.c select.h
dnstxt_LDADD = libdns.a libenv.a libtai.a liballoc.a libbuffer.a \
	libunix.a libbyte.a

pickdns_SOURCES = pickdns.c server.c response.c droproot.c qlog.c prot.c \
	common.c qlog.h response.h prot.h hasshsgr.h common.h
pickdns_LDADD = libdns.a libenv.a libtai.a liballoc.a libbuffer.a \
	libunix.a libbyte.a
pickdns_LDFLAGS = -lcdb

pickdns_conf_SOURCES = pickdns-conf.c generic-conf.c auto_home.c \
	auto_home.h generic-conf.h
pickdns_conf_LDADD = libbuffer.a libunix.a libbyte.a

pickdns_data_SOURCES = pickdns-data.c
pickdns_data_LDADD = libdns.a liballoc.a libbuffer.a \
	libunix.a libbyte.a
pickdns_data_LDFLAGS = -lcdb

random_ip_SOURCES = random-ip.c
random_ip_LDADD = libdns.a libtai.a libbuffer.a libunix.a libbyte.a

rbldns_SOURCES = rbldns.c server.c response.c dd.c droproot.c qlog.c prot.c \
	common.c qlog.h response.h prot.h dd.h hasshsgr.h common.h
rbldns_LDADD = libdns.a libenv.a libtai.a liballoc.a libbuffer.a \
	libunix.a libbyte.a
rbldns_LDFLAGS = -lcdb

rbldns_conf_SOURCES = rbldns-conf.c generic-conf.c auto_home.c \
	auto_home.h generic-conf.h
rbldns_conf_LDADD = libbuffer.a libunix.a libbyte.a

rbldns_data_SOURCES = rbldns-data.c
rbldns_data_LDADD = liballoc.a libbuffer.a libunix.a libbyte.a
rbldns_data_LDFLAGS = -lcdb

tinydns_SOURCES = tinydns.c server.c droproot.c tdlookup.c response.c \
	qlog.c prot.c common.c \
	qlog.h response.h prot.h hasshsgr.h common.h
tinydns_LDADD = libdns.a libtai.a libenv.a liballoc.a libbuffer.a \
	libunix.a libbyte.a
tinydns_LDFLAGS = -lcdb

# an init script for tinydns service.
tinydnsd: tinydns.sh
	sed -e 's:PREFIX:${prefix}:' tinydns.sh > tinydnsd

tinydns.1: tinydns.ms
	sed -e 's:PREFIX:${sysconfdir}:' tinydns.ms > tinydns.1

tinydns_conf_SOURCES = tinydns-conf.c generic-conf.c auto_home.c \
	auto_home.h generic-conf.h
tinydns_conf_LDADD = libbuffer.a libunix.a libbyte.a

tinydns_data_SOURCES = tinydns-data.c
tinydns_data_LDADD = libdns.a liballoc.a libbuffer.a \
	libunix.a libbyte.a
tinydns_data_LDFLAGS = -lcdb

tinydns-data.1: tinydns-data.ms
	cp tinydns-data.ms tinydns-data.1

tinydns_edit_SOURCES = tinydns-edit.c
tinydns_edit_LDADD = libdns.a liballoc.a libbuffer.a libunix.a libbyte.a

tinydns-edit.1: tinydns-edit.ms
	cp tinydns-edit.ms tinydns-edit.1

tinydns_get_SOURCES = tinydns-get.c tdlookup.c response.c printpacket.c \
	printrecord.c parsetype.c \
	response.h printrecord.h
tinydns_get_LDADD = libdns.a libtai.a libbuffer.a liballoc.a \
	libunix.a libbyte.a
tinydns_get_LDFLAGS = -lcdb

tinydns-get.1: tinydns-get.ms
	cp tinydns-get.ms tinydns-get.1

walldns_SOURCES = walldns.c server.c response.c droproot.c qlog.c prot.c dd.c \
	common.c qlog.h response.h prot.h dd.h hasshsgr.h common.h
walldns_LDADD = libdns.a libenv.a liballoc.a libbuffer.a \
	libunix.a libbyte.a libtai.a
walldns_LDFLAGS = -lcdb

walldns_conf_SOURCES = walldns-conf.c generic-conf.c auto_home.c \
	auto_home.h generic-conf.h
walldns_conf_LDADD = libbuffer.a libunix.a libbyte.a


#
# Static libraries built for compilation. These are NOT installed.
#

noinst_LIBRARIES = liballoc.a libbuffer.a libbyte.a libdns.a \
	libenv.a libgetopt.a libtai.a libunix.a

liballoc_a_SOURCES = alloc.c alloc_re.c getln.c getln2.c stralloc_cat.c \
	stralloc_catb.c stralloc_cats.c stralloc_copy.c stralloc_eady.c \
	stralloc_num.c stralloc_opyb.c stralloc_opys.c stralloc_pend.c \
	alloc.h error.h byte.h getln.h buffer.h stralloc.h gen_alloc.h \
	gen_allocdefs.h str.h

libbuffer_a_SOURCES = buffer.c buffer_1.c buffer_2.c buffer_copy.c \
	buffer_get.c buffer_put.c strerr_die.c strerr_sys.c \
	buffer.h byte.h error.h str.h strerr.h

libbyte_a_SOURCES = byte_chr.c byte_copy.c byte_cr.c byte_diff.c byte_zero.c \
	case_diffb.c case_diffs.c case_lowerb.c fmt_ulong.c ip4_fmt.c \
	ip4_scan.c scan_ulong.c str_chr.c str_diff.c str_len.c str_rchr.c \
	str_start.c uint16_pack.c uint16_unpack.c uint32_pack.c \
	uint32_unpack.c byte.h case.h fmt.h ip4.h scan.h str.h uint16.h \
	uint32.h

#libcdb_a_SOURCES = cdb.c cdb_hash.c cdb_make.c \
#	error.h seek.h byte.h cdb.h uint32.h alloc.h cdb_make.h buffer.h

libdns_a_SOURCES = dns_dfd.c dns_domain.c dns_dtda.c dns_ip.c dns_ipq.c \
	dns_mx.c dns_name.c dns_nd.c dns_packet.c dns_random.c dns_rcip.c \
	dns_rcrw.c dns_resolve.c dns_sortip.c dns_transmit.c dns_txt.c \
	error.h alloc.h byte.h dns.h stralloc.h gen_alloc.h iopause.h taia.h \
	tai.h uint64.h case.h uint16.h str.h fmt.h uint32.h openreadclose.h \
	ip4.h env.h socket.h select.h

libenv_a_SOURCES = env.c str.h env.h

libgetopt_a_SOURCES = sgetopt.c subgetopt.c \
	buffer.h sgetopt.h subgetopt.h subgetopt.h

libtai_a_SOURCES = tai_add.c tai_now.c tai_pack.c tai_sub.c tai_uint.c \
	tai_unpack.c taia_add.c taia_approx.c taia_frac.c taia_less.c \
	taia_now.c taia_pack.c taia_sub.c taia_tai.c taia_uint.c \
	tai.h uint64.h taia.h

libunix_a_SOURCES = buffer_read.c buffer_write.c error.c error_str.c \
	ndelay_off.c ndelay_on.c open_read.c open_trunc.c openreadclose.c \
	readclose.c seek_set.c socket_accept.c socket_bind.c socket_conn.c \
	socket_listen.c socket_recv.c socket_send.c socket_tcp.c socket_udp.c \
	buffer.h error.h ndelay.h open.h readclose.h stralloc.h gen_alloc.h \
	openreadclose.h seek.h byte.h socket.h uint16.h
