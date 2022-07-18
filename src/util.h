#pragma once

#ifndef PROGRAM_NAME
#define PROGRAM_NAME "util"
#endif

#define MAX(A, B)        ((A) > (B) ? (A) : (B))
#define MIN(A, B)        ((A) < (B) ? (A) : (B))
#define BETWEEN(X, A, B) ((A) <= (X) && (X) <= (B))
#define LENGTH(ARR)      ((int) (sizeof (ARR) / sizeof (ARR)[0]))

#ifdef DEBUG
#include <stdio.h>
#pragma GCC diagnostic ignored "-Wformat-extra-args"
#define LOGINFO(FMT, ...)                                               \
  fprintf(stderr,                                                       \
          "%s:%d:0: info: " FMT "\n", __FILE__, __LINE__, __VA_ARGS__)
#define LOGINFO_ARR(ARR, LEN, FMTHEAD, FMTBODY) \
  do {                                          \
    fprintf(stderr, (FMTHEAD));                 \
    for (int i=0; i<(LEN); i++) {               \
      fprintf(stderr, (FMTBODY), (ARR)[i]);     \
    }                                           \
    fprintf(stderr, "\n");                      \
  } while(0)
#else
#define LOGINFO(FMT, ...)
#define LOGINFO_ARR(ARR, LEN, FMTHEAD, FMTBODY)
#endif
