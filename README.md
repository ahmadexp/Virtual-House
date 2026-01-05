# Virtual House

A 3D simulation environment built with C++ and OpenGL to study the cognitive spatial navigation ability of the player. This was part of my Ph.D. thesis. This project has been modernized to support cross-platform builds on macOS, Linux, and Windows using the Meson build system.

<img width="1278" height="746" alt="Screenshot 2025-12-25 at 7 41 56 PM" src="https://github.com/user-attachments/assets/e4e339f7-e844-4242-9ccf-f006ef602242" />

## Getting Started

### Prerequisites

| Platform | Dependencies | Install Command |
|----------|--------------|-----------------|
| **macOS** | `brew`, `meson`, `ninja`, `glfw`, `pkg-config` | `brew install meson ninja glfw Pkg-config` |
| **Linux** | `meson`, `ninja`, `glfw`, `pkg-config`, `libxrandr-dev`, `libxinerama-dev`, `libxcursor-dev`, `libxi-dev` | `sudo apt-get install meson ninja-build libx11-dev libgl1-mesa-dev pkg-config libglu1-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev` |
| **Windows**| `choco`, `meson`, `ninja`, `Visual Studio`, `pkgconfiglite` | `choco install meson ninja pkgconfiglite` |

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
- `/AUTOEXIT`: Automatically exit after reaching the goal.
- `/USEMOUSE`: Enable free-look camera with the mouse.
- `/SHOWPLAYER`: Show the player model (3rd person view).
- `/USEJOYSTICK`: Enable joystick input.
- `/TRIAL`: Allows to enter trial number.
- `/LATENCY`: Adds input latency.
- `/ALLOCENTRIC`: Enables 3rd person view where you can see the player.
- `/JOYANGVEL`: Sets Joystick rotation velocity.
- `/JOYTRANSVEL`: Sets joysticks traversion velocity.
- `/LANGUAGE n`: Sets language (1=English, 2=French, 3=Spanish, 4=German).
- `/INOUTRATIO`: In vs Out ratio.
- `/KIDMODE`: Kid-friendly mode (required for animal sounds).
- `/ANIMSOUND`: Play animal sound hints (requires `/KIDMODE`).
- `/PERPSTAIR n`: Set stair/ramp type (1-6: 1=stairs 180°, 2=stairs 90°, 3=ramp 180°, 4=ramp 90°, 5=double stairs, 6=double ramps).
- `/LOGTOTAL`: Logging everything.
- `/NOTEXTURE`: Avoid using texture.
- `/TURNDURATION`: Set turning about the house velocity.

Example:
```bash
./build/virtualhouse /USEMOUSE /NOINFO
```

📖 **For detailed usage guide with examples, see [USAGE.md](USAGE.md)**

## Running Batch file for experiments

for MacOS

```
./runmeEGO.command
```

for Linux

```
sh runmeEGO.sh
```

and for Windows

```
runmeEGO.bat
```

## Project Structure

- `src/`: Main application source code (`start.cpp`).
- `include/`: Header files for game logic and rendering.
- `fw/`: Cross-platform framework library (Input, Windowing, Math).
- `meson.build`: Build configuration.
- `Media/`: Game assets (textures, models).

## Known Issues

- **Legacy audio**: Audio playback uses system commands (`afplay` on macOS) rather than a dedicated audio library.
- It crashes after about 19 seconds on the Raspberry Pi (Raspbian) with "Segmentation Fault".

## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License (CC BY-NC 4.0).

You are free to:

Share — copy and redistribute the material in any medium or format
Adapt — remix, transform, and build upon the material
Under the following terms:

Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made.
NonCommercial — You may not use the material for commercial purposes.
For full details, see: https://creativecommons.org/licenses/by-nc/4.0/

As the project creator, I reserve the right to use this material commercially or under any other terms.
