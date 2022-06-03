#ifndef	DUMP_H_
#define	DUMP_H_

#include <sys/types.h> // lseek
#include <unistd.h>    // lseek
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>
#include "particle.h"
#include "string_utils.h"
#include "fragment.h"
#include "quat_utils.h"
#include "file_utils.h"
#include "trie.h"
#include "dump_parse_ctxt.h"
#include "dump_atom_fields.h"
#include "dump_sections.h"
#include "dump_parse.h"
#include "particle_transform.h"

void
dump_transform(char const* in,
	       char const* prefix,
	       fragments **fragments,
	       bool on_the_fly)
{
  open_file_assert(hin, in, "r");

  char *line = NULL;
  size_t len = 0;
  ssize_t chars_read = 0;

  dump_parse_ctxt ctxt = {};
  particle p = {};
  ctxt.p = &p;
  ctxt.fragments = fragments;
  ctxt.prefix_file = strdup(prefix);

  bool flush = !on_the_fly;

  int linen = 1;
  while ((chars_read = getline(&line, &len, hin)) != -1) {
    line[chars_read-1] = '\0';
    ctxt.line = line;
    ctxt.linen = linen++;

    particle *p;
    if (on_the_fly) {
      if (parse_dump_line_on_the_fly(&ctxt, false)) {
	particle_transform_on_the_fly(&ctxt,
				      fragments[ctxt.p->type-1]->fragments,
				      false);
      }
    } else {
      p = parse_dump_line(&ctxt, false);
      if (p) free(p);
    }
  }

  if (!on_the_fly) {
    flush = true;
    printf("\nflushing\n");
    particle *p = parse_dump_line(&ctxt, flush);
    if (p) free(p);
  }

  fclose(hin);

  free(ctxt.particles);
  free(ctxt.frag_count);
  free(ctxt.prefix_file);
  free(ctxt.out_filename);
}

#endif	    /* !DUMP_H_ */
