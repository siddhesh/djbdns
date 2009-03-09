\" Use nroff -ms <file-name> to format this file
\"

.ll 6i
.po 1i
.pl 66

.nr LL 6i
.nr PO 1i
.nr PL 66

\" No hyphenation
.hy 0
.nr HY 0


.DS C
djbdns-1.05.1
=============
.DE

.LP
Hello all,

.PP
I am pleased to release this *new* version of djbdns-1.05.1. Djbdns is a
fully-fledged Domain Name System(DNS), originally written by the eminent
author of qmail, Dr. D J Bernstein. This new release is a complete makeover
to the original source(djbdns-1.05) and is meant to make life a lot more
pleasant. The notable changes so far are in the set-up & configuration steps.
The original source is in public-domain since late Dec 2007.

.in +4
Please see: http://cr.yp.to/distributors.html
.in -4

Nevertheless, this new release is distributed under the GNU General Public
Licence for good. See ChangeLog for more details.

Installation:
.br
-------------
.sp
To install djbdns: just say
.DS I
sh>$ ./configure [ --prefix=/usr/local ]
sh>$ make
sh># make install
.DE

Once installed, On Linux machines add `dnscache' to the system services
by following steps. Note that, if you chose a different install prefix with
`--prefix' use that while creating the link with ln.
.DS I
sh># ln -s /usr/local/bin/djbdns /etc/init.d/djbdns
sh># chkconfig --add djbdns
sh># chkconfig --list djbdns
.DE

Now you can start the service by

.DS I
sh># service djbdns start
         OR
sh># dnscache -D
.DE

Consult the dnscahce(1) manual page for more help.

.DS L
Problems:
---------
.DE

.PP
If you encounter any problems while installing djbdns OR find any bugs in
working of djbdns, please send an email to <prasad@redhat.com> describing in
details about the problem/bug.

.sp 2
.LP
Thank you!
