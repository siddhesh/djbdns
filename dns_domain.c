#include <assert.h>
#include <unistd.h>

#include "error.h"
#include "alloc.h"
#include "case.h"
#include "byte.h"
#include "dns.h"

unsigned int
dns_domain_length (const char *dn)
{
    const char *x = dn;
    unsigned char c = 0;

    if (x)
        while (c = *x++)
            x += (unsigned int) c;

    return x - dn;
}

void
dns_domain_free (char **out)
{
    if (*out)
    {
        alloc_free (*out);
        *out = 0;
    }
}

int
dns_domain_copy (char **out, const char *in)
{
    char *x = NULL;
    unsigned int len = 0;

    assert (in != NULL);
    assert (out != NULL);

    len = dns_domain_length (in);
    if (!(x = alloc (len)))
        return 0;

    byte_copy (x, len, in);
    if (*out)
        alloc_free (*out);
    *out = x;

    return 1;
}

int
dns_domain_equal (const char *dn1, const char *dn2)
{
    unsigned int len = 0;

    len = dns_domain_length (dn1);
    if (len != dns_domain_length (dn2))
        return 0;
    if (case_diffb (dn1, len, dn2))
        return 0; /* safe since 63 < 'A' */

    return 1;
}

int
dns_domain_suffix (const char *big, const char *little)
{
    unsigned char c = 0;

    for (;;)
    {
        if (dns_domain_equal (big, little))
            return 1;
        if (!(c = *big++))
            return 0;

        big += c;
    }
}

unsigned int
dns_domain_suffixpos (const char *big, const char *little)
{
    unsigned char c = 0;
    const char *orig = big;

    for (;;)
    {
        if (dns_domain_equal (big, little))
            return big - orig;
        if (!(c = *big++))
            return 0;

        big += c;
    }
}
