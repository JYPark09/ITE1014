#ifndef MML_DEFS_H
#define MML_DEFS_H

#define SUCCESS		0
#define FAIL		-1
#define ALLOC_ERROR -2

#define SUCCESSED(result) ((result) >= 0)
#define FAILED(result)	  ((result) < 0)

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) > (b)) ? (b) : (a))
#define cut_range(a, b) \
	min(max(a, b), a)

#define NEW(type, size) \
	(type *)malloc(size * sizeof(type))

#endif
