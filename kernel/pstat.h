#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"
#include "types.h"

struct pstat {
  int inuse[NPROC];
  int pid[NPROC];
  int ppid[NPROC];
  int priority[NPROC];
  int state[NPROC];
  uint64 sz[NPROC];
  char name[NPROC][16];
};

#endif
