#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "fragment.h"
#include "dump.h"

void usage(char *progname)
{
  fprintf(stderr, "Usage: %s [[-s] [-t <templates>] -o <out-prefix>] "
	  "dumpfilename\n",
	  progname);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
  char **templates = NULL;
  int ntemplates = 0;
  char *output_prefix = NULL;
  /* bool dump_xyz = false; */
  bool on_the_fly = false;

  char const short_options[] = "t:o:f";
  int optc = 0;

  while ((optc = getopt (argc, argv, short_options)) != -1) {
    switch (optc) {
    case 't':
      templates = realloc(templates, sizeof(char*)*(ntemplates+1));
      templates[ntemplates++] = strdup(optarg);
      break;
    case 'o':
      output_prefix = strdup(optarg);
      break;
    /* case 'x': */
    /*   dump_xyz = true; */
    /*   break; */
    case 'f':
      on_the_fly = true;
      break;
    default:
      usage(argv[0]);
    }
  }

  char *dumpfilename = argv[optind];

  if (!output_prefix) {
    if (dumpfilename) {
      output_prefix = strdup(dumpfilename);
    } else {
      usage(argv[0]);
      exit(1);
    }
  }

  struct fragments *fs[ntemplates];

  for (int i=0; i<ntemplates; ++i) {
    fs[i] = fragment_parse_xyz(templates[i]);
  }

  if (optind != argc-1) {
    usage(argv[0]);
  }

  dump_transform(dumpfilename, output_prefix, fs, on_the_fly);

  free(output_prefix);

  for (int i=0; i<ntemplates; ++i) {
    free(fs[i]->fragments);
    free(fs[i]);
  }

  return 0;
}
