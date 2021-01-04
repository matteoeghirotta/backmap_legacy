#ifndef	STRING_UTILS_H_
#define	STRING_UTILS_H_

#include <stdlib.h>
#include <errno.h>

#define parse_double(string, result, ...)				     \
  {									     \
    char *endptr;							     \
    errno = 0;								     \
    result = strtod(string, &endptr);					     \
    if (errno) {							     \
      fprintf(stderr, "couldn't parse %s: ", string);			     \
      perror("ERROR in strtod");					     \
      exit(1);								     \
    }									     \
    if (*endptr) {							     \
      fprintf(stderr, "couldn't parse (part of) <%s>: \"%s\" as double\n",   \
	      string, endptr);						     \
      __VA_ARGS__;							     \
    }									     \
  }									     \

#define parse_int(string, result, ...)					     \
  {									     \
    char *endptr;							     \
    errno = 0;								     \
    result = strtol(string, &endptr, 0);				     \
    if (errno) {							     \
      fprintf(stderr, "couldn't parse %s: ", string);			     \
      perror("ERROR in strtol");					     \
      exit(1);								     \
    }									     \
    if (*endptr) {							     \
      fprintf(stderr, "couldn't parse (part of) <%s>: \"%s\" as int\n",	     \
	      string, endptr);						     \
      __VA_ARGS__;							     \
    }									     \
  }									     \

#define token_iter_NODUP(token_string, delim, token, ...)		     \
  {									     \
    char *save_ptr = NULL;						     \
    printf("ITER %s\n", token_string);					     \
    char *token = strtok_r(token_string, delim, &save_ptr);		     \
									     \
    __VA_ARGS__;							     \
									     \
    while ((token = strtok_r(NULL, delim, &save_ptr))) {		     \
      __VA_ARGS__;							     \
    }									     \
    printf("DONE\n");							     \
  }									     \


#define token_iter(input_string, delim, token, ...)			     \
  {									     \
    char *save_ptr = NULL;						     \
    char *dup = strdup(input_string);					     \
    char *token = strtok_r(dup, delim, &save_ptr);			     \
									     \
    __VA_ARGS__;							     \
									     \
    while ((token = strtok_r(NULL, delim, &save_ptr))) {		     \
      __VA_ARGS__;							     \
    }									     \
    free(dup);								     \
  }									     \

#endif	    /* !STRING_UTILS_H_ */
