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

typedef enum {
  dump_atom_field_id,
  dump_atom_field_type,
  dump_atom_field_x,
  dump_atom_field_y,
  dump_atom_field_z,
  dump_atom_field_qw,
  dump_atom_field_qx,
  dump_atom_field_qy,
  dump_atom_field_qz,
  dump_atom_field_shapex,
  dump_atom_field_shapey,
  dump_atom_field_shapez,
  dump_atom_field_vx,
  dump_atom_field_vy,
  dump_atom_field_vz,
  dump_atom_field_angmomx,
  dump_atom_field_angmomy,
  dump_atom_field_angmomz,
  dump_atom_field_mol,
  dump_atom_field_END
} dump_atom_field;

#define MAX_KEYWORDS 12

typedef struct atom_field {
  dump_atom_field field_type;
  bool optional;
  bool parsed;
  int n_keywords;
  const char *keywords[MAX_KEYWORDS];
} atom_field;

atom_field atom_field_id = {
  .field_type = dump_atom_field_id,
  .optional = false,
  .parsed = false,
  .n_keywords = 1,
  .keywords = {
    "id"
  }
};

atom_field atom_field_type = {
  .field_type = dump_atom_field_type,
  .optional = false,
  .parsed = false,
  .n_keywords = 1,
  .keywords = {
    "type"
  }
};

atom_field atom_field_x = {
  .field_type = dump_atom_field_x,
  .optional = false,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "x",
    "xu"
  }
};

atom_field atom_field_y = {
  .field_type = dump_atom_field_y,
  .optional = false,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "y",
    "yu"
  }
};

atom_field atom_field_z = {
  .field_type = dump_atom_field_z,
  .optional = false,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "z",
    "zu"
  }
};

atom_field atom_field_qw = {
  .field_type = dump_atom_field_qw,
  .optional = false,
  .parsed = false,
  .n_keywords = 3,
  .keywords = {
    "qw",
    "quatw",
    "c_q[1]"
  }
};

atom_field atom_field_qx = {
  .field_type = dump_atom_field_qx,
  .optional = false,
  .parsed = false,
  .n_keywords = 3,
  .keywords = {
    "qx",
    "quatx",
    "c_q[2]"
  }
};

atom_field atom_field_qy = {
  .field_type = dump_atom_field_qy,
  .optional = false,
  .parsed = false,
  .n_keywords = 3,
  .keywords = {
    "qy",
    "quaty",
    "c_q[3]"
  }
};

atom_field atom_field_qz = {
  .field_type = dump_atom_field_qz,
  .optional = false,
  .parsed = false,
  .n_keywords = 3,
  .keywords = {
    "qz",
    "quatz",
    "c_q[4]"
  }
};

atom_field atom_field_shapex = {
  .field_type = dump_atom_field_shapex,
  .optional = true,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "c_shape[1]",
    "shapex"
  }
};

atom_field atom_field_shapey = {
  .field_type = dump_atom_field_shapey,
  .optional = true,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "c_shape[2]",
    "shapey"
  }
};

atom_field atom_field_shapez = {
  .field_type = dump_atom_field_shapez,
  .optional = true,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "c_shape[3]",
    "shapez"
  }
};

atom_field atom_field_vx = {
  .field_type = dump_atom_field_vx,
  .optional = true,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "c_v[1]",
    "vx"
  }
};

atom_field atom_field_vy = {
  .field_type = dump_atom_field_y,
  .optional = true,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "c_v[2]",
    "vy"
  }
};

atom_field atom_field_vz = {
  .field_type = dump_atom_field_vz,
  .optional = true,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "c_v[3]",
    "vz"
  }
};

atom_field atom_field_angmomx = {
  .field_type = dump_atom_field_angmomx,
  .optional = true,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "c_angmom[1]",
    "angmomx"
  }
};

atom_field atom_field_angmomy = {
  .field_type = dump_atom_field_y,
  .optional = true,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "c_angmom[2]",
    "angmomy"
  }
};

atom_field atom_field_angmomz = {
  .field_type = dump_atom_field_angmomz,
  .optional = true,
  .parsed = false,
  .n_keywords = 2,
  .keywords = {
    "c_angmom[3]",
    "angmomz"
  }
};

atom_field atom_field_mol = {
  .field_type = dump_atom_field_mol,
  .optional = false,
  .parsed = false,
  .n_keywords = 1,
  .keywords = {
    "mol"
  }
};

atom_field *atom_fields[] = {
  &atom_field_id,
  &atom_field_type,
  &atom_field_x,
  &atom_field_y,
  &atom_field_z,
  &atom_field_qw,
  &atom_field_qx,
  &atom_field_qy,
  &atom_field_qz,
  &atom_field_shapex,
  &atom_field_shapey,
  &atom_field_shapez,
  &atom_field_vx,
  &atom_field_vy,
  &atom_field_vz,
  &atom_field_angmomx,
  &atom_field_angmomy,
  &atom_field_angmomz,
  &atom_field_mol
};

typedef struct section {
  char const *header;
  int nfields;
  char const *name;
  int *indices;
} section;

