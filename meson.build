project('girara', 'c',
  version: '0.3.4',
  meson_version: '>=0.48',
  default_options: 'c_std=c11',
)

version = meson.project_version()
version_array = version.split('.')

# Rules for so_major and so_minor:
# Before a release perform the following checks against the last release:
# * If a function has been removed or the paramaters of a function have changed
#   bump SOMAJOR and set SOMINOR to 0.
# * If any of the exported datastructures have changed in a incompatible way
#   bump SOMAJOR and set SOMINOR to 0.
# * If a function has been added bump SOMINOR.
so_major = '3'
so_minor = '1'
so_version = '@0@.@1@'.format(so_major, so_minor)

conf_data = configuration_data()
conf_data.set('GVMAJOR', version_array[0])
conf_data.set('GVMINOR', version_array[1])
conf_data.set('GVREV', version_array[2])
conf_data.set('version', version)

cc = meson.get_compiler('c')

prefix = get_option('prefix')
localedir = get_option('localedir')

# required dependencies
libm = cc.find_library('m', required: false)
glib = dependency('glib-2.0', version: '>=2.50')
gtk3 = dependency('gtk+-3.0', version: '>=3.20')
pango = dependency('pango', version: '>=1.14')

build_dependencies = [libm, glib, gtk3, pango]
pc_requires = ['glib-2.0', 'gtk+-3.0']

# supported functions
has_getpwnam_r = cc.has_function('getpwnam_r', prefix: '#define _DEFAULT_SOURCE\n#include <sys/types.h>\n#include <pwd.h>')

# defines
defines = [
  '-DGETTEXT_PACKAGE="libgirara-gtk3-@0@"'.format(so_major),
  '-DLOCALEDIR="@0@"'.format(join_paths(prefix, localedir)),
  '-D_DEFAULT_SOURCE',
]

if has_getpwnam_r
  defines += ['-DHAVE_GETPWNAM_R']
endif

# compile flags
flags = [
  '-Wall',
  '-Wextra',
  '-pedantic',
  '-Wmissing-declarations',
  '-Werror=implicit-function-declaration',
  '-Werror=vla'
]
flags = cc.get_supported_arguments(flags)

# optional dependencies
pc_requires_private = ['pango']
libnotify = dependency('libnotify', version: '>=0.7.0', required: get_option('notify'))
jsonc = dependency('json-c', required: get_option('json'))

if libnotify.found()
  build_dependencies += libnotify
  defines += '-DWITH_LIBNOTIFY'
  pc_requires_private += 'libnotify'
endif

if jsonc.found()
  build_dependencies += jsonc
  defines += '-DWITH_JSON'
  pc_requires_private += 'json-c'
endif

# generate version header file
version_header = configure_file(
  input: 'girara/version.h.in',
  output: 'girara-version.h',
  configuration: conf_data
)
include_directories = [
  include_directories('.')
]

subdir('data')
subdir('po')

# source files
sources = files(
  'girara/callbacks.c',
  'girara/commands.c',
  'girara/completion.c',
  'girara/config.c',
  'girara/datastructures.c',
  'girara/entry.c',
  'girara/input-history-io.c',
  'girara/input-history.c',
  'girara/log.c',
  'girara/session.c',
  'girara/settings.c',
  'girara/shortcuts.c',
  'girara/statusbar.c',
  'girara/template.c',
  'girara/utils.c'
)
sources += girara_css

# header files to install
headers = files(
  'girara/callbacks.h',
  'girara/commands.h',
  'girara/completion.h',
  'girara/config.h',
  'girara/datastructures.h',
  'girara/entry.h',
  'girara/girara.h',
  'girara/input-history.h',
  'girara/log.h',
  'girara/macros.h',
  'girara/session.h',
  'girara/settings.h',
  'girara/shortcuts.h',
  'girara/statusbar.h',
  'girara/template.h',
  'girara/types.h',
  'girara/utils.h'
)
headers += version_header

# girara library
girara = library(
  'girara-gtk3',
  sources,
  dependencies: build_dependencies,
  version: so_version,
  install: true,
  include_directories: include_directories,
  c_args: defines + flags,
  gnu_symbol_visibility: 'hidden'
)
install_headers(headers, subdir: 'girara')

# pkg-config file
pkg = import('pkgconfig')
pkg.generate(
  name: 'girara-gtk3',
  description: 'User interface library',
  url: 'https://pwmt.org/projects/girara',
  version: version,
  libraries: girara,
  requires: pc_requires,
  requires_private: pc_requires_private,
)

girara_dependency = declare_dependency(link_with: girara, include_directories: include_directories)

subdir('doc')
subdir('tests')
