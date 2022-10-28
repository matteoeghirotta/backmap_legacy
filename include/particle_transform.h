#ifndef	PARTICLE_TRANSFORM_H
#define	PARTICLE_TRANSFORM_H

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

  printf("FRAG %i %i\n", frag_index, atom_index);

  fragment *frag = &fragments->fragments[frag_index];

    printf(" %i\n", frag->natoms);
  double mat[3][3];
  quat_to_mat(p->quat, mat);

  int current_atom = atom_index;

  // atomistic particles
  for (int i=0; i<frag->natoms; ++i) {
    printf("tr %i/%i\n", i, frag->natoms);
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

#endif	    /* !PARTICLE_TRANSFORM_H */
