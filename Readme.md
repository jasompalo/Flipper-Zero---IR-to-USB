# IR to Spacebar

Flipper Zero app that sends spacebar when it receives any IR signal. Made for Geometry Dash but works for whatever you want

## Requirements

- Flipper Zero (any firmware)
- Python 3.9+
- uFBT

## Setup

Install uFBT:
```bash
pip install ufbt
```

Pull the Momentum SDK:
```bash
python -m ufbt update
```

Build and deploy:
```bash
python -m ufbt launch
```

## Usage

1. Connect Flipper to PC via USB
2. Launch the app
3. Point any IR remote at the Flipper and press a button
4. It sends spacebar to your PC

Hold BACK to exit

## Credits

- [@jasompalo](https://github.com/jasompalo) - original idea
- [@pilot2254](https://github.com/pilot2254) - rework
