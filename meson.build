project('virtualhouse', 'cpp',
  version: '5.8',
  default_options: [
    'cpp_std=c++17',
    'warning_level=1',
    'optimization=2',  # Enable optimization to inline stream functions
  ]
)

# Platform-specific configuration
host_system = host_machine.system()

app_deps = []

if host_system == 'darwin'
  # macOS - silence OpenGL deprecation warnings
  add_project_arguments('-DGL_SILENCE_DEPRECATION', language: 'cpp')
  # Disable stack protector to avoid false positives with large static arrays
  add_project_arguments('-fno-stack-protector', language: 'cpp')
  
  # No X11/GLX needed - using native Cocoa
endif

# Build the framework library
subdir('fw')

# Main application source
app_sources = files(
  'src/start.cpp',
  'include/sky/skybox.cpp',  # Located in include dir due to original project structure
  'include/gamespecific/ms3d/msModel.cpp',
  'include/gamespecific/ms3d/mathlib.cpp',
)

# Include directories for the main application
app_inc = include_directories(
  'include',
  'include/generic',
  'include/gamespecific',
  'include/sky',
)

# Build the executable
executable('virtualhouse',
  app_sources,
  include_directories: app_inc,
  dependencies: [fw_dep] + app_deps,
  install: true,
)

# Create a summary
summary({
  'Platform': host_system,
  'Build type': get_option('buildtype'),
  'C++ Standard': get_option('cpp_std'),
}, section: 'Configuration')
