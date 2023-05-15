# Project Declaration
project(
  'asciichart',
  'cpp',
  default_options: [
    'cpp_std=c++17',
    'warning_level=3'
  ],
  license: 'MIT',
  meson_version: '>=0.57.0',
  version: files('VERSION'),
)

incs = include_directories('include')

# Dependency Declaration
# Parent projects using this subproject will able to call
# asciichart_proj = subproject('asciichart')
# asciichart_dep = asciichart_proj.get_variable('asciichart_dep')
asciichart_dep = declare_dependency(
  include_directories: incs,
)

plotter = executable(
  'Plotter',
  ['src' / 'plotter' / 'plotter.cc'],
  include_directories: incs
)
