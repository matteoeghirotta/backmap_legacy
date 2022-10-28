#include <stdio.h>
#include <stdlib.h>

void usage(char *progname)
{
  fprintf(stderr, "Usage: %s [[-s] [-t <templates>] -o <out-prefix>] "
	  "dumpfilename\n",
	  progname);
  exit(EXIT_FAILURE);
}
