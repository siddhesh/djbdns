#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "byte.h"
#include "socket.h"

int
socket_recv4 (int s, char *buf, int len, char ip[4], uint16 *port)
{
    int r = 0;
    struct sockaddr_in sa;
    int dummy = sizeof (sa);

    r = recvfrom (s, buf, len, 0, (struct sockaddr *)&sa, &dummy);
    if (r == -1)
        return -1;

    byte_copy (ip, 4, (char *)&sa.sin_addr);
    uint16_unpack_big ((char *)&sa.sin_port, port);

    return r;
}
