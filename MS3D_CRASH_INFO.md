# Linux Crash - MS3D Player Model

## Current Status

The crash is now happening when loading the player MS3D model file.

### Last Log Line
```
DEBUG: loadms3d() - loading 'Media/player.ms3d'
```

The crash happens immediately after this, which means it's crashing **inside** the `msModel::Load()` function.

## Possible Causes

1. **File doesn't exist** - Check if `Media/player.ms3d` exists on Linux
2. **File is corrupted** - The MS3D file might be corrupted or have wrong format
3. **Memory allocation issue** - The MS3D loader uses `std::vector::resize()` which could fail
4. **Linux-specific issue** - Endianness, struct packing, or other platform differences

## Quick Fix: Skip Player Model

Since the player model is optional for testing, you can temporarily skip it by commenting out the player loading in `include/setup.h` around line 328-350.

## Diagnostic Steps

### 1. Check if file exists on Linux:
```bash
ls -lh Media/player.ms3d
file Media/player.ms3d
```

### 2. Try without player model:
Comment out the player model loading in `setup.h` (lines 328-350) and see if the application starts.

### 3. Run with GDB to get exact crash location:
```bash
gdb ./build/virtualhouse
(gdb) run
# Wait for crash
(gdb) bt
```

This will show exactly which line in `msModel.cpp` is crashing.

## Files Fixed So Far

All these now properly handle missing files:
- ✅ `loadobj.h` - World tiles and entities
- ✅ `loadms3d.h` - Player model (with error checking)
- ✅ `loadbmp.h` - Textures
- ✅ `loadtga.h` - Textures
- ✅ `text.h` - Font rendering

## Next Steps

1. Check if `Media/player.ms3d` exists on Linux
2. If it doesn't exist, the application should skip it (my fix should handle this)
3. If it does exist, we need the GDB backtrace to see where exactly it's crashing in the MS3D loader

The MS3D loader is complex (795 lines) and uses many `fread()` calls. If the file is corrupted or has unexpected data, it could crash at any of those points.
