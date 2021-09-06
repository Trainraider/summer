# SPDX-License-Identifier: GPL-2.0-only

exe = executable(meson.project_name(), ['main.c', 'args.c'],
  c_args : ['-DMAIN',
            '-DVERSION="v@0@"'.format(meson.project_version()),
            '-DPROJNAME="@0@"'.format(meson.project_name()),
            '-DEMAIL="@0@"'.format(email),
            '-DDESCRIPTION="@0@"'.format(description)],
  include_directories: include,
  dependencies: [types_dep],
  install : true)
