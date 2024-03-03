# Exhaust Valve Control Script

This Arduino-based script enables the control of exhaust valves using a single OEM button, offering a straightforward and efficient method for toggling the exhaust system between open and closed states. It interfaces directly with the PCB of a remote fob button, eliminating the need for external relays.

## Features

- **Single Button Control**: Utilizes one OEM button for intuitive operation, allowing the driver to open or close the exhaust valves without distraction.
- **LED Feedback**: Incorporates an LED indicator to provide real-time status of the exhaust valve (open or closed), enhancing usability and safety.
- **Direct Fob Button Integration**: Solder directly to the PCB of a spare remote fob button for seamless and reliable control.
- **Debounce Logic**: Implements state management to accurately detect button presses, preventing false triggers and ensuring reliable operation.

## Hardware Requirements

- **Arduino Board**: Compatible with most Arduino boards.
- **OEM Exhaust button**: Some kind of exhaust button on the car that you can tap into.
- **Remote Fob Button**: The wires need to be soldered directly to the PCB of a remote fob, where the button used for toggling the exhaust valve state is.
- **LED**: An optional LED for visual feedback on the system's status.

## Pin Configuration

- `buttonPin`: Input pin connected to the OEM button.
- `onSignalPin`: Output pin to signal the opening of the exhaust valves - connected to remote fob 'on' button.
- `offSignalPin`: Output pin to signal the closing of the exhaust valves - connected to remote fob 'off' button.
- `ledPin`: Output pin connected to an LED for status indication.

## Setup and Installation

1. **Solder to Remote Fob**: Carefully solder the Arduino header wire connections directly to the PCB of the remote fob button according to the pin configuration.
2. **Upload Script**: Load the script onto your Arduino board using the Arduino IDE.
3. **Test System**: Verify the operation by pressing the OEM button and observing the LED and exhaust valve behavior.

## Operation

Pressing the OEM button toggles the state of the exhaust valves. The script monitors the button state to switch between opening and closing the valves. The built-in LED offers visual feedback, indicating the current state of the exhaust system.
