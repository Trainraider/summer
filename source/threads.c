// SPDX-License-Identifier: GPL-2.0-only
// Full license at https://spdx.org/licenses/GPL-2.0.html

#define _GNU_SOURCE

#include "args.h"
#include "threads.h"
#include <argp.h>
#include <sched.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct thjob {
        int     t_no;
        uint64_t start;
        uint64_t end;
} thjob;

void* sum_numbers(void* arg)
{
        thjob*    job = arg;
        pthread_t id  = pthread_self();

        uint64_t  start = job->start;
        uint64_t  end   = job->end;
        uint64_t* sum   = malloc(sizeof(int64_t));
        *sum           = 0;

        for (uint64_t i = start; i <= end; i++) {
                *sum += i;
        }
        return sum;
}

int main(int argc, char** argv)
{
        argdata data;
        argp_parse(&argp, argc, argv, 0, 0, &data);
        
        I nt = data.nthreads;
        uint64_t sumto = data.sumto;
        pthread_t* tid = malloc(nt * sizeof (pthread_t));
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        uint64_t jobsize = sumto / nt;
        uint64_t jobrm   = sumto % nt;

        int   err;
        thjob* job = malloc(nt * sizeof (thjob));
        for (int i = 0; i < nt; i++) {
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
        uint64_t  sum = 0;
        uint64_t* psum;
        for (int i = 0; i < nt; i++) {
                pthread_join(tid[i], (void**)&psum);
                sum += *psum;
                free(psum);
        }
        printf("Sum: %" PRIu64 "\n", sum);
        pthread_attr_destroy(&attr);

        free(job);
        free(tid);
        return 0;
}

int nthreads()
{
        cpu_set_t cs;
        CPU_ZERO(&cs);
        sched_getaffinity(0, sizeof cs, &cs);
        return CPU_COUNT(&cs);
}
