# SPDX-License-Identifier: GPL-2.0-only
# Full license at https://spdx.org/licenses/GPL-2.0.html

exe = executable(meson.project_name(), ['threads.c', 'args.c'],
  c_args : ['-DMAIN',
            '-DVERSION="v@0@"'.format(meson.project_version()),
            '-DPROJNAME="@0@"'.format(meson.project_name()),
            '-DEMAIL="@0@"'.format(email),
            '-DDESCRIPTION="@0@"'.format(description)],
  include_directories: include,
  dependencies: [types_dep, threads_dep],
  install : true)
