#ifndef	FILE_UTILS_H_
#define	FILE_UTILS_H_

#define open_file_assert(handle, name, mode)				     \
  FILE *handle = fopen(name, mode);					     \
  if (!handle) {							     \
    fprintf(stderr, "ERROR: cannot open %s\n", name);			     \
    exit(EXIT_FAILURE);							     \
  }									     \

#define seek_begin(handle, ...)						     \
  int fd = fileno(handle);						     \
  if (lseek(fd, 0, SEEK_SET) != -1) {					     \
    __VA_ARGS__;							     \
  } else {								     \
    fprintf(stderr, "ERROR in lseek\n");				     \
    exit(EXIT_FAILURE);							     \
  }

//#define cat_files(handle, ...)					     

#endif	    /* !FILE_UTILS_H_ */
