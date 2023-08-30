project(
  'asciichart',
  'cpp',
  default_options: [
    'cpp_std=c++17',
    'warning_level=3',
    'buildtype=debugoptimized',
  ],
  license: 'MIT',
  meson_version: '>=0.57.0',
  version: files('VERSION'),
)

subdir('include')
# Dependency Declaration
# Parent projects using this subproject will able to call
# asciichart_proj = subproject('asciichart')
# asciichart_dep = asciichart_proj.get_variable('asciichart_dep')
asciichart_dep = declare_dependency(include_directories: inc_dirs)

subdir('src')
