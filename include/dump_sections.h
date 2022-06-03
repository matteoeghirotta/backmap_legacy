#ifndef	DUMP_SECTIONS_H
#define	DUMP_SECTIONS_H

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
               // printf("DEBUG %2i <%s>\n", field_count, tok);
               for (size_t i=0; i<sizeof(atom_fields)/sizeof(atom_field*); ++i) {
                 atom_field *field = atom_fields[i];
                 int j = 0;
                 do {
                 // for (int j = 0; j<field->n_keywords; ++j) {
                   // printf("debug %lu <%s> / %i\n", strlen(field->keywords[j]), field->keywords[j], field->n_keywords);
                   if (strncmp(tok, field->keywords[j], strlen(field->keywords[j])) == 0) {
                   // if (strncmp(tok, field->keywords[j], strlen(tok)) == 0) {
                     indices[field->field_type] = field_count-2;
                     // printf("cmp %s %s set %i %i %i\n",
                     //        field->keywords[j],
                     //        tok,
                     //        field->field_type,
                     //        indices[field->field_type],
                     //        parsed_fields);
                     parsed_fields++;
                     field->parsed = true;
                   }

                   j++;
                 } while(!field->parsed && j < field->n_keywords);
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

    // for (int i = 0; i < dump_atom_field_END; i++) {
    //   printf("Indices %i %i \n", i, indices[i]);
    // }

    return indices;
}

#endif	    /* !DUMP_SECTIONS_H */
