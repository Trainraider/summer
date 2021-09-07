# SPDX-License-Identifier: GPL-2.0-only

#source folder shorthand
s = '../source/'

# Each element in tests contains a name, sources list, dependency list, 
# c_args list, link_args list, suite name, and whether to expect failure.
# ['test', ['test.c', s + 'main.c'], [luadep], ['-DTESTING'], [], 
#                                                            'fakesuite', false]

tests = []

# Each list in builds contains a list where the first elements is some c_args and
# the 2nd is a list of link_args. 3rd element is whether valgrind is
# appropriate. Element 4: name suffix. Every test needs a unique name. Each 
# element of builds will create a seperate test build.
builds = [[['-O0'],[], true, ''],
          [['-O1'],[], true, 'O1'],
          [['-O2'],[], true, 'O2'],
          [['-O3'],[], true, 'O3'],
          [['-fsanitize=address,undefined'],['-fsanitize=address,undefined'],
            false, 'asan']]

# Test generation below usually won't need modified unless things just aren't
# building. You will probably want to modify the links_with option at some point
# anyway.

valgrind = find_program('valgrind', disabler: true)

foreach t : tests
  name_t    = t[0]
  sources_t = t[1]
  deps_t    = t[2]
  c_args_t  = t[3]
  l_args_t  = t[4]
  suite     = t[5]
  exp_fail  = t[6]
  foreach b : builds
    c_args_b     = b[0]
    l_args_b     = b[1]
    use_valgrind = b[2]
    suffix       = b[3]
    
    name_f   = name_t + '_' + suffix
    c_args_f = c_args_b + c_args_t
    l_args_f = l_args_b + l_args_t
    suite_f  = suite + '_' + suffix

    exe = executable(name_f, sources_t,
      include_directories: include,
      dependencies: deps_t,
      c_args: c_args_f,
      link_args: l_args_f,
      link_with: foo_lib,
      install: false)  

    if use_valgrind
      test(name_f,
        valgrind,
        args : ['--error-exitcode=1', '--leak-check=full', '-s', 
                '--track-origins=yes', exe.full_path()],
        should_fail : exp_fail,
        suite : [suite, suite_f, suffix])
    else
      test(name_f,
        exe,
        should_fail : exp_fail, 
        suite : [suite, suite_f, suffix])
    endif
  endforeach
endforeach
