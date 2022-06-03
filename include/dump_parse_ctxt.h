#ifndef	DUMP_PARSE_CTXT_H_
#define	DUMP_PARSE_CTXT_H_

typedef struct dump_parse_ctxt {
  bool parsing_timestep;
  bool parsing_natoms;
  bool parsing_bounds;
  bool parsing_atoms;
  bool parsing_atoms_novel;
  int  parsing_bounds_count;
  int  parsing_natoms_count;
  bool parsed_natoms;
  bool parsed_configuration;
  char *line;
  int linen;
  particle *p;
  int ntimestep;
  double bounds[3];
  FILE *out_file;
  char *out_filename;
  char *prefix_file;
  int natoms;
  int nmols;
  int ntypes;
  int current_atom;
  particle *particles;
  bool particles_allocated;
  // section *section;
  struct fragments **fragments;
  int last_atom_index;
  int *frag_count;
} dump_parse_ctxt;


void
dump_parse_ctxt_new_timestep(dump_parse_ctxt *ctxt)
{
  int ndigits = 8;
  if (!ctxt->out_filename)
    ctxt->out_filename = malloc(strlen(ctxt->prefix_file)
                                + 1   // .
                                + ndigits
                                + 1); // \0

  ctxt->parsing_timestep = false;
  ctxt->parsing_natoms = false;
  ctxt->parsed_natoms = false;
  ctxt->parsed_configuration = false;
  ctxt->parsing_bounds = false;
  ctxt->parsing_bounds_count = 0;
  ctxt->parsing_natoms_count = 0;
  ctxt->parsing_atoms = false;
  ctxt->parsing_atoms_novel = false;
  memset(ctxt->bounds, 0, sizeof(double)*3);

  ctxt->natoms = 0;
  ctxt->current_atom = 0;
  ctxt->nmols = 0;
  ctxt->ntypes = 0;
  ctxt->particles = NULL;
  /* ctxt->fragments = NULL; */ // assigned at start, must not null
  ctxt->particles_allocated = false;
  ctxt->last_atom_index = 0;
  ctxt->frag_count = NULL;
}

#endif	    /* !DUMP_PARSE_CTXT_H_ */
