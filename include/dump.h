#ifndef	DUMP_H_
#define	DUMP_H_

#include <sys/types.h> // lseek
#include <unistd.h>    // lseek
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "particle.h"
#include "string_utils.h"
#include "fragment.h"
#include "quat_utils.h"
#include "file_utils.h"
#include "trie.h"

typedef enum {
  dump_atom_fields_id,
  dump_atom_fields_type,
  dump_atom_fields_x,
  dump_atom_fields_y,
  dump_atom_fields_z,
  dump_atom_fields_qw,
  dump_atom_fields_qx,
  dump_atom_fields_qy,
  dump_atom_fields_qz,
  dump_atom_fields_shapex,
  dump_atom_fields_shapey,
  dump_atom_fields_shapez,
  dump_atom_fields_vx,
  dump_atom_fields_vy,
  dump_atom_fields_vz,
  dump_atom_fields_angmomx,
  dump_atom_fields_angmomy,
  dump_atom_fields_angmomz,
  dump_atom_fields_mol,
  dump_atom_fields_END
} dump_atom_fields;

typedef struct section {
  char const *header;
  int nfields;
  char const *name;
  int *indices;
  struct trie *field_index_map;
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
  .header = "ITEM: ATOMS "
  "id type x y z c_q[1] c_q[2] c_q[3] c_q[4] "
  "c_shape[1] c_shape[2] c_shape[3] "
  "vx vy vz angmomx angmomy angmomz mol",
  .nfields = 9+3+7,
  .name = "atoms",
  .indices = (int[]) {
    [dump_atom_fields_id] = 0,
    [dump_atom_fields_type] = 1,
    [dump_atom_fields_x] = 2,
    [dump_atom_fields_y] = 3,
    [dump_atom_fields_z] = 4,
    [dump_atom_fields_qw] = 5,
    [dump_atom_fields_qx] = 6,
    [dump_atom_fields_qy] = 7,
    [dump_atom_fields_qz] = 8,
    [dump_atom_fields_shapex] = 9,
    [dump_atom_fields_shapey] = 10,
    [dump_atom_fields_shapez] = 11,
    [dump_atom_fields_vx] = 12,
    [dump_atom_fields_vy] = 13,
    [dump_atom_fields_vz] = 14,
    [dump_atom_fields_angmomx] = 15,
    [dump_atom_fields_angmomy] = 16,
    [dump_atom_fields_angmomz] = 17,
    [dump_atom_fields_mol] = 18
  }
};

section section_atoms_novel = {
  .header = "ITEM: ATOMS "
  "id type x y z c_q[1] c_q[2] c_q[3] c_q[4] "
  "c_shape[1] c_shape[2] c_shape[3] mol",
  .nfields = 9+4,
  .name = "atoms_novel",
  .indices = (int[]) {
    [dump_atom_fields_id] = 0,
    [dump_atom_fields_type] = 1,
    [dump_atom_fields_x] = 2,
    [dump_atom_fields_y] = 3,
    [dump_atom_fields_z] = 4,
    [dump_atom_fields_qw] = 5,
    [dump_atom_fields_qx] = 6,
    [dump_atom_fields_qy] = 7,
    [dump_atom_fields_qz] = 8,
    [dump_atom_fields_shapex] = 9,
    [dump_atom_fields_shapey] = 10,
    [dump_atom_fields_shapez] = 11,
    [dump_atom_fields_vx] = -1,
    [dump_atom_fields_vy] = -1,
    [dump_atom_fields_vz] = -1,
    [dump_atom_fields_angmomx] = -1,
    [dump_atom_fields_angmomy] = -1,
    [dump_atom_fields_angmomz] = -1,
    [dump_atom_fields_mol] = 12
  }
};

section section_atoms_novel_unwrap = {
  .header = "ITEM: ATOMS "
  "id type xu yu zu c_q[1] c_q[2] c_q[3] c_q[4] "
  "c_shape[1] c_shape[2] c_shape[3] mol",
  .nfields = 9+4,
  .name = "atoms_novel_unwrap",
  .indices = (int[]) {
    [dump_atom_fields_id] = 0,
    [dump_atom_fields_type] = 1,
    [dump_atom_fields_x] = 2,
    [dump_atom_fields_y] = 3,
    [dump_atom_fields_z] = 4,
    [dump_atom_fields_qw] = 5,
    [dump_atom_fields_qx] = 6,
    [dump_atom_fields_qy] = 7,
    [dump_atom_fields_qz] = 8,
    [dump_atom_fields_shapex] = 9,
    [dump_atom_fields_shapey] = 10,
    [dump_atom_fields_shapez] = 11,
    [dump_atom_fields_vx] = -1,
    [dump_atom_fields_vy] = -1,
    [dump_atom_fields_vz] = -1,
    [dump_atom_fields_angmomx] = -1,
    [dump_atom_fields_angmomy] = -1,
    [dump_atom_fields_angmomz] = -1,
    [dump_atom_fields_mol] = 12
  }
};

