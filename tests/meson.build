# SPDX-License-Identifier: GPL-2.0-only

#source folder shorthand
s = '../source/'

# Each element in tests contains a name, sources list, dependency list, 
# c_args list, link_args list, suite name, and whether to expect failure.
# ['test', ['test.c', 's + main.c'], [luadep], ['-DTESTING'], [], 
#                                                            'fakesuite', false]

tests = []

valgrind = find_program('valgrind')

foreach t : tests
  exe = executable(t[0], t[1], include_directories: include, dependencies: t[2],
                   c_args: t[3], link_args: t[4])  
  test(t[0], valgrind, args : ['--error-exitcode=1', '--leak-check=full',
                               '-s', '--track-origins=yes', exe.full_path()],
                               should_fail : t[6],
                       suite : [t[5], ''.join([t[5], '_O0']), 'O0'])

  exe_O2 = executable(''.join([t[0], '_O2']), t[1], include_directories: include,
                   dependencies: t[2], c_args: t[3] + ['-O2'], link_args: t[4])  
  test(''.join([t[0],'_O2']), valgrind, args : ['--error-exitcode=1', 
                               '--leak-check=full', '-s', '--track-origins=yes', 
                               exe_O2.full_path()], should_fail : t[6],
                       suite : [t[5], ''.join([t[5], '_O2']), 'O2'])

  exe_O3 = executable(''.join([t[0], '_O3']), t[1], include_directories: include,
                   dependencies: t[2], c_args: t[3] + ['-O3'], link_args: t[4])  
  test(''.join([t[0],'_O3']), valgrind, args : ['--error-exitcode=1', 
                               '--leak-check=full', '-s', '--track-origins=yes', 
                               exe_O3.full_path()], should_fail : t[6],
                       suite : [t[5], ''.join([t[5], '_O3']), 'O3'])

  exe_f = executable(''.join([t[0], '_asan']), t[1], include_directories:
    include, dependencies: t[2], c_args: t[3] + ['-fsanitize=address,undefined'], 
    link_args: t[4] + ['-fsanitize=address,undefined'])
  test(''.join([t[0], '_asan']), exe_f, should_fail : t[6], 
                       suite : [t[5], ''.join([t[5], '_asan']), 'asan'])
endforeach
