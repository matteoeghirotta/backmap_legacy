#ifndef	DUMP_ATOM_FIELDS_H_
#define	DUMP_ATOM_FIELDS_H_

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
  .n_keywords = 4,
  .keywords = {
    "qw",
    "quatw",
    "c_q[1]",
    "c_orient[1]"
  }
};

atom_field atom_field_qx = {
  .field_type = dump_atom_field_qx,
  .optional = false,
  .parsed = false,
  .n_keywords = 5,
  .keywords = {
    "qx",
    "quatx",
    "quati",
    "c_q[2]",
    "c_orient[2]"
  }
};

atom_field atom_field_qy = {
  .field_type = dump_atom_field_qy,
  .optional = false,
  .parsed = false,
  .n_keywords = 5,
  .keywords = {
    "qy",
    "quaty",
    "quatj",
    "c_q[3]",
    "c_orient[3]"
  }
};

atom_field atom_field_qz = {
  .field_type = dump_atom_field_qz,
  .optional = false,
  .parsed = false,
  .n_keywords = 5,
  .keywords = {
    "qz",
    "quatz",
    "quatk",
    "c_q[4]",
    "c_orient[4]"
  }
};

atom_field atom_field_shapex = {
  .field_type = dump_atom_field_shapex,
  .optional = true,
  .parsed = false,
  .n_keywords = 4,
  .keywords = {
    "c_shape[1]",
    "shapex",
    "c_diameter[1]",
    "diameterx"
  }
};

atom_field atom_field_shapey = {
  .field_type = dump_atom_field_shapey,
  .optional = true,
  .parsed = false,
  .n_keywords = 4,
  .keywords = {
    "c_shape[2]",
    "shapey",
    "c_diameter[2]",
    "diametery"
  }
};

atom_field atom_field_shapez = {
  .field_type = dump_atom_field_shapez,
  .optional = true,
  .parsed = false,
  .n_keywords = 4,
  .keywords = {
    "c_shape[3]",
    "shapez",
    "c_diameter[3]",
    "diameterz"
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
  .field_type = dump_atom_field_vy,
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
  .field_type = dump_atom_field_angmomy,
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

#endif	    /* !DUMP_ATOM_FIELDS_H_ */
