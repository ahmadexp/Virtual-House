project('virtualhouse', 'cpp',
  version: '5.8',
  default_options: [
    'cpp_std=c++17',
    'warning_level=1',
    'optimization=2',  # Enable optimization to inline stream functions
  ]
)

host_system = host_machine.system()
app_deps = []
add_project_arguments('-DGL_SILENCE_DEPRECATION', language: 'cpp')
subdir('fw')
app_sources = files(
  'src/start.cpp',
  'include/sky/skybox.cpp',
  'include/gamespecific/ms3d/msModel.cpp',
  'include/gamespecific/ms3d/mathlib.cpp',
)

app_inc = include_directories(
  'include',
  'include/generic',
  'include/gamespecific',
  'include/sky',
)

executable('virtualhouse',
  app_sources,
  include_directories: app_inc,
  dependencies: [fw_dep] + app_deps,
  install: true,
  win_subsystem: 'console',  # Ensure console window on Windows for debugging
)

summary({
  'Platform': host_system,
  'Build type': get_option('buildtype'),
  'C++ Standard': get_option('cpp_std'),
}, section: 'Configuration')
