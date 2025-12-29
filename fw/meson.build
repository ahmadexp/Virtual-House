# Framework library build configuration

# Platform detection
host_system = host_machine.system()

# Common source files
common_sources = files(
  'src/FWApplication.cpp',
  'src/FWCamera.cpp',
  'src/FWDebugConsole.cpp',
  'src/FWDebugFont.cpp',
  'src/FWDebugFontRenderer.cpp',
  'src/FWDisplayInfo.cpp',
  'src/FWInput.cpp',
  'src/FWNullApplication.cpp',
  'src/FWNullWindow.cpp',
  'src/FWNullDebugFontRenderer.cpp',
  'src/FWWindow.cpp',
  'src/psgl/FWGLApplication.cpp',
  'src/psgl/FWGLCamApplication.cpp',
  'src/psgl/FWGLCamControlApplication.cpp',
  'src/psgl/FWGLDebugFontRenderer.cpp',
  'src/psgl/FWGLExtensions.cpp',
  'src/psgl/FWGLGrid.cpp',
)

platform_sources = []
platform_deps = []
platform_includes = []

# Dependencies
thread_dep = dependency('threads')

# Platform-specific configuration
if host_system == 'darwin'
  # macOS - use system OpenGL (not XQuartz) for compatibility
  gl_dep = dependency('OpenGL', required: true)
  glu_dep = dependency('OpenGL', required: true)  # GLU is part of OpenGL framework on macOS
endif

if host_system == 'linux'
  gl_dep = dependency('gl', required: true)
  glu_dep = dependency('glu', required: true)  # Use system GLU
endif

if host_system == 'windows'
  # Windows uses native OpenGL and GLU
  gl_dep = dependency('gl', required: true)
  # On Windows, GLU is glu32.lib
  cc = meson.get_compiler('cpp')
  glu_dep = cc.find_library('glu32', required: true)
endif

base_deps = [gl_dep, thread_dep]
if glu_dep.found()
  base_deps += [glu_dep]
endif

# Windows-specific: Add glaux if available
if host_system == 'windows'
  cc = meson.get_compiler('cpp')
  glaux_dep = cc.find_library('glaux', required: false)
  if glaux_dep.found()
    base_deps += [glaux_dep]
  endif
endif

# Platform-specific sources and includes
# All platforms now use GLFW
platform_sources += files(
  'src/psgl/FWGLExtensions.cpp',  # Use PSGL version for basic GL extensions
  'src/glfw/FWGLFWInput.cpp',
  'src/glfw/FWGLFWMain.cpp',
  'src/glfw/FWGLFWGLWindow.cpp',
  'src/glfw/FWGLFWTime.cpp',
)
platform_includes += include_directories('include/glfw')

# GLFW dependency - fallback to subproject if not found on system
glfw_dep = dependency('glfw3', required: false, fallback: ['glfw', 'glfw_dep'])
if not glfw_dep.found()
  glfw_dep = dependency('glfw3', required: true)
endif
platform_deps += [glfw_dep]

# macOS-specific frameworks
if host_system == 'darwin'
  add_project_arguments('-framework', 'Cocoa', language: 'cpp')
  add_project_arguments('-framework', 'IOKit', language: 'cpp')
  add_project_arguments('-framework', 'CoreVideo', language: 'cpp')
endif

# Include directories
inc_dirs = include_directories(
  'include',
  'include/psgl',
  '../lib',
  '../lib/include',
)

all_includes = [inc_dirs] + platform_includes

# Build the framework library
fw_lib = static_library('framework',
  common_sources + platform_sources,
  include_directories: all_includes,
  dependencies: base_deps + platform_deps,
  install: false,
)

# Make the library available for the main project
fw_dep = declare_dependency(
  link_with: fw_lib,
  include_directories: all_includes,
  dependencies: base_deps + platform_deps,
)
