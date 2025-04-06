# Interfacing MAX7219 with TIVA C LaunchPad

## Overview
This project demonstrates interfacing the MAX7219 LED display driver with the TIVA C LaunchPad (EK-TM4C123GXL, TM4C123GH6PM microcontroller) using direct register access (no TivaWare). The MAX7219 controls an 8x8 LED matrix via SPI communication, showcasing embedded systems skills such as SPI configuration, GPIO handling, and real-time display updates. The code includes functions to display, static patterns, and clear the matrix, with a focus on educational use and hardware-level programming.

### Features
- Configures SPI (SSI0) for communication with the MAX7219 at 1.6 MHz.
- Implements GPIO control for the MAX7219's CS (Chip Select) pin.
- Supports initialization with adjustable brightness, scan limit, and decode mode.
- Sets the system clock to 16 MHz using direct register configuration.

## Hardware Requirements
- **TIVA C LaunchPad**: EK-TM4C123GXL with TM4C123GH6PM microcontroller.
- **MAX7219 Module**: 8x8 LED matrix with MAX7219 driver (e.g., common-cathode type).
- **Connections**:
  - MAX7219 VCC → 5V (or 3.3V with level shifter if needed)
  - MAX7219 GND → GND
  - MAX7219 DIN → PD3 (SSI3Tx)
  - MAX7219 CLK → PD0 (SSI3Clk)
  - MAX7219 CS → PD1 (GPIO for Chip Select/LOAD)
- **Optional**: Level shifter (e.g., 74HCT245) if using 3.3V logic with a 5V MAX7219 module.
- **Jumper Wires**: For connecting the MAX7219 module to the LaunchPad.

## Software Requirements
- **Code Composer Studio (CCS)**: Version 12.4.0 or later.
- **Compiler**: TI ARM Compiler (included with CCS).
- **Header File**: `tm4c123gh6pm.h` for register definitions.

## Setup Instructions
1. **Hardware Setup**:
   - Connect the MAX7219 module to the TIVA C LaunchPad as per the pin assignments above.
   - Ensure proper power supply (5V or 3.3V with level shifting) and ground connections.
   - Power the LaunchPad via USB.
2. **Software Setup**:
   - Clone or download this repository.
