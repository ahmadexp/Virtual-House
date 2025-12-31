# Virtual House - Complete Usage Guide

This guide explains how to play Virtual House with all available options, written for users who just want to play without reading the source code.

## How to Run the Game

```bash
# Basic command structure
./build/virtualhouse [log_file] [/FLAG1] [/FLAG2 value] ...
```

## Understanding Flag Types

| Type | How to Use | Example |
|------|------------|---------|
| **Toggle** | Just add the flag (no value) | `/USEMOUSE` |
| **Value** | Flag + space + number | `/LANGUAGE 2` |

---

## 🎮 All Available Flags

### Toggle Flags (No Value Needed)

| Flag | Description | Default State |
|------|-------------|---------------|
| `/USEMOUSE` | Enable mouse to look around freely | OFF (keyboard only) |
| `/NOINFO` | Hide the on-screen information display | OFF (info visible) |
| `/SHOWPLAYER` | Show your character (3rd person view) | OFF (1st person) |
| `/ALLOCENTRIC` | Enable allocentric navigation mode | OFF |
| `/AUTOEXIT` | Auto-close game after reaching goal | OFF |
| `/USEJOYSTICK` | Enable gamepad/joystick control | OFF |
| `/TESTMODE` | Automated testing mode | OFF |
| `/KIDMODE` | Kid-friendly mode (required for animal sounds!) | OFF |
| `/ANIMSOUND` | Play animal sound hints (**requires /KIDMODE**) | OFF |
| `/NOTEXTURE` | Disable textures (wireframe look) | OFF (textures on) |

### Value Flags (Must Provide a Number)

| Flag | Description | Valid Values | Default |
|------|-------------|--------------|---------|
| `/LANGUAGE n` | Set display language | 1=English, 2=French, 3=Spanish, 4=German | 1 |
| `/TRIAL n` | Set experiment trial number | 1, 2, 3, 4, 5... | 1 |
| `/LATENCY n` | Add input delay (frames) | 0-1000 | 1 |
| `/PERPSTAIR n` | Set stair/ramp type | 1-6 (see table below) | 3 |
| `/TURNDURATION n` | Intro rotation duration (seconds) | Any number | 40 |
| `/JOYANGVEL n` | Joystick rotation speed | Any number | 2.36 |
| `/JOYTRANSVEL n` | Joystick movement speed | Any number | 0.1 |
| `/INOUTRATIO n` | Indoor/outdoor movement ratio | Any number | 1 |
| `/LOGTOTAL file` | Path for experiment log | Filename | total.txt |

### Stair Types for /PERPSTAIR

| Value | Description |
|-------|-------------|
| 1 | Stairs at 180° |
| 2 | Stairs at 90° |
| 3 | Ramp at 180° **(default)** |
| 4 | Ramp at 90° |
| 5 | Double stairs at 180° |
| 6 | Double ramps at 180° |

---

## 🎯 Ready-to-Use Command Examples

### For Casual Players

```bash
# Simple play with mouse look
./build/virtualhouse /USEMOUSE

# Clean view (no info overlay)
./build/virtualhouse /USEMOUSE /NOINFO

# Third-person view (see your character)
./build/virtualhouse /USEMOUSE /SHOWPLAYER

# Third-person with clean view
./build/virtualhouse /USEMOUSE /SHOWPLAYER /NOINFO
```

### With Different Languages

```bash
# English (default)
./build/virtualhouse /USEMOUSE

# French
./build/virtualhouse /USEMOUSE /LANGUAGE 2

# Spanish  
./build/virtualhouse /USEMOUSE /LANGUAGE 3

# German
./build/virtualhouse /USEMOUSE /LANGUAGE 4
```

### Kid Mode with Animal Sounds

```bash
# Kid mode with animal sounds (English)
./build/virtualhouse /USEMOUSE /KIDMODE /ANIMSOUND

# Kid mode with animal sounds (Spanish)
./build/virtualhouse /USEMOUSE /KIDMODE /ANIMSOUND /LANGUAGE 3

# Kid mode, animal sounds, third person, Spanish
./build/virtualhouse /USEMOUSE /KIDMODE /ANIMSOUND /SHOWPLAYER /LANGUAGE 3
```

### With Stairs Instead of Ramps

```bash
# Use stairs at 180 degrees
./build/virtualhouse /USEMOUSE /PERPSTAIR 1

# Use double stairs
./build/virtualhouse /USEMOUSE /PERPSTAIR 5
```

### For Research/Experiments

```bash
# Basic experiment setup
./build/virtualhouse mylog.txt /TRIAL 1 /AUTOEXIT /USEJOYSTICK

# Full experiment with all options
./build/virtualhouse subject1_trial1.txt /LANGUAGE 2 /TRIAL 1 /AUTOEXIT /USEJOYSTICK /LOGTOTAL subject1_total.txt
```

### Gamepad/Joystick Users

```bash
# Joystick control
./build/virtualhouse /USEJOYSTICK

# Joystick with custom speeds
./build/virtualhouse /USEJOYSTICK /JOYANGVEL 3 /JOYTRANSVEL 0.2
```

---

## ⌨️ In-Game Keyboard Controls

| Key | Action |
|-----|--------|
| **↑ / ↓** | Move forward / backward |
| **← / →** | Turn left / right |
| **P** | Toggle 3rd-person view |
| **M** | Toggle mouse control |
| **I** | Toggle info display |
| **F** | Decrease field of view |
| **D** | Increase field of view |
| **1** | Decrease view range |
| **2** | Increase view range |
| **3** | Toggle textures on/off |
| **H** | Adjust player height |
| **S** | Start intro rotation |
| **E** | Toggle auto-exit |
| **J** | Toggle joystick |
| **L** | Increase input latency |
| **K** | Decrease input latency |
| **Q / ESC** | Quit game |

---

## 🔧 Troubleshooting

### Game won't start
- Make sure you built the project first: `meson compile -C build`
- Run from the project root directory (where `Media/` folder is)

### No sound on macOS
- The game uses `afplay` for audio - this should work out of the box
- Check your system volume

### Animal sounds not playing
- You must use **both** `/KIDMODE` and `/ANIMSOUND` together
- Example: `./build/virtualhouse /USEMOUSE /KIDMODE /ANIMSOUND`

### Mouse not working
- Add the `/USEMOUSE` flag
- Example: `./build/virtualhouse /USEMOUSE`

