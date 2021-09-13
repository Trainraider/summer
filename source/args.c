// SPDX-License-Identifier: GPL-2.0-only
// Full license at https://spdx.org/licenses/GPL-2.0.html

#include "args.h"
#include "threads.h"
#include "types.h"
#include <string.h>
#include <argp.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"

const char*               argp_program_version     = PROJNAME " " VERSION;
const char*               argp_program_bug_address = EMAIL;
static char               doc[]                    = DESCRIPTION;
static char               args_doc[]               = "[-t nthreads] num"; // usage string
static struct argp_option options[]
        = { { "threads", 't', "count", 0,
                    "Specify thread count, 0 for automatic", 0},
            { 0 } };

bool str_is_zeros(char* str){
        size_t len = strlen(str);
        for(size_t i = 0; i < len; i++){
                if (str[i] != '0') return false;
        }
        return true;
}

static error_t parse_opt(int key, char* arg, struct argp_state* state)
{
        argdata* data = state->input;
        S SZM nargs = 0;
        char* tailptr;
        switch (key) {
        case ARGP_KEY_INIT: 
                data->nthreads = nthreads();
                break;
        case ARGP_KEY_ARG:
                if (nargs >=1) argp_usage(state); 
                nargs++;
                data->sumto = strtoull(arg, &tailptr, 10);
                if ('\0' != tailptr[0]) argp_usage(state);
                break;
        case 't':;
                int nt = strtol(arg, &tailptr, 10);
                if ('\0' != tailptr[0]) argp_usage(state);
                if (0 != nt) data->nthreads = nt;
                break;
        case ARGP_KEY_ARGS: break;
        case ARGP_KEY_END: break;
        case ARGP_KEY_NO_ARGS: break;
        case ARGP_KEY_SUCCESS: break;
        case ARGP_KEY_ERROR: break;
        case ARGP_KEY_FINI: 
                if (nargs == 0) argp_usage(state);
                break;
        default: return ARGP_ERR_UNKNOWN;
        }
        return 0;
}

struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };
