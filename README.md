# Meson Template
The project serves as a pre-made template for CLI utility development. It's 
configured to use werror by default for robust code, and generate useful unit
tests that run through both Valgrind and fsanitize to help catch memory bugs and
undefined behavior.

## License
Although this would appear to be a GPL 2.0 project, it's more of a template for
GPL 2.0 projects. I hereby release this template in the public domain.

## Getting Started
You'll need to adjust parts of the build system to get started and as you add
files. You might want to remove my weird opinionated subprojects as well.

#### `./meson.build`
The first place to look is the top-level `meson.build`. You'll want to change
the project name from `'template'` and possibly `'c'` to another language, as
well a adjusting the version field and possibly the license. Next adjust the
email and description fields.

#### `./makefile`
As you add or remove subproject dependencies, you should update the `clean-full`
target so that a current list of subproject directories gets removed by the
target. Also update `.gitignore`.

#### `./.gitignore`
Keep this file current with any subproject directories so they aren't getting
committed.

#### `./AUTHORS ./LICENSE ./README.md`
These are self explanatory. Just don't forget to edit these to suit your 
project.

#### `./source/meson.build`
If you add dependencies or source files to your project, add them to the
`executable()` call here.

#### `./source/args.c` and `./include/args.h`
You can add command line option to your program by adding them to the `options`
struct in `args.c`. Then you'll want to add a case inside `parse_opt` so that
the option can affect the program in some way. You'll probably want to add some
data to the `argdata` struct in `args.h` which will be used for the option to have
its effect. The option `verbose` has already been added as an example, but it
won't hurt to read the [argp
documentation](https://www.gnu.org/software/libc/manual/html_node/Argp.html).

#### `./tests/meson.build`
This build file will auto generate a bunch of unit tests compiled in different
ways based on the contents of the `tests` variable. Whenever you create a new
unit test source file, just add it to `tests` according to the comments and
example above `tests`.

## Makefile targets
This template uses both the Meson and Make build systems, but really the
makefile is more of collection of scripts that use Meson to actually do all the
hard work. It just makes the commands shorter when working with the project.

#### make or make compile
Plain `make` or `make compile` which is the default target, simply builds the
project. It produces an unoptimized debug build with debug symbols in the final
binaries. Uses `build` as the build directory.

#### make install
This compiles an optimized release build of the project and installs it. Uses
`release` as the build directory.

#### make uninstall
Uninstalls the project. Relies on the ninja back end to meson, as there is no
`meson uninstall` command to match the `meson install` command. This might make
this target less portable.

#### make fsan
Builds the project using `-fsanitize=address,undefined`. This adds runtime
checks for memory safety issues and undefined behavior. It shouldn't be used
with Valgrind. Uses `asan` as the
build directory.

#### make test
Runs all unit tests. Run plain `make` if the tests aren't already compiled. You
can run specific tests or suites by setting a variable called `ARGS` in your
make command. 

For example to run all tests with the address sanitizer:  
`make test ARGS="--suite asan"`

Running a single test:  
`make test ARGS="foo"`  
`make test ARGS="foo_O3"`

This project will automatically create not just your suites defined in
`./tests/meson.build -> tests` but also suites O0, O1, O2, O3, and asan. In
addition, suites are generated that combine these names with suites you defined.
If you define suite `foo`, the suite `foo_asan` and `foo_O2` are just two more
valid suite names. The same suffixes are applied to test names too.

The `ARGS` variable is available in other targets to pass arguments to meson but
I haven't found a use for it yet.

#### make clean
Removes all build directories.

#### make clean-full
Removes all build and subproject directories. You'll need to keep this target up
to date when subprojects are added.

#### make format
This will format all code in the project with clang-format according to the
rules in the file `.clangformat`.
 
 ---
 #### Targets that make build directories
 make build  
 make release  
 make asan  

