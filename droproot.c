#include <err.h>
#include <unistd.h>

#include "env.h"
#include "scan.h"
#include "prot.h"
#include "strerr.h"

extern short mode;
enum op_mode { DEBUG = 2 };

void
droproot (const char *fatal)
{
    char *x = NULL;
    unsigned long id = 0;

    x = env_get ("ROOT");
    if (!x)
        err (-1, "$ROOT not set");
    if (chdir (x) == -1)
        err (-1, "could not change working directory to `%s'", x);
    if (chroot(".") == -1)
        err (-1, "could not change root directory to `%s'", x);

    if (mode & DEBUG)
        warnx ("root & working directory changed to `%s'", x);

    x = env_get ("GID");
    if (!x)
        err (-1, "$GID not set");
    scan_ulong (x, &id);
    if (prot_gid ((int) id) == -1)
        err (-1, "could not set group-id to `%ld'", id);

    x = env_get ("UID");
    if (!x)
        err (-1, "$UID not set");
    scan_ulong (x, &id);
    if (prot_uid ((int) id) == -1)
        err (-1, "could not set user-id to `%ld'", id);

    if (mode & DEBUG)
        warnx ("root privileges dropped, user-id set to `%ld'", id);
}
