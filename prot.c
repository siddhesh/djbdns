#include "hasshsgr.h"
#include "prot.h"

int
prot_gid (int gid)
{
#ifdef HASSHORTSETGROUPS
    short x[2];
    x[0] = gid;
    x[1] = 73; /* catch errors */
    if (setgroups (1, x) == -1)
        return -1;
#else
    if (setgroups(1, &gid) == -1)
        return -1;
#endif

  if (setgid (gid) == -1)
      return -1;

  return setegid (gid); /* _should_ be redundant; On some systems it isn't */
}

int
prot_uid (int uid)
{
    if (setuid (uid) == -1)
        return -1;

    return seteuid (uid);
}
