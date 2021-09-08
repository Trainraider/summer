// SPDX-License-Identifier: GPL-2.0-only
// Full license at https://spdx.org/licenses/GPL-2.0.html

#include "args.h"
#include "types.h"
#include <argp.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef MAIN
IM main(I argc, CHM* argv[])
{
        argdata data;
        argp_parse(&argp, argc, argv, 0, 0, &data);
        puts("Hello World");
        if (data.verbose) {
                puts("How do you do?");
        }
        return EXIT_SUCCESS;
}
#endif // MAIN
