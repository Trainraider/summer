# SPDX-License-Identifier: GPL-2.0-only

project('template', 'c',
  version : '0.0',
  license : 'GPL-2.0-only',
  default_options : ['warning_level=3',
                     'werror=true'])
email = '<trainraider7@gmail.com>'
description = 'Prints Hello world'
include = include_directories(['include'])

types_dep = dependency('types', fallback: ['types', 'types_dep'])
testing_dep = dependency('testing', fallback: ['testing', 'testing_dep'])

subdir('source')
subdir('tests')
