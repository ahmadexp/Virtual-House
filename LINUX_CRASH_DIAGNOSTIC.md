# Linux Crash Diagnostic Guide

## Critical Information Needed

To diagnose the remaining crash, I need you to run the application on Linux and capture the following:

### 1. Run with Debug Output
```bash
cd /path/to/Virtual-House
./build/virtualhouse 2>&1 | tee crash_log.txt
```

This will capture all output (including errors) to both screen and `crash_log.txt`.

### 2. What to Look For

When it crashes, please provide:

1. **The last 50 lines before the crash** from `crash_log.txt`
2. **The exact error message** (e.g., "Segmentation fault (core dumped)")
3. **Timing**: Does it crash at exactly 10 seconds, or is it variable?

### 3. Run with GDB for Stack Trace

If possible, run with GDB to get a stack trace:

```bash
gdb ./build/virtualhouse
(gdb) run
# Wait for crash
(gdb) bt
# Copy the backtrace output
```

### 4. Run with Valgrind (if available)

This will show exactly where the memory error occurs:

```bash
valgrind --leak-check=full --track-origins=yes ./build/virtualhouse 2>&1 | tee valgrind_log.txt
```

Note: This will be VERY slow, but will pinpoint the exact line causing the crash.

## What I've Fixed So Far

1. ✅ **loadbmp.h** - Fixed massive buffer overflow (was allocating 8x too much memory)
2. ✅ **loadtga.h** - Added validation and proper format handling
3. ✅ **text.h drawtext()** - Added bounds checking for character array access
4. ✅ **text.h drawtext()** - Added safety checks for null texture and null text pointer

## Likely Remaining Issues

Based on the code analysis, the most likely remaining causes are:

### A. Invalid OBJ File Data
**File**: `include/generic/loadobj.h` lines 52-64

The code calls `atoi(strtok(...))` without checking if `strtok()` returns NULL.
If an OBJ file is malformed, this causes undefined behavior.

**To test**: Check if any `.obj` files in `Media/` are malformed or empty.

### B. sprintf Buffer Overflow
**File**: `include/drawhud.h` line 89

```cpp
char temptext[100];
sprintf(temptext,"%s%s,%s,%s","Log files: ",logfilename,logfilename_2,total_logfilename);
```

If the combined filename length exceeds 100 bytes, this overflows.

**To test**: Check the length of your log filenames.

### C. OpenGL State Corruption
The crash might be in OpenGL driver code, triggered by:
- Invalid texture ID
- Corrupted vertex data
- Invalid OpenGL state

### D. File I/O Issues
Check if any of these files are missing or corrupted:
- `Media/font.tga`
- Any `Media/worldtiles/*.bmp` or `*.tga` files
- Any `Media/worldtiles/*.obj` files

## Quick Tests

### Test 1: Check Media Files
```bash
ls -lh Media/font.tga
ls -lh Media/worldtiles/*.bmp | head
ls -lh Media/worldtiles/*.obj | head
```

### Test 2: Validate File Sizes
```bash
# Check for suspiciously small or large files
find Media -type f -size 0  # Empty files
find Media -type f -size +10M  # Very large files
```

### Test 3: Check for Non-ASCII in Text
The crash might be from non-ASCII characters in strings being rendered.

## Next Steps

Please provide:
1. The debug output (last 50 lines before crash)
2. GDB backtrace if possible
3. Valgrind output if available
4. List of files in `Media/` directory

This will help me pinpoint the exact cause of the crash.
