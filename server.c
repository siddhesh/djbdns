/*
 * server.c: This file is part of the `djbdns' project, originally written
 * by Dr. D J Bernstein and later released under public-domain since late
 * December 2007 (http://cr.yp.to/distributors.html).
 *
 * I've modified this file for good and am releasing this new version under
 * GNU General Public License.
 * Copyright (C) 2009 Prasad J Pandit
 *
 * This program is a free software; you can redistribute it and/or modify
 * it under the terms of GNU General Public License as published by Free
 * Software Foundation; either version 2 of the license or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * of FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <err.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/resource.h>

#include "version.h"

#include "env.h"
#include "ip4.h"
#include "dns.h"
#include "qlog.h"
#include "byte.h"
#include "case.h"
#include "buffer.h"
#include "strerr.h"
#include "uint16.h"
#include "ndelay.h"
#include "socket.h"
#include "common.h"
#include "droproot.h"
#include "response.h"

extern void initialize (void);
extern int respond (char *, char *, char *);

static char ip[4];
static uint16 port;

static int len;
static char *q;
static char buf[1024];

static char *prog = NULL;
short mode = 0, debug_level = 0;

enum op_mode { DAEMON = 1, DEBUG = 2 };

void
usage (void)
{
    printf ("Usage: %s [OPTIONS]\n", prog);
}

void
printh (void)
{
    usage ();
    printf ("\n Options: \n");
    printf ("%-17s %s\n", "   -d <value>", "print debug messages");
    printf ("%-17s %s\n", "   -D", "run as daemon");
    printf ("%-17s %s\n", "   -h --help", "print this help");
    printf ("%-17s %s\n", "   -v --version", "print version information");
    printf ("\nReport bugs to <pj.pandit@yahoo.co.in>\n");
}

int
check_option (int argc, char *argv[])
{
    int n = 0, ind = 0;
    const char optstr[] = "+:d:Dhv";
    struct option lopt[] = \
    {
        { "help", no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'v' },
        { 0, 0, 0, 0 }
    };

    opterr = optind = mode = 0;
    while ((n = getopt_long (argc, argv, optstr, lopt, &ind)) != -1)
    {
        switch (n)
        {
        case 'd':
            mode |= DEBUG;
            debug_level = atoi (optarg);
            break;

        case 'D':
            mode |= DAEMON;
            break;

        case 'h':
            printh ();
            exit (0);

        case 'v':
            printf ("%s version %s\n", prog, VERSION);
            exit (0);

        case ':':
            errx (-1, "option `%c' takes an argument, see: --help", optopt);

        default:
            errx (-1, "unknown option `%c', see: --help", optopt);
        }
    }

    return optind;
}

static int
doit (void)
{
    char qtype[2];
    char qclass[2];
    char header[12];
    unsigned int pos = 0;

    if (len >= sizeof buf)
        goto NOQ;
    if (!(pos = dns_packet_copy (buf, len, 0, header, 12)))
        goto NOQ;
    if (header[2] & 128)
        goto NOQ;
    if (header[4])
        goto NOQ;
    if (header[5] != 1)
        goto NOQ;

    if (!(pos = dns_packet_getname (buf, len, pos, &q)))
        goto NOQ;
    if (!(pos = dns_packet_copy (buf, len, pos, qtype, 2)))
        goto NOQ;
    if (!(pos = dns_packet_copy (buf, len, pos, qclass, 2)))
        goto NOQ;

    if (!response_query (q, qtype, qclass))
        goto NOQ;
    response_id (header);

    if (byte_equal (qclass, 2, DNS_C_IN))
        response[2] |= 4;
    else if (byte_diff (qclass, 2, DNS_C_ANY))
            goto WEIRDCLASS;
    response[3] &= ~128;
    if (!(header[2] & 1))
        response[2] &= ~1;

    if (header[2] & 126)
        goto NOTIMP;
    if (byte_equal (qtype, 2, DNS_T_AXFR))
        goto NOTIMP;

    case_lowerb (q, dns_domain_length (q));
    if (!respond (q, qtype, ip))
    {
        qlog (ip, port, header, q, qtype, " - ");
        return 0;
    }
    qlog (ip, port, header, q, qtype, " + ");

    return 1;

NOTIMP:
    response[3] &= ~15;
    response[3] |= 4;
    qlog (ip, port, header, q, qtype, " I ");

    return 1;

WEIRDCLASS:
    response[3] &= ~15;
    response[3] |= 1;
    qlog (ip, port, header, q, qtype, " C ");

    return 1;

NOQ:
    qlog (ip, port, "\0\0", "", "\0\0", " / ");

    return 0;
}

int
main (int argc, char *argv[])
{
    time_t t = 0;
    char *x = NULL;
    struct sigaction sa;
    int i = 0, udp53 = 0;

    prog = strdup ((x = strrchr (argv[0], '/')) != NULL ? x + 1 : argv[0]);

    sa.sa_handler = handle_term;
    sigaction (SIGINT, &sa, NULL);
    sigaction (SIGTERM, &sa, NULL);

    sa.sa_handler = SIG_IGN;
    sigaction (SIGPIPE, &sa, NULL);

    i = check_option (argc, argv);
    argc -= i;
    argv += i;

    if (mode & DAEMON)
    {
        i = fork ();
        if (i == -1)
            err (-1, "could not fork a daemon process");
        if (i > 0)
            return 0;
    }

    time (&t);
    memset (buf, 0, sizeof (buf));
    strftime (buf, sizeof (buf), "%b-%d %Y %T", localtime (&t));
    fprintf (stderr, "\n");
    warnx ("version %s: starting: %s\n", VERSION, buf);

    initialize ();

    if ((x = env_get ("DATALIMIT")))
    {
        struct rlimit r;
        unsigned long dlimit = atol (x);

        if (getrlimit (RLIMIT_DATA,  &r) != 0)
            err (-1, "could not get resource RLIMIT_DATA");

        r.rlim_cur = (dlimit <= r.rlim_max) ? dlimit : r.rlim_max;

        if (setrlimit (RLIMIT_DATA, &r) != 0)
            err (-1, "could not set resource RLIMIT_DATA");

        if (debug_level)
            warnx ("DATALIMIT set to `%ld' bytes", r.rlim_cur);
    }

    if (!(x = env_get ("IP")))
        err (-1, "$IP not set");
    if (!ip4_scan (x, ip))
        err (-1, "could not parse IP address `%s'", x);

    udp53 = socket_udp();
    if (udp53 == -1)
        err (-1, "could not open UDP socket");
    if (socket_bind4_reuse (udp53, ip, 53) == -1)
        err (-1, "could not bind UDP socket");

    droproot ();
  
    ndelay_off (udp53);
    socket_tryreservein (udp53, 65536);

    for (;;)
    {
        len = socket_recv4 (udp53, buf, sizeof buf, ip, &port);
        if (len < 0)
            continue;
        if (!doit ())
            continue;
        if (response_len > 512)
            response_tc ();

        /* may block for buffer space; if it fails, too bad */
        socket_send4 (udp53, response, response_len, ip, port);
    }
}
