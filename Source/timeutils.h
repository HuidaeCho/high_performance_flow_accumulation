#ifndef _TIMEUTILS_H_
#define _TIMEUTILS_H_

#ifdef _MSC_VER
#include <winsock2.h>
/* gettimeofday.c */
int gettimeofday(struct timeval*, struct timezone*);
#else
#include <sys/time.h>
#endif

/* timeval_diff.c */
long long timeval_diff(struct timeval *, struct timeval *, struct timeval *);

#endif
