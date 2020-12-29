#ifndef	ATOM_H_
#define	ATOM_H_

typedef struct atom {
  double pos[3];
  char *name;
} atom;

// strip atom markers for CG axes
char*
atom_name_strip_markers(char const* name)
{
  char *stripped = strdup(name);

  // do not keeps markers
  char *end_name_x = strchr(stripped, '*');
  char *end_name_y = strchr(stripped, '+');
  char *end_name_z = strchr(stripped, '/');

  if (end_name_x)
    *end_name_x = '\0';
  else if (end_name_y)
    *end_name_y = '\0';
  else if (end_name_z)
    *end_name_z = '\0';
  else
    stripped[strlen(stripped)] = '\0';

  return stripped;
}

// last pdb field - strip every char not letters 
char*
atom_name_strip(char const* name)
{
  char* stripped = strdup(name);

  int charn = 0;
  int cursor = 0;

  char c;
  while ((c = stripped[charn++]) != '\0') {
    if (isalpha(c)) {
      stripped[cursor++] = c;
    }
  }

  stripped[cursor] = '\0';

  return stripped;
}

void
invert_pos(double p[3])
{
  p[0] *= -1.0;
  p[1] *= -1.0;
  p[2] *= -1.0;
}

atom
translate(atom a, double t[3])
{
  atom r = a;

  r.pos[0] = a.pos[0] + t[0];
  r.pos[1] = a.pos[1] + t[1];
  r.pos[2] = a.pos[2] + t[2];

  return r;
}

atom
rotate(atom a, double m[3][3])
{
  atom rotated = a;

  rotated.pos[0] =
    m[0][0]*a.pos[0]+
    m[0][1]*a.pos[1]+
    m[0][2]*a.pos[2];

  rotated.pos[1] =
    m[1][0]*a.pos[0]+
    m[1][1]*a.pos[1]+
    m[1][2]*a.pos[2];

  rotated.pos[2] =
    m[2][0]*a.pos[0]+
    m[2][1]*a.pos[1]+
    m[2][2]*a.pos[2];

  return rotated;
}
  
#endif	    /* !ATOM_H_ */
