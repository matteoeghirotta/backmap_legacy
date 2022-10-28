#ifndef	FRAGMENT_H_
#define	FRAGMENT_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "atom.h"
#include "string_utils.h"

typedef struct fragment {
  atom *atoms;
  int natoms;
  char *name;
  char *filename;
} fragment;

typedef struct fragments {
  fragment *fragments;
  int n;
} fragments;

fragment *
fragment_parse_equivalents(FILE *h,
			   char const* filename)
{
  char *endptr;
  char *line = NULL;
  size_t len = 0;
  ssize_t chars_read = 0;

  fragment *f = calloc(1, sizeof(fragment));
  f->filename = strdup(filename);

  // number of atoms
  if ((chars_read = getline(&line, &len, h)) != -1) {
    f->natoms = strtod(line, &endptr);

    if ((chars_read == 1) && (strncmp(line, "\n", 1) == 0)) {
      goto cleanup;
    }

    if ((*endptr != '\n')
        &&
        (*endptr != ' ')) {
      fprintf(stderr, "error reading file %s : natoms: <%s> line: %s\n",
	      filename, endptr, line);
      exit(EXIT_FAILURE);
    }    
  } else {
    goto cleanup;
    /* free(f); */
    /* return NULL; */
  }

  // comment
  if ((chars_read = getline(&line, &len, h)) != -1) {
    int token_count = 0;
    token_iter(line,
    	       " ",
	       name,
	       token_count++;
	       if (token_count == 1) {
		 f->name = strdup(name);
		 /* printf("name %s:%s\n", name, f->name); */
	       }
      );
  }

  char *save_ptr = NULL;
  char const* delim = " ";

  // atoms
  long savepos = 0;
  int natom = 0;  
  while ((chars_read = getline(&line, &len, h)) != -1) {
    if (natom == f->natoms) {
      // rewind ...
      fseek(h, savepos, SEEK_SET);
      break;
    }

    char *token = strtok_r(line, delim, &save_ptr);
    f->atoms = realloc(f->atoms, sizeof(atom)*(natom+1));
    //printf("alloc frag atoms %p\n", f->atoms);
    f->atoms[natom].name = strdup(token);

    /* printf("ATOM <%s> %s\n", f->atoms[natom].name, filename); */

    int i = 0;
    while ((token = strtok_r(NULL, delim, &save_ptr))
	   && (i < 3)) {
      f->atoms[natom].pos[i++] = strtod(token, &endptr);
      //printf("%f ", f->atoms[natom].pos[i-1]);
    }
    //printf("\n");

    natom++;
    savepos = ftell(h);
  }

  free(line);
  return f;

  cleanup:
  free(line);
  free(f);
  f = NULL;
  return f;
}

int
fragment_find_atom(fragments *fs, atom *atom)
{
  char *name = atom->name; // atom_name_strip(atom->name);
  int n = 0;

  for (int i=0; i<fs->n; ++i) {
    fragment *fi = &fs->fragments[i];

    for (int ii=0; ii<fi->natoms; ++ii) {
      char *name_i = fi->atoms[ii].name;

      if ((strcmp(name_i, name) == 0)) {
	n++;
      }
    }
  }

  return n;
}

fragments *
fragment_parse_xyz(char const* filename)
{
  FILE *h = fopen(filename, "r");
  if (!h) {
    fprintf(stderr, "ERROR: cannot open %s\n", filename);
    exit(EXIT_FAILURE);
  }

  fragments *fs = malloc(sizeof(fragments));  

  fs->fragments = malloc(sizeof(fragment));  
  fs->n = 0;

  fragment *f = NULL;

  do {
    f = fragment_parse_equivalents(h, filename);

    if (f) {
      fs->fragments = realloc(fs->fragments, sizeof(fragment)*(fs->n+1));
      fs->fragments[fs->n] = *f;
      fs->n++;
    }
  } while (f);

  //printf("fragment %s has %i fragments\n", filename, fs->n);

  fclose(h);

  return fs;
}

#endif	    /* !FRAGMENT_H_ */
