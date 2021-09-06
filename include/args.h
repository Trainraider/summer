// SPDX-License-Identifier: GPL-2.0-only

#include "types.h"
#include <argp.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-variable"

extern struct argp argp;

typedef struct argdata {
        bool verbose;
} argdata;
