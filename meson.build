project('posprintf', 'c',
  meson_version: '>=0.54.0')

posprintf = static_library('posprintf', 'posprintf.S')

posprintf_dep = declare_dependency(
  include_directories: ['include'],
  link_with: posprintf)

meson.override_dependency('posprintf', posprintf_dep)
