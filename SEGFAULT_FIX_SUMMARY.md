# Linux Segmentation Fault Fix - Summary

## Problem
The application crashes with a segmentation fault after approximately 10 seconds on Linux.

## Root Causes Identified

### 1. **Critical Buffer Overflow in `loadbmp.h`** ✅ FIXED
**Location**: `/Users/ahmadbyagowi/git/Virtual-House/include/generic/loadbmp.h` line 69-70

**Original Code**:
```cpp
pPixels = new unsigned char[Width * Height * BitCount];  // WRONG!
fread(pPixels, BitCount, Width * Height, fp);            // WRONG!
```

**Problem**: 
- `BitCount` is bits per pixel (24 or 32), not bytes
- Line 69 allocated `Width * Height * 24` bytes for a 24-bit image (should be `Width * Height * 3`)
- This caused massive over-allocation and potential heap corruption
- Line 70 read data incorrectly

**Fix**: Changed to:
```cpp
int bytesPerPixel = BitCount / 8;
size_t imageSize = Width * Height * bytesPerPixel;
pPixels = new unsigned char[imageSize];
fread(pPixels, 1, imageSize, fp);
```

### 2. **Buffer Overflow in `loadtga.h`** ✅ FIXED
**Location**: `/Users/ahmadbyagowi/git/Virtual-House/include/generic/loadtga.h` line 42-43

**Original Code**:
```cpp
pPixels = new unsigned char[width * height * 4];
fread(pPixels, 4, width * height, fp);
```

**Problem**:
- Assumed all TGA files are 32-bit (4 bytes per pixel)
- No validation of file format or dimensions
- Could read wrong amount of data causing heap corruption

**Fix**: 
- Added proper validation for width, height, and bpp
- Read actual file data based on bpp (24 or 32 bit)
- Convert 24-bit BGR to 32-bit BGRA properly
- Added comprehensive error checking

### 3. **Critical Buffer Overflow in `drawtext()` function** ✅ FIXED
**Location**: `/Users/ahmadbyagowi/git/Virtual-House/include/generic/text.h` line 70

**Original Code**:
```cpp
glTexCoordPointer(2,GL_FLOAT,0,fonttexturecoords[text[a]-' ']);
```

**Problem**:
- `fonttexturecoords` is declared as `float fonttexturecoords[96][8]`
- Valid indices are 0-95 (characters from space ' ' to '~')
- If `text[a]` contains any character < 32 or > 127, this causes **out-of-bounds array access**
- This is likely the cause of the 10-second crash if text rendering happens periodically

**Fix**: Added bounds checking:
```cpp
int charIndex = text[a] - ' ';
if (charIndex < 0 || charIndex >= 96) {
    charIndex = 0; // Use space character as fallback
}
glTexCoordPointer(2,GL_FLOAT,0,fonttexturecoords[charIndex]);
```

### 4. **Potential Issue in `loadobj.h`** ⚠️ NEEDS INVESTIGATION
**Location**: `/Users/ahmadbyagowi/git/Virtual-House/include/generic/loadobj.h` lines 52-64

**Potential Problem**:
```cpp
loadedface[facecount][0] = atoi(strtok(temptext,"/"))-1;
```

If `strtok()` returns `NULL` (malformed OBJ file), then:
- `atoi(NULL)` causes undefined behavior
- The resulting index could be invalid
- Accessing `loadedvertex[invalid_index]` causes segmentation fault

**Recommendation**: Add NULL checks after each `strtok()` call.

## Changes Made

### Files Modified:
1. ✅ `include/generic/loadtga.h` - Complete rewrite with validation
2. ✅ `include/generic/loadbmp.h` - Fixed buffer allocation and reading
3. ✅ `include/generic/text.h` - Added bounds checking in `drawtext()`

### Key Improvements:
- **Validation**: All image dimensions and formats are now validated
- **Error Handling**: Proper error messages for debugging
- **Bounds Checking**: Prevents out-of-bounds array access
- **Debug Output**: Comprehensive logging to identify issues
- **Memory Safety**: Correct allocation sizes based on actual data

## Testing Recommendations

When you run on Linux, watch for:
1. Debug output showing which files are being loaded
2. Any error messages about invalid dimensions or formats
3. The exact point where the crash occurs (should be visible in debug output)

If the crash still occurs, the debug output will show:
- Which texture/model file is being loaded when it crashes
- The dimensions and format of that file
- Whether it's during loading or during rendering

## Next Steps

If the crash persists:
1. Run with the debug output and note the last message before crash
2. Check if any text strings contain non-printable characters
3. Validate all OBJ files for correct format
4. Consider adding NULL checks to `loadobj.h` as well