section section_atoms_unwrap = {
  .header = "ITEM: ATOMS "
  "id type xu yu zu c_q[1] c_q[2] c_q[3] c_q[4] "
  "c_shape[1] c_shape[2] c_shape[3] "
  "vx vy vz angmomx angmomy angmomz mol",
  .nfields = 9+3+7,
  .name = "atoms_unwrap",
  .indices = (int[]) {
    [dump_atom_fields_id] = 0,
    [dump_atom_fields_type] = 1,
    [dump_atom_fields_x] = 2,
    [dump_atom_fields_y] = 3,
    [dump_atom_fields_z] = 4,
    [dump_atom_fields_qw] = 5,
    [dump_atom_fields_qx] = 6,
    [dump_atom_fields_qy] = 7,
    [dump_atom_fields_qz] = 8,
    [dump_atom_fields_shapex] = 9,
    [dump_atom_fields_shapey] = 10,
    [dump_atom_fields_shapez] = 11,
    [dump_atom_fields_vx] = 12,
    [dump_atom_fields_vy] = 13,
    [dump_atom_fields_vz] = 14,
    [dump_atom_fields_angmomx] = 15,
    [dump_atom_fields_angmomy] = 16,
    [dump_atom_fields_angmomz] = 17,
    [dump_atom_fields_mol] = 18
  }
};

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
  section *section;
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
  } else if (ctxt->parsing_atoms || ctxt->parsing_atoms_novel) {
    int ntok = 0;
    char *tokens[dump_atom_fields_END];
    token_iter(ctxt->line,
    	       " ",
    	       tok,
	       tokens[ntok++] = strdup(tok);
      );
    
    if ((ntok != section_atoms.nfields)
	&& (ntok != section_atoms_novel.nfields)
	&& (ntok != section_atoms_novel_unwrap.nfields)
	&& (ntok != section_atoms_unwrap.nfields)) {
      /* fprintf(stderr, "n %i instead of %i REPARSE line %i : %s\n", */
      /* 	      ntok, section_atoms_novel.nfields, ctxt->linen, ctxt->line); */
      goto match_context;
    }
    
    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_type]],
		 ctxt->p->type,
		 fprintf(stderr, "reparsing %s|ctxt %i line %i\n",
			 ctxt->line,
			 dump_atom_fields_type,
			 ctxt->linen);
		 goto match_context;
      );
    
    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_x]],
		 ctxt->p->pos[0],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_x,
			ctxt->linen, ctxt->line);
		 goto match_context;
      );

    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_y]],
		 ctxt->p->pos[1],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_y,
			ctxt->linen, ctxt->line);
		 goto match_context;
      );

    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_z]],
		 ctxt->p->pos[2],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_z,
			ctxt->linen, ctxt->line);
		 exit(1);
      );

    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_qw]],
		 ctxt->p->quat[0],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_qw,
			ctxt->linen, ctxt->line);
		 exit(1);
      );
    
    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_qx]],
		 ctxt->p->quat[1],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_qx,
			ctxt->linen, ctxt->line);
		 exit(1);
      );
    
    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_qy]],
		 ctxt->p->quat[2],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_qy,
			ctxt->linen, ctxt->line);
		 exit(1);
      );
    
    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_qz]],
		 ctxt->p->quat[3],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_qz,
			ctxt->linen, ctxt->line);
		 exit(1);
      );

    if (!ctxt->parsing_atoms_novel) {
      parse_double(tokens[section_atoms.indices[dump_atom_fields_vx]],
		   ctxt->p->vel[0],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_vx,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);
    
      parse_double(tokens[section_atoms.indices[dump_atom_fields_vy]],
		   ctxt->p->vel[1],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_vy,
			  ctxt->linen, ctxt->line);
		   exit(1);
	);
    
      parse_double(tokens[section_atoms.indices[dump_atom_fields_vz]],
		   ctxt->p->vel[2],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_vz,
			  ctxt->linen, ctxt->line);
		   exit(1);
	);

      parse_double(tokens[section_atoms.indices[dump_atom_fields_angmomx]],
		   ctxt->p->angmom[0],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_angmomx,
			  ctxt->linen, ctxt->line);
		   exit(1);
	);
    
      parse_double(tokens[section_atoms.indices[dump_atom_fields_angmomy]],
		   ctxt->p->angmom[1],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_angmomy,
			  ctxt->linen, ctxt->line);
		   exit(1);
	);
    
      parse_double(tokens[section_atoms.indices[dump_atom_fields_angmomz]],
		   ctxt->p->angmom[2],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_angmomz,
			  ctxt->linen, ctxt->line);
		   exit(1);
	);

      parse_double(tokens[section_atoms.indices[dump_atom_fields_mol]],
		   ctxt->p->mol,
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_mol,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);
    } else {
      parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_mol]],
		   ctxt->p->mol,
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_mol,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);
    }      

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
  } else if (match_header(section_atoms.header)
	     || match_header(section_atoms_unwrap.header)) {
    ctxt->parsing_atoms = true;
  } else if (match_header(section_atoms_novel.header)
	     || match_header(section_atoms_novel_unwrap.header)) {	     
    ctxt->parsing_atoms_novel = true;
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
    //printf("parsing_timestep\n");
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
    //printf("parsing_natoms from %s\n", ctxt->line);

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
    //printf("parsed_natoms not allocated\n");
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
    //printf("parsing bounds\n");
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
  } else if (ctxt->parsing_atoms || ctxt->parsing_atoms_novel) {
    /* printf("parsing_atoms\n"); */
    int ntok = 0;
    char *tokens[dump_atom_fields_END]; 
    
    token_iter(ctxt->line,
	       " ",
	       tok,
	       /* printf("DEBUG %2i %s\n", ntok, tok); */
	       tokens[ntok++] = strdup(tok);
      );

    if ((ntok != section_atoms.nfields)
	&& (ntok != section_atoms_novel.nfields)
	&& (ntok != section_atoms_novel_unwrap.nfields)
	&& (ntok != section_atoms_unwrap.nfields)) {
      /* fprintf(stderr, "n %i instead of %i REPARSE line %i : %s\n", */
      /* 	      ntok, section_atoms_novel.nfields, ctxt->linen, ctxt->line); */
      goto match_context;
    }
    
    parse_int(tokens[section_atoms_novel.indices[dump_atom_fields_id]],
	      ctxt->p->atomID,
	      fprintf(stderr, "reparsing %s|ctxt %i line %i\n",
		      ctxt->line,
		      dump_atom_fields_type,
		      ctxt->linen);
	      goto match_context;
      );


    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_type]],
		 ctxt->p->type,
		 fprintf(stderr, "reparsing %s|ctxt %i line %i\n",
			 ctxt->line,
			 dump_atom_fields_type,
			 ctxt->linen);
		 goto match_context;
      );

    if (ctxt->p->type > ctxt->ntypes) {
      ctxt->ntypes = ctxt->p->type;
    }
      
    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_x]],
		 ctxt->p->pos[0],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_x,
			 ctxt->linen, ctxt->line);
		 goto match_context;
      );

    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_y]],
		 ctxt->p->pos[1],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_y,
			 ctxt->linen, ctxt->line);
		 goto match_context;
      );

    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_z]],
		 ctxt->p->pos[2],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_z,
			 ctxt->linen, ctxt->line);
		 exit(1);
      );

    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_qw]],
		 ctxt->p->quat[0],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_qw,
			 ctxt->linen, ctxt->line);
		 exit(1);
      );
    
    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_qx]],
		 ctxt->p->quat[1],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_qx,
			 ctxt->linen, ctxt->line);
		 exit(1);
      );
    
    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_qy]],
		 ctxt->p->quat[2],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_qy,
			 ctxt->linen, ctxt->line);
		 exit(1);
      );
    
    parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_qz]],
		 ctxt->p->quat[3],
		 fprintf(stderr, "ctxt %i in line %i:%s\n",
			 dump_atom_fields_qz,
			 ctxt->linen, ctxt->line);
		 exit(1);
      );

    if (!ctxt->parsing_atoms_novel) {
      parse_double(tokens[section_atoms.indices[dump_atom_fields_vx]],
		   ctxt->p->vel[0],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_vx,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);
    
      parse_double(tokens[section_atoms.indices[dump_atom_fields_vy]],
		   ctxt->p->vel[1],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_vy,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);
    
      parse_double(tokens[section_atoms.indices[dump_atom_fields_vz]],
		   ctxt->p->vel[2],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_vz,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);

      parse_double(tokens[section_atoms.indices[dump_atom_fields_angmomx]],
		   ctxt->p->angmom[0],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_angmomx,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);
    
      parse_double(tokens[section_atoms.indices[dump_atom_fields_angmomy]],
		   ctxt->p->angmom[1],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_angmomy,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);
    
      parse_double(tokens[section_atoms.indices[dump_atom_fields_angmomz]],
		   ctxt->p->angmom[2],
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_angmomz,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);

      parse_double(tokens[section_atoms.indices[dump_atom_fields_mol]],
		   ctxt->p->mol,
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_mol,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);

      if (ctxt->p->mol > ctxt->nmols) {
	ctxt->nmols = ctxt->p->mol;
      }
    } else {
      parse_double(tokens[section_atoms_novel.indices[dump_atom_fields_mol]],
		   ctxt->p->mol,
		   fprintf(stderr, "ctxt %i in line %i:%s\n",
			   dump_atom_fields_mol,
			   ctxt->linen, ctxt->line);
		   exit(1);
	);
    }      

    for (int i=0; i<dump_atom_fields_END; ++i)
      free(tokens[i]); 

    ctxt->particles[ctxt->p->atomID-1] = *ctxt->p;
  } else {
    //printf("NOP %s\n", ctxt->line);
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
  } else if (match_header(section_atoms.header)
	     || match_header(section_atoms_unwrap.header)) {
    ctxt->parsing_atoms = true;
  } else if (match_header(section_atoms_novel.header)
	     || match_header(section_atoms_novel_unwrap.header)) {	     
    ctxt->parsing_atoms_novel = true;
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