#define section_is(section, name)						    \
  (strcmp(section->name, target) == 0)

section section_timestep = {
  .header = "ITEM: TIMESTEP",
  .nfields = 1,
  .name = "timestep"
};

section section_natoms = {
  .header = "ITEM: NUMBER OF ATOMS",
  .nfields = 1,
  .name = "natoms"
};

section section_bounds = {
  .header = "ITEM: BOX BOUNDS",
  .nfields = 2,
  .name = "bounds"
};

section section_atoms = {
  .header = "ITEM: ATOMS",
  .nfields = -1,
  .name = "atoms",
  // .indices = (int[]){-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int *
section_atoms_generic_parse(char const* line) {
    // printf("LINE: %s of %i\n", line, dump_atom_field_END);

    int *indices = calloc(dump_atom_field_END, sizeof(int));
    for (int i = 0; i < dump_atom_field_END; i++) {
      indices[i] = -1;
    }

    int field_count = 0;
    int parsed_fields = 0;

    token_iter(line,
	       " ",
	       tok,
               // printf("DEBUG %2i <%s>\n", ntok, tok);
               for (size_t i=0; i<sizeof(atom_fields)/sizeof(atom_field*); ++i) {
                 atom_field *field = atom_fields[i];
                 for (int j = 0; j<field->n_keywords; ++j) {
                   if (strcmp(tok, field->keywords[j]) == 0) {
                     indices[field->field_type] = field_count-2;
                     // printf("cmp %s %s set %i %i\n", field->keywords[j], tok, field->field_type, indices[field->field_type]);
                     parsed_fields++;
                     field->parsed = true;
                   }
                 }
               }
               field_count++;
      );

    section_atoms.nfields = parsed_fields;

    for (size_t i=0; i<sizeof(atom_fields)/sizeof(atom_field*); ++i) {
      atom_field *field = atom_fields[i];

      if (!field->optional && !field->parsed) {
        fprintf(stderr, "ERROR: a field with id ");

        for (int j=0; j<field->n_keywords; ++j) {
          fprintf(stderr, "%s",field->keywords[j]);

          if (j < field->n_keywords-1) {
            fprintf(stderr, " or ");
          }
        }

        fprintf(stderr, " is supposed to be present\n");

        exit(1);
      }
    }

    return indices;
}

typedef struct dump_parse_ctxt {
  bool parsing_timestep;
  bool parsing_natoms;
  bool parsing_bounds;
  bool parsing_atoms;
  bool parsing_atoms_novel;
  int  parsing_bounds_count;
  int  parsing_natoms_count;
  bool parsed_natoms;
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

void
particle_transform_on_the_fly(dump_parse_ctxt *ctxt,
			      fragment *frag,
			      bool dump_xyz)
{
  char *pdb_fmt = "ATOM %6i %-4s %-4s%1s%4i    %8.3f%8.3f%8.3f%6.2f%6.2f          %-2s\n";
  char *long_pdb_fmt = "ATOM %6i %-4s %-4s%1s%4i    %8.3f%8.3f%8.3f%6.2f%6.2f          %-2s\n";
  char *fmt = NULL;
  if (frag->natoms > 100000)
    fmt = long_pdb_fmt;
  else
    fmt = pdb_fmt;

  double mat[3][3];
  quat_to_mat(ctxt->p->quat, mat);
  
  //print_mat(mat);
  /* double matrev[3][3]; */
  /* quat_to_mat_trans(ctxt->p->quat, matrev); */
  /* print_mat(matrev); */

  for (int i=0; i<frag->natoms; ++i) {
    atom a = frag->atoms[i];
    atom r = rotate(a, mat);
    atom t = translate(r, ctxt->p->pos);
    
    ctxt->natoms++;
    
    if (dump_xyz) {
      fprintf(ctxt->out_file, "%s %f %f %f\n",
	      t.name,
	      t.pos[0],
	      t.pos[1],
	      t.pos[2]);
    } else {
      
      // do not keeps markers
      char *end_name_x = strchr(t.name, '*');
      char *end_name_y = strchr(t.name, '+');
      char *end_name_z = strchr(t.name, '/');

      if (end_name_x)
	*end_name_x = '\0';
      else if (end_name_y)
	*end_name_y = '\0';
      else if (end_name_z)
	*end_name_z = '\0';
      else
	t.name[strlen(t.name)] = '\0';

      char const* chain_id = " ";

      char const* atom_type = atom_name_strip(t.name);

      fprintf(ctxt->out_file,
	      fmt, //"ATOM %6i %-4s %-4s%1s%4i    %8.3f%8.3f%8.3f%6.2f%6.2f          %-2s\n",
	      //"ATOM %6i %-4s %-4s%1s%4i    %8.3f%8.3f%8.3f%6.2f%6.2f%9s\n",
	      //"ATOM %6i  %-4s%-3s%5i    %8.3f%8.3f%8.3f  %3.2f  %3.2f           %c\n",
	      ctxt->natoms,
	      t.name,
	      frag->name,
	      chain_id,
	      ctxt->p->mol,
	      t.pos[0],
	      t.pos[1],
	      t.pos[2],
	      0.0,
	      0.0,
	      atom_type);
    }
  }
}

int
particle_transform(FILE *out_file,
		   int atom_index,
		   int frag_index,
		   particle* p,
		   fragments *fragments)
{
  char *pdb_fmt      = "ATOM  %5i %-4s %-.3s%1s%5i    %8.3f%8.3f%8.3f%6.2f%6.2f  %10s\n";
  char *long_pdb_fmt = "ATOM  %5x %-4s %-.3s%1s%5i    %8.3f%8.3f%8.3f%6.2f%6.2f  %10s\n";

  fragment *frag = &fragments->fragments[frag_index];
  
  double mat[3][3];
  quat_to_mat(p->quat, mat);

  int current_atom = atom_index;
  
  // atomistic particles
  for (int i=0; i<frag->natoms; ++i) {
    atom a = frag->atoms[i];
    atom r = rotate(a, mat);
    atom t = translate(r, p->pos);

    // do not keeps markers
    char *atom_name = atom_name_strip_markers(t.name);
    char const* chain_id = " ";
    char *atom_type = atom_name_strip(t.name);
    
    char *fmt = NULL;
    if (current_atom > 99999) //  100000
      fmt = long_pdb_fmt;
    else
      fmt = pdb_fmt;
    
    fprintf(out_file,
	    fmt,
	    current_atom++,
	    atom_name,
	    frag->name,
	    chain_id,
	    p->mol,
	    t.pos[0],
	    t.pos[1],
	    t.pos[2],
	    0.0,
	    0.0,
	    atom_type);

    free(atom_name);
    free(atom_type);
  }
  
  return current_atom;
}

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

particle *
parse_dump_line(dump_parse_ctxt *ctxt,
		bool flush)
{
  ctxt->p = calloc(1, sizeof(particle));

  // sorted: flush end of file
  if ( ((ctxt->out_file && ctxt->parsed_natoms) &&
	(ctxt->parsing_timestep	|| flush))) {

    int frag_counts = ctxt->ntypes*ctxt->nmols;

    ctxt->last_atom_index = 1;

    if (ctxt->frag_count)
      free(ctxt->frag_count);

    ctxt->frag_count = calloc(frag_counts, sizeof(int));

    // CG particles
    for (int i=0; i<ctxt->natoms; ++i) {
      particle p = ctxt->particles[i];
      int atom_type = p.type-1;
      int mol_index = p.mol-1;
      struct fragments *fragments = ctxt->fragments[atom_type];
      int frag_index = ctxt->ntypes*mol_index + atom_type;

      assert(frag_index < frag_counts);

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

  if (ctxt->parsing_timestep) {
    // printf("parsing_timestep\n");

    if (ctxt->out_file) {
      /* if (dump_xyz) */
      /* 	fprintf(ctxt->out_file, "%i\n", ctxt->natoms); */
      fclose(ctxt->out_file);
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
    // printf("parsing_natoms from %s\n", ctxt->line);

    if (ctxt->parsing_natoms_count == 0) {
      ctxt->natoms = atoi(ctxt->line);
      ctxt->parsing_natoms = false;
      ctxt->parsed_natoms = true;
    }

    if (!ctxt->particles) {
      //printf("allocating %i particles\n", ctxt->natoms);

      ctxt->particles = malloc(sizeof(particle)*ctxt->natoms);
      ctxt->particles_allocated = true;
    }

    ctxt->parsing_natoms_count++;
  } else if ((ctxt->parsed_natoms) && (!ctxt->particles_allocated)) {
    // printf("parsed_natoms not allocated\n");
    if (!ctxt->particles) {
      //printf("allocating %i particles\n", ctxt->natoms);

      ctxt->particles = malloc(sizeof(particle)*ctxt->natoms);
    }

    if (!ctxt->particles) {
      fprintf(stderr, "ERROR allocating %i particles\n", ctxt->natoms);
      exit(1);
    }

    ctxt->particles_allocated = true;
  } else if (ctxt->parsing_bounds) {
    // printf("parsing bounds\n");
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
    // printf("parsing_natoms from %s\n", ctxt->line);

    int ntok = 0;
    char *tokens[dump_atom_field_END];

    token_iter(ctxt->line,
	       " ",
	       tok,
               // printf("DEBUG %2i %s\n", ntok, tok);
               if (tok) tokens[ntok++] = strdup(tok);
      );

    if (ntok != section_atoms.nfields) {
      // fprintf(stderr, "n %i instead of %i REPARSE line %i : %s\n",
      //               ntok, section_atoms.nfields, ctxt->linen, ctxt->line);
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
    // for (int i=0; i<dump_atom_field_END; ++i)
    //   free(tokens[i]);

    ctxt->particles[ctxt->p->atomID-1] = *ctxt->p;
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
    int *indices = section_atoms_generic_parse(ctxt->line);
    section_atoms.indices = indices;

    // for (int i = 0; i < dump_atom_field_END; i++) {
    //   printf("indices %i %i \n", i, indices[i]);
    // }

    ctxt->parsing_atoms = true;
  }
#undef match_header
#undef match_header_debug

  return ctxt->p;
}

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
