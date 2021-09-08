// SPDX-License-Identifier: GPL-2.0-only
// Full license at https://spdx.org/licenses/GPL-2.0.html

#include "types.h"
#include <argp.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-variable"

extern struct argp argp;

typedef struct argdata {
        bool verbose;
} argdata;
