# Virtual House

A 3D simulation environment built with C++ and OpenGL. This project has been modernized to support cross-platform builds on macOS, Linux, and Windows using the Meson build system.

## Getting Started

### Prerequisites

| Platform | Dependencies | Install Command |
|----------|--------------|-----------------|
| **macOS** | `meson`, `ninja`, `glfw` | `brew install meson ninja glfw` |
| **Linux** | `meson`, `ninja`, `libx11-dev`, `libgl1-mesa-dev` | `sudo apt-get install meson ninja-build libx11-dev libgl1-mesa-dev` |
| **Windows**| `meson`, `ninja`, `Visual Studio` | `pip install meson ninja` |

### Building the Project

1.  **Configure the build:**
    ```bash
    meson setup build
    ```

2.  **Compile:**
    ```bash
    meson compile -C build
    ```

### Running the Application

To run the application, executing the binary from the project root:

```bash
./build/virtualhouse
```

**Common Flags:**
- `/NOINFO`: Hide the information overlay.
- `/TESTMODE`: Enable automated test mode.
- `/AUTOEXIT`: Automatically exit after the simulation completes.
- `/USEMOUSE`: Enable free-look camera with the mouse.
- `/AUTOEXIT`: Exits the game after reaching the goal.
- `/USEJOYSTICK`: Enable joystick input.
- `/TRIAL`: Allows to enter trial number.
- `/LATENCY`: Adds input latency.
- `/ALLOCENTRIC`: Enables 3rd person view where you can see the player.
- `/JOYANGVEL`: Sets Joystick rotation velocity.
- `/JOYTRANSVEL`: Sets joysticks traversion velocity.
- `/LANGUAGE`: Sets langugae.
- `/INOUTRATIO`: In vs Out ratio.
- `/KIDMODE`: Kid mode.
- `/ANIMSOUND`: Animal sound.
- `/PERPSTAIR`: Proper Stairs vs Ramp.
- `/LOGTOTAL`: Logging everything.
- `/NOTEXTURE`: Avoid using texture.
- `/TURNDURATION`: Set turning about the house velocity.

Example:
```bash
./build/virtualhouse /USEMOUSE /NOINFO
```

## 📁 Project Structure

- `src/`: Main application source code (`start.cpp`).
- `include/`: Header files for game logic and rendering.
- `fw/`: Cross-platform framework library (Input, Windowing, Math).
- `meson.build`: Build configuration.
- `Media/`: Game assets (textures, models).

## Known Issues

- **Legacy audio**: Audio playback uses system commands (`afplay` on macOS) rather than a dedicated audio library.
- **Cg Shaders**: NVIDIA Cg shader support is deprecated and may not function on all platforms.

## License

Original code based on open source samples.
Modifications for cross-platform support added 2025.
