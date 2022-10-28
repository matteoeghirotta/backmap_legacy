#ifndef	DUMP_PARSE_ON_THE_FLY_H
#define	DUMP_PARSE_ON_THE_FLY_H

#include "particle.h"
#include "particle_transform.h"

particle *
parse_dump_line_on_the_fly(dump_parse_ctxt *ctxt, bool dump_xyz)
{
  particle *p = NULL;

  if (ctxt->out_file && feof(ctxt->out_file)) {
    if (dump_xyz)
      fprintf(ctxt->out_file, "%i\n", ctxt->natoms);
    fclose(ctxt->out_file);
  }

  if (ctxt->parsing_timestep) {
    if (ctxt->out_file) {
      if (dump_xyz)
	fprintf(ctxt->out_file, "%i\n", ctxt->natoms);
      fclose(ctxt->out_file);
    }

    dump_parse_ctxt_new_timestep(ctxt);

    parse_double(ctxt->line, ctxt->ntimestep);

    sprintf(ctxt->out_filename,
	    "%s.%06i",
	    ctxt->prefix_file, ctxt->ntimestep);

    open_file_assert(hout, ctxt->out_filename, "w");
    ctxt->out_file = hout;

    ctxt->parsing_timestep = false;
  } else if (ctxt->parsing_natoms) {
    ctxt->parsing_natoms = false;
  } else if (ctxt->parsing_bounds) {
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

    ctxt->bounds[ctxt->parsing_bounds_count] = hi-lo;

    if (ctxt->parsing_bounds_count == 2) {
      ctxt->parsing_bounds = false;
      ctxt->parsing_bounds_count = 0;

      if (dump_xyz) {
	fprintf(ctxt->out_file,
		"# %f %f %f\n",
		ctxt->bounds[0], ctxt->bounds[1], ctxt->bounds[2]);
      } else {
	fprintf(ctxt->out_file,
		"CRYST1 %8.3f %8.3f %8.3f  90.00  90.00  90.00 P 1           1\n",
		ctxt->bounds[0], ctxt->bounds[1], ctxt->bounds[2]);
      }
    } else {
      ctxt->parsing_bounds_count++;
    }
  } else if (ctxt->parsing_atoms) {
    printf("PARSING ATOMS 2\n");

    int ntok = 0;
    char *tokens[dump_atom_field_END];
    token_iter(ctxt->line,
    	       " ",
    	       tok,
	       tokens[ntok++] = strdup(tok);
      );

    // if ((ntok != section_atoms.nfields)
    //     && (ntok != section_atoms_novel.nfields)
    //     && (ntok != section_atoms_novel_unwrap.nfields)
    //     && (ntok != section_atoms_unwrap.nfields)) {
    //   [> fprintf(stderr, "n %i instead of %i REPARSE line %i : %s\n", <]
    //   [> 	      ntok, section_atoms_novel.nfields, ctxt->linen, ctxt->line); <]
    //   goto match_context;
    // }

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

    printf("Reassign: %i %i\n", ctxt->p->type , ctxt->ntypes);

    if (ctxt->p->type > ctxt->ntypes) {
      printf("REASSIGN: %i %i\n", ctxt->p->type , ctxt->ntypes);

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

    p = ctxt->p;
  }

  match_context:  
#define match_header_debug(header) \
  printf("match %s ? %i\n",header,strncmp(header, ctxt->line, strlen(header))),(strncmp(header, ctxt->line, strlen(header)) == 0)			     

#define match_header(header)						     \
  (strncmp(header, ctxt->line, strlen(header)) == 0)

  if (match_header(section_timestep.header)) {
    ctxt->parsing_timestep = true;
  } else if (match_header(section_natoms.header)) {
    ctxt->parsing_natoms = true;
  } else if (match_header(section_bounds.header)) {
    ctxt->parsing_bounds = true;
  } else if (match_header(section_atoms.header)) {
    ctxt->parsing_atoms = true;
  }
#undef match_header
#undef match_header_debug

  return p;
}

#endif

