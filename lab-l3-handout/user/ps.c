// Create a zombie process that
// must be reparented at exit.

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
    uint16 proc_idx = 0;
    while (1)
    {
        struct user_proc *procs = ps(proc_idx, 2);

        if (procs == 0)
        {
            printf("SYSCALL FAILED");
            exit(-1);
        }

        for (int i = 0; i < 2; i++)
        {
            if (procs[i].state == UNUSED)
                exit(0);
            printf("%s (%d): %d\n", procs[i].name, procs[i].pid, procs[i].state);
        }
        proc_idx += 2;
    }
    exit(0);
}
