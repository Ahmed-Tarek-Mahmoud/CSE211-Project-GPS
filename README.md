# CSE211-Project-GPS
# GPS Tracking System Using TM4C123GH6PM

This project involves creating a GPS tracking system using the TM4C123GH6PM microcontroller, a GPS module, an LCD display, and a few additional components. The system allows users to either set a 100-meter limit or enter a specific destination. Once the conditions are met, the coordinates are sent to a PC, and a Python script is used to visualize the path using gmplot.

## Features

- **100-Meter Limit Mode**: Users can select this mode to trigger an alert when they move 100 meters away from the starting point.
- **Destination Mode**: Users can input a specific latitude and longitude as their destination.
- **Interrupt Handling**: Use of physical switches to trigger events.
- **LED and LCD Feedback**: Visual indicators for user actions.
- **Serial Communication**: Sends GPS coordinates to a PC for further processing.
- **Path Visualization**: Python script to plot the path using gmplot.

## User Stories

### User Story 1: Select Operation Mode

As a user, I want to select the operation mode of the GPS tracking system through a terminal interface or a physical switch, so that I can choose between a 100-meter limit or a specific destination.

**Acceptance Criteria:**
1. Open the terminal using PuTTY on a PC.
2. Enter 'N' to select the 100-meter limit mode.
3. Enter 'Y' to enter the destination mode.
4. In destination mode, input the final destination latitude and longitude.

### User Story 2: Trigger Alert

As a user, I want the system to alert me when the predefined condition (100-meter limit or reaching the destination) is met or when I press Switch 1, so that I know when to perform the next action.

**Acceptance Criteria:**
1. When the user moves 100 meters away from the starting point or reaches the destination coordinates, a red LED turns on.
2. The LCD displays the message 'Press Switch 1'.
3. The user can also press Switch 1 to trigger the alert manually and end the path.

### User Story 3: Send Coordinates and Visualize Path

As a user, I want to send the GPS coordinates to my PC and visualize the path on a map, so that I can see my movement history.

**Acceptance Criteria:**
1. Press Switch 2 to send the current GPS coordinates to the PC.
2. The LCD displays 'Open Serial' indicating that the terminal should be opened.
3. Open the terminal and send 'U' to start the transmission of coordinates.
4. Run a provided Python script to draw the path using gmplot.

## Setup Instructions

1. **Hardware Setup**:
   - Connect the TM4C123GH6PM microcontroller to the GPS module.
   - Connect the LCD display to the microcontroller.
   - Connect the TM4C123GH6PM microcontroller to the PC with a UART to TTL module
   - Ensure all connections are properly secured and powered.

2. **Software Setup**:
   - Install PuTTY on your PC for serial communication.
   - Prepare the TM4C123GH6PM firmware to handle GPS data, user input, and control the LED and LCD.
   - Install Python and gmplot library on your PC.

3. **Operation**:
   - Power up the system.
   - Use the terminal to select the mode.
   - Follow the on-screen instructions on the LCD for further actions.

4. **Python Script**:
   - Run the provided Python script after receiving the GPS coordinates to visualize the path on a map.

## Dependencies

- TM4C123GH6PM microcontroller
- GPS module
- LCD display
- PuTTY terminal software
- Python 3.x
- gmplot library for Python

---

For further details and troubleshooting, please refer to the project documentation or contact the project maintainer.
