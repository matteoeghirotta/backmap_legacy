#ifndef	DUMP_PARSE_H
#define	DUMP_PARSE_H

#include "verbose.h"
#include "particle.h"
#include "particle_transform.h"

particle *
parse_dump_line(dump_parse_ctxt *ctxt,
                bool flush, int verbose)
{
  ctxt->p = calloc(1, sizeof(particle));

  if (verbose >= MEDIUM) printf("LINE %i <%s> %i\n", ctxt->linen, ctxt->line, ctxt->parsed_configuration);

  if (ctxt->parsing_timestep) {
    if (verbose >= MEDIUM) printf("Parsing timestep: %s\n", ctxt->line);

    if (ctxt->out_file && ctxt->parsed_configuration) {
      if (verbose >= MEDIUM) printf("closing %s\n", ctxt->out_filename);

      fclose(ctxt->out_file);
      ctxt->parsed_configuration = false;
    }

    dump_parse_ctxt_new_timestep(ctxt);

    parse_double(ctxt->line, ctxt->ntimestep);

    sprintf(ctxt->out_filename,
            "%s.%08i",
            ctxt->prefix_file, ctxt->ntimestep);

    open_file_assert(hout, ctxt->out_filename, "w");
    ctxt->out_file = hout;

    ctxt->parsing_timestep = false;
  } else if (ctxt->parsing_natoms) {
    if (verbose >= MEDIUM) printf("parsing_natoms from %s\n", ctxt->line);

    if (ctxt->parsing_natoms_count == 0) {
      ctxt->natoms = atoi(ctxt->line);
      ctxt->parsing_natoms = false;
      ctxt->parsed_natoms = true;
    }

    if (!ctxt->particles) {
      if (verbose >= MEDIUM) {
        printf("allocating %i particles\n", ctxt->natoms);
      }

      ctxt->particles = malloc(sizeof(particle)*ctxt->natoms);
      ctxt->particles_allocated = true;
    }

    ctxt->parsing_natoms_count++;
  } else if (ctxt->parsed_natoms && (!ctxt->particles_allocated)) {
    if (!ctxt->particles) {
      if (verbose >= MEDIUM) {
        printf("allocating %i particles\n", ctxt->natoms);
      }

      ctxt->particles = malloc(sizeof(particle)*ctxt->natoms);
    }

    if (!ctxt->particles) {
      fprintf(stderr, "ERROR allocating %i particles\n", ctxt->natoms);
      exit(1);
    }

    ctxt->particles_allocated = true;
  } else if (ctxt->parsing_bounds) {
    if (verbose >= MEDIUM) {
      printf("parsing bounds\n");
    }

    int ntok = 0;
    char *tokens[2];
    token_iter(ctxt->line,
               " ",
               tok,
               tokens[ntok++] = strdup(tok);
              );

    double lo;
    parse_double(tokens[0], lo,
                 fprintf(stderr, "ctxt %i in line %i:%s\n", 0,
                         ctxt->linen, ctxt->line);
                 exit(1);
                );

    double hi;
    parse_double(tokens[1], hi,
                 fprintf(stderr, "ctxt %i in line %i:%s\n", 0,
                         ctxt->linen, ctxt->line);
                 exit(1);
                );

    for (int i=0; i<2; ++i)
      free(tokens[i]);

    ctxt->bounds[ctxt->parsing_bounds_count] = hi-lo;

    if (ctxt->parsing_bounds_count == 2) {
      ctxt->parsing_bounds = false;
      ctxt->parsing_bounds_count = 0;

      fprintf(ctxt->out_file,
              "CRYST1 %8.3f %8.3f %8.3f  90.00  90.00  90.00 P 1           1\n",
              ctxt->bounds[0], ctxt->bounds[1], ctxt->bounds[2]);
    } else {
      ctxt->parsing_bounds_count++;
    }
  } else if (ctxt->parsing_atoms) {
    if (verbose >= MEDIUM) printf("parsing_atoms from %s\n", ctxt->line);

    int ntok = 0;
    char *tokens[dump_atom_field_END];

    token_iter(ctxt->line,
               " ",
               tok,
               // printf("DEBUG %2i %s\n", ntok, tok);
               if (tok) tokens[ntok++] = strdup(tok);
              );

    if (ntok != section_atoms.nfields) {
      if (verbose == HIGH) {
        printf("ntok %i instead of %i REPARSE line %i : %s\n",
               ntok, section_atoms.nfields, ctxt->linen, ctxt->line);
      }

      ctxt->parsed_configuration = true;

      goto match_context;
    }

    if (section_atoms.indices[dump_atom_field_id] != -1)
      parse_int(tokens[section_atoms.indices[dump_atom_field_id]],
                ctxt->p->atomID,
                fprintf(stderr, "reparsing %s|ctxt %i line %i\n",
                        ctxt->line,
                        dump_atom_field_type,
                        ctxt->linen);
                goto match_context;
               );


    if (section_atoms.indices[dump_atom_field_type] != -1)
      parse_int(tokens[section_atoms.indices[dump_atom_field_type]],
                ctxt->p->type,
                fprintf(stderr, "reparsing %s|ctxt %i line %i\n",
                        ctxt->line,
                        dump_atom_field_type,
                        ctxt->linen);
                goto match_context;
               );

    if (ctxt->p->type > ctxt->ntypes) {
      ctxt->ntypes = ctxt->p->type;
    }

    if (section_atoms.indices[dump_atom_field_x] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_x]],
                   ctxt->p->pos[0],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_x,
                           ctxt->linen, ctxt->line);
                   goto match_context;
                  );

    if (section_atoms.indices[dump_atom_field_y] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_y]],
                   ctxt->p->pos[1],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_y,
                           ctxt->linen, ctxt->line);
                   goto match_context;
                  );

    if (section_atoms.indices[dump_atom_field_z] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_z]],
                   ctxt->p->pos[2],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_z,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_qw] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_qw]],
                   ctxt->p->quat[0],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_qw,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_qx] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_qx]],
                   ctxt->p->quat[1],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_qx,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_qy] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_qy]],
                   ctxt->p->quat[2],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_qy,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_qz] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_qz]],
                   ctxt->p->quat[3],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_qz,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_vx] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_vx]],
                   ctxt->p->vel[0],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_vx,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_vy] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_vy]],
                   ctxt->p->vel[1],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_vy,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_vz] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_vz]],
                   ctxt->p->vel[2],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_vz,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_angmomx] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_angmomx]],
                   ctxt->p->angmom[0],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_angmomx,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_angmomy] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_angmomy]],
                   ctxt->p->angmom[1],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_angmomy,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_angmomz] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_angmomz]],
                   ctxt->p->angmom[2],
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_angmomz,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );

    if (section_atoms.indices[dump_atom_field_mol] != -1)
      parse_double(tokens[section_atoms.indices[dump_atom_field_mol]],
                   ctxt->p->mol,
                   fprintf(stderr, "ctxt %i in line %i:%s\n",
                           dump_atom_field_mol,
                           ctxt->linen, ctxt->line);
                   exit(1);
                  );


    if (ctxt->p->mol > ctxt->nmols) {
      ctxt->nmols = ctxt->p->mol;
    }

    ctxt->particles[ctxt->p->atomID-1] = *ctxt->p;
    ctxt->natoms_parsed++;
  }


  if (verbose >= HIGH) printf("HERE: ntypes %i nmols %i | %i %i %i\n", ctxt->ntypes, ctxt->nmols, ctxt->natoms, ctxt->natoms_parsed, flush);

  if (ctxt->natoms == ctxt->natoms_parsed) {
    int frag_counts = ctxt->ntypes*ctxt->nmols;

    if (verbose >= MEDIUM) {
      printf("frag counts:%i ntypes:%i nmols:%i %i\n",
             frag_counts, ctxt->ntypes, ctxt->nmols, ctxt->particles_allocated);
    }

    ctxt->last_atom_index = 1;

    if (ctxt->frag_count)
      free(ctxt->frag_count);

    ctxt->frag_count = calloc(frag_counts, sizeof(int));

    if (verbose >= MEDIUM) {
      printf("ENTER LOOP atoms:%i frags:%i\n", ctxt->natoms, frag_counts);
    }

    // CG particles
    for (int i=0; i<ctxt->natoms; ++i) {
      particle p = ctxt->particles[i];
      int atom_type = p.type-1;
      int mol_index = p.mol-1;
      struct fragments *fragments = ctxt->fragments[atom_type];
      int frag_index = ctxt->ntypes*mol_index + atom_type;

      assert(frag_index < frag_counts);

      if (verbose >= MEDIUM) {
        printf("PP %i %i %i\n", atom_type, mol_index, i);
      }

      ctxt->last_atom_index = particle_transform(ctxt->out_file,
                                                 ctxt->last_atom_index,
                                                 ctxt->frag_count[frag_index],
                                                 &p,
                                                 fragments);

      if (ctxt->frag_count[frag_index] + 1 == fragments->n) {
        ctxt->frag_count[frag_index] = 0;
      } else {
        ctxt->frag_count[frag_index]++;
      }
    }
  }

match_context:
#define match_header_debug(header)						    \
  printf("match %s ? %i\n",							    \
         header, strncmp(header, ctxt->line, strlen(header))),			    \
  (strncmp(header, ctxt->line, strlen(header)) == 0)

#define match_header(header)							    \
  (strncmp(header, ctxt->line, strlen(header)) == 0)

  if (match_header(section_timestep.header)) {
    ctxt->parsing_timestep = true;
  } else if (match_header(section_natoms.header)) {
    ctxt->parsing_natoms = true;
  } else if (match_header(section_bounds.header)) {
    ctxt->parsing_bounds = true;
  } else if (match_header(section_atoms.header)) {
    int *indices = section_atoms_generic_parse(ctxt->line, verbose);
    section_atoms.indices = indices;

    if (verbose >= TOP) {
      printf("MATCH HEADER parsing_atoms\n");
      for (int i = 0; i < dump_atom_field_END; i++) {
        printf("indices %i %i \n", i, indices[i]);
      }

      fflush(stdout);
    }

    ctxt->parsing_atoms = true;
  }
#undef match_header
#undef match_header_debug

  return ctxt->p;
}

#endif	    /* !DUMP_PARSE_H */
