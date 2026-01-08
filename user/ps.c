#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"

static char *states[] = {
  [0] "UNUSED",
  [1] "USED",
  [2] "SLEEP",
  [3] "RUNNABLE",
  [4] "RUNNING",
  [5] "ZOMBIE",
};

int
main(void)
{
  struct pstat ps;

  if (getpinfo(&ps) < 0) {
    printf("ps: getpinfo failed\n");
    exit(1);
  }

  printf("PID\tPPID\tSTATE\t\tSZ\tNAME\n");

  for (int i = 0; i < NPROC; i++) {
    if (ps.inuse[i] == 0)
      continue;

    int st = ps.state[i];
    char *s = (st >= 0 && st < (int)(sizeof(states)/sizeof(states[0])) && states[st])
                ? states[st]
                : "???";

    printf("%d\t%d\t%s\t%ld\t%s\n",
           ps.pid[i],
           ps.ppid[i],
           s,
           ps.sz[i],
           ps.name[i]);
  }

  exit(0);
}
