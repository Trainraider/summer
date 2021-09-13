// SPDX-License-Identifier: GPL-2.0-only
// Full license at https://spdx.org/licenses/GPL-2.0.html

#define _GNU_SOURCE

#include "threads.h"
#include "args.h"
#include <argp.h>
#include <inttypes.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct thjob {
        UI64M start;
        UI64M end;
        UI64M ret_sum;
        IM    t_no;
} thjob;

VM* sum_numbers(VM* arg)
{
        thjob* job = arg;

        UI64  start = job->start;
        UI64  end   = job->end;
        UI64M sum   = 0;

        for (UI64M i = start; i <= end; i++) {
                sum += i;
        }
        job->ret_sum = sum;
        return arg;
}

int main(int argc, char** argv)
{
        argdata data;
        argp_parse(&argp, argc, argv, 0, 0, &data);

        I              nt    = data.nthreads;
        UI64           sumto = data.sumto;
        pthread_t*     tid   = calloc(nt, sizeof(pthread_t));
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        UI64 jobsize = sumto / nt;
        UI64 jobrm   = sumto % nt;

        IM     err;
        thjob* job = calloc(nt, sizeof(thjob));
        for (IM i = 0; i < nt; i++) {
                job[i].t_no  = i;
                job[i].start = jobsize * i + 1;
                job[i].end   = jobsize * (i + 1);
                if (i == nt - 1)
                        job[i].end += jobrm;

                err = pthread_create(&tid[i], &attr, &sum_numbers, &job[i]);
                if (err != 0) {
                        fprintf(stderr, "Can't create thread %i :[%s]", i + 1,
                            strerror(err));
                        exit(1);
                }
        }
        UI64M  sum = 0;
        thjob* psum;
        for (IM i = 0; i < nt; i++) {
                pthread_join(tid[i], (VM**)&psum);
                sum += psum->ret_sum;
        }
        printf("Sum: %" PRIu64 "\n", sum);
        pthread_attr_destroy(&attr);

        free(job);
        free(tid);
        return 0;
}

IM nthreads()
{
        cpu_set_t cs;
        CPU_ZERO(&cs);
        sched_getaffinity(0, sizeof cs, &cs);
        return CPU_COUNT(&cs);
}
