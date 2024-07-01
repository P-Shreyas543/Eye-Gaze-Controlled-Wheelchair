# Eye Gaze Controlled Wheelchair

## Project Description
The Eye Gaze Controlled Wheelchair enhances mobility for individuals with severe physical disabilities. Using a webcam and Raspberry Pi for real-time eye-tracking, the system sends commands to an ESP32 microcontroller to control the wheelchair's motors. It offers hands-free navigation, improving independence and quality of life.

## Features
- Real-time eye tracking
- Gaze direction detection
- Wireless UDP communication

## Repository Structure
\`\`\`
eye-gaze-controlled-wheelchair/
├── README.md
├── app.py
├── requirements.txt
├── src/
│   ├── __init__.py
│   ├── face_detection.py
│   ├── gaze_control.py
├── esp32/
│   └── main.ino
└── tests/
    └── test_gaze_control.py
\`\`\`

## Installation

### Raspberry Pi and OpenCV Setup

1. Clone the repository:
    \`\`\`bash
    git clone https://github.com/yourusername/eye-gaze-controlled-wheelchair.git
    cd eye-gaze-controlled-wheelchair
    \`\`\`

2. Create and activate a virtual environment:
    \`\`\`bash
    python -m venv venv
    source venv/bin/activate  # On Windows use \`venv\Scripts\activate\`
    \`\`\`

3. Install dependencies:
    \`\`\`bash
    pip install -r requirements.txt
    \`\`\`

### Setting Up the ESP32

1. Open the \`main.ino\` file located in the \`esp32\` directory with the Arduino IDE.
2. Ensure you have the necessary libraries installed:
    - WiFi
    - WiFiUdp
3. Update the WiFi credentials in the code with your own network details:
    \`\`\`cpp
    const char* ssid = \"your_SSID\";
    const char* password = \"your_PASSWORD\";
    \`\`\`
4. Connect the ESP32 to your computer and select the correct board and port in the Arduino IDE.
5. Upload the code to the ESP32.
6. Open the Serial Monitor to see the connection status and incoming commands.

### Wiring for Motor Control

Connect the ESP32 to the motor driver as follows:
- ENA_PIN (GPIO 14) -> Motor Driver ENA
- IN1_PIN (GPIO 27) -> Motor Driver IN1
- IN2_PIN (GPIO 26) -> Motor Driver IN2
- IN3_PIN (GPIO 25) -> Motor Driver IN3
- IN4_PIN (GPIO 33) -> Motor Driver IN4
- ENB_PIN (GPIO 32) -> Motor Driver ENB

Ensure the motor driver is properly connected to the motors and powered.

## Usage

1. Run the application on your Raspberry Pi:
    \`\`\`bash
    python app.py
    \`\`\`
2. Follow the on-screen instructions to control the wheelchair using your eye gaze.

## Testing

Add tests for critical parts of your project to ensure everything works as expected. Use a framework like \`unittest\` or \`pytest\`.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.
