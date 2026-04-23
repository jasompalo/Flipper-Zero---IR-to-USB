# Installation Guide - IR to HID

A Flipper Zero application that converts infrared signals into USB HID keyboard inputs.

## Prerequisites

Before installing, ensure you have:

- **Flipper Zero** device
- **USB-C cable** to connect Flipper to your computer
- **Flipper Zero firmware** installed and up to date
- **uFBT** (Flipper Build Tool) installed on your computer
- **Python 3.9+** (required for uFBT)

## Installation Steps

### 1. Install uFBT

uFBT is the build system for Flipper Zero apps. Install it globally:

```bash
pip3 install ufbt
```

Verify installation:
```bash
ufbt --version
```

### 2. Clone or Download the Repository

Clone this repository to your computer:

```bash
git clone https://github.com/yourusername/ir_to_usb.git
cd ir_to_usb
```

Or download as ZIP and extract to a folder.

### 3. Connect Your Flipper Zero

- Connect your Flipper Zero to your computer using a USB-C cable
- Unlock the Flipper and enable USB connection when prompted
- Keep the device connected throughout the installation

### 4. Build and Install the App

From within the `ir_to_usb` directory, run:

```bash
ufbt flash_usb
```

This command will:
- Build the application
- Flash it to your Flipper Zero via USB
- Install it to the app library

**Note:** If you encounter permission issues, try:
```bash
sudo ufbt flash_usb
```

### 5. Verify Installation

1. On your Flipper Zero, navigate to the **Apps** menu
2. Go to **Misc** category
3. You should see **"IR to HID"** in the list

## Usage

Once installed, launch the app from the Flipper's app library and follow the on-screen instructions to:

1. **Learn IR signals** — point your remote at the Flipper to record button presses
2. **Map to keyboard keys** — bind recorded signals to USB HID keyboard inputs
3. **Use as HID device** — connect your Flipper via USB to your computer to send keyboard commands

## Troubleshooting

### Build fails with "SDK not found"
Update the uFBT SDK:
```bash
ufbt update
```

### Permission denied during flash
Try with `sudo`:
```bash
sudo ufbt flash_usb
```

### Flipper not detected
- Ensure USB cable is connected and device is unlocked
- Try reconnecting the USB cable
- Restart the Flipper device

### App doesn't appear in app library
- Verify the build completed without errors
- Check that the app was flashed (not just built with `ufbt`)
- Restart your Flipper by holding BACK for 2 seconds

## Alternative Installation Methods

### Using CLI Launch (Temporary)
For testing without installing to the library:
```bash
ufbt launch
```
This runs the app temporarily. When you disconnect or restart, it will be gone.

### Manual Firmware Flash (SWD Method)
For advanced users with SWD debugger:
```bash
ufbt flash
```

## Uninstallation

To remove the app from your Flipper:

1. On the Flipper, go to **Apps** → **Misc**
2. Select **IR to HID** and press **Delete**
3. Confirm deletion

Or clean your build environment with:
```bash
ufbt -c
```

## Support

For issues or questions:
- Check the [uFBT documentation](https://github.com/flipperdevices/flipperzero-firmware/blob/dev/documentation/UsingUFBT.md)
- Review the [Flipper Zero developer docs](https://docs.flipper.net/development)
- Open an issue on this repository

## License

MIT
