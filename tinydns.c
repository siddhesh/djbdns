#include "dns.h"

short debug_level = 0;

const char *fatal = "tinydns: fatal: ";
const char *starting = "starting tinydns\n";

static char seed[128];

void initialize(void)
{
  dns_random_init(seed);
}
