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
  glu_dep = dependency('glu', required: false)
endif

if host_system == 'windows'
  # Windows uses native OpenGL
  gl_dep = dependency('gl', required: true)
  glu_dep = dependency('glu', required: false)
endif

base_deps = [gl_dep, thread_dep]
if glu_dep.found()
  base_deps += [glu_dep]
endif

# Platform-specific sources and includes
if host_system == 'darwin'
  # macOS - use GLFW for native OpenGL windowing (pure C, no Objective-C)
  platform_sources += files(
    'src/psgl/FWGLExtensions.cpp',  # Use PSGL version for basic GL extensions
    'src/glfw/FWGLFWInput.cpp',
    'src/glfw/FWGLFWMain.cpp',
    'src/glfw/FWGLFWGLWindow.cpp',
    'src/glfw/FWGLFWTime.cpp',
  )
  platform_includes += include_directories('include/glfw')
  
  # GLFW dependency
  glfw_dep = dependency('glfw3', required: true)
  platform_deps += [glfw_dep]
  
  # macOS frameworks
  add_project_arguments('-framework', 'Cocoa', language: 'cpp')
  add_project_arguments('-framework', 'IOKit', language: 'cpp')
  add_project_arguments('-framework', 'CoreVideo', language: 'cpp')
  
elif host_system == 'linux'
  # Linux
  platform_sources += files(
    'src/linux/FWLinuxGLExtensions.cpp',
    'src/linux/FWLinuxInput.cpp',
    'src/linux/FWLinuxMain.cpp',
    'src/linux/FWLinuxTime.cpp',
    'src/linux/FWLinuxGLWindow.cpp',
  )
  platform_includes += include_directories('include/linux')
  
  x11_dep = dependency('x11', required: true)
  platform_deps += [x11_dep]
  
elif host_system == 'windows'
  # Windows
  platform_sources += files(
    'src/win32/FWWin32GLExtensions.cpp',
    'src/win32/FWWin32Input.cpp',
    'src/win32/FWWin32Main.cpp',
    'src/win32/FWWin32Time.cpp',
    'src/win32/FWWin32GLWindow.cpp',
  )
  platform_includes += include_directories('include/win32')
  
  # Windows doesn't need X11
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
