// SPDX-License-Identifier: GPL-2.0-only

#include "args.h"
#include "types.h"
#include <argp.h>

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"

const char*               argp_program_version     = PROJNAME " " VERSION;
const char*               argp_program_bug_address = EMAIL;
static char               doc[]                    = DESCRIPTION;
static char               args_doc[] = ""; // usage string
static struct argp_option options[]
    = { { "verbose", 'v', 0, 0, "Produce verbose output", 0 }, { 0 } };

static error_t parse_opt(int key, char* arg, struct argp_state* state)
{
        argdata* data = state->input;
        switch (key) {
        case ARGP_KEY_INIT: data->verbose = false; break;
        case ARGP_KEY_ARG: break;
        case ARGP_KEY_ARGS: break;
        case ARGP_KEY_END: break;
        case ARGP_KEY_NO_ARGS: break;
        case ARGP_KEY_SUCCESS: break;
        case ARGP_KEY_ERROR: break;
        case ARGP_KEY_FINI: break;
        case 'v': data->verbose = true; break;
        default: return ARGP_ERR_UNKNOWN;
        }
        return 0;
}

struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };
