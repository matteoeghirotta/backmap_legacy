#ifndef	DUMP_SECTIONS_H
#define	DUMP_SECTIONS_H

#include "verbose.h"

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
section_atoms_generic_parse(char const* line, verbose_level verbose) {
    int *indices = calloc(dump_atom_field_END, sizeof(int));
    for (int i = 0; i < dump_atom_field_END; i++) {
      indices[i] = -1;
    }

    int field_count = 0;
    int parsed_fields = 0;
    size_t n_atom_fields = sizeof(atom_fields)/sizeof(atom_field*);
    bool parsed_token = false;

    token_iter(line,
	       " ",
	       tok,
               parsed_token = false;

               if (verbose >= TOP) {
                 printf("TOKEN %s n %i\n", tok, field_count);
               }

               size_t i = 0;

               do {
                 atom_field *field = atom_fields[i];
                 int j = 0;

                 do {
                   if (verbose >= TOP) {
                     printf("CMP %s wrt %s (%i) ? %i, parsed %i\n", tok, field->keywords[j], field->n_keywords, strcmp(tok, field->keywords[j]), parsed_fields);
                   }

                   if (strcmp(tok, field->keywords[j]) == 0) {
                     indices[field->field_type] = field_count-2;
                     parsed_fields++;
                     field->parsed = true;
                     parsed_token = true;
                   }

                   j++;
                 } while(!field->parsed && j < field->n_keywords);

                 i++;
               } while (!parsed_token && i<n_atom_fields);

               field_count++;
      );

    section_atoms.nfields = parsed_fields;

    printf("COUNTED ON LINE: %s of %i\n", line, dump_atom_field_END);
    printf("COUNTED FIELDS %i\n", parsed_fields);

    for (size_t i=0; i<n_atom_fields; ++i) {
      atom_field *field = atom_fields[i];

      if (!field->optional && !field->parsed) {
        printf("ERROR: a field with id ");

        for (int j=0; j<field->n_keywords; ++j) {
          printf("\"%s\"",field->keywords[j]);

          if (j < field->n_keywords-1) {
            printf(" or ");
          }
        }

        printf(" is supposed to be present\n");

        exit(1);
      }
    }

    // for (int i = 0; i < dump_atom_field_END; i++) {
    //   printf("Indices %i %i \n", i, indices[i]);
    // }

    // reset parsed atom_fields for next iteration
    for (size_t i=0; i<n_atom_fields; i++)
      atom_fields[i]->parsed = false;

    return indices;
}

#endif	    /* !DUMP_SECTIONS_H */
