# Eye Gaze Controlled Wheelchair

## Project Description
The Eye Gaze Controlled Wheelchair enhances mobility for individuals with severe physical disabilities. This system uses a webcam and Raspberry Pi for real-time eye-tracking to send commands to an ESP32 microcontroller, which controls the wheelchair's motors. The project provides hands-free navigation to improve user independence and quality of life.

## Features
- Real-time eye tracking
- Gaze direction detection
- Wireless UDP communication

## OpenCV Setup

### Prerequisites

1. **Install Python**:
   - Download and install Python from the [official Python website](https://www.python.org/downloads/release/python-31011/). Ensure that Python 3.x is installed.
   - Add Python to your system PATH during installation.

2. **Install Python Libraries**:
   - Open a terminal or command prompt and install the necessary libraries by running:
     ```bash
     pip install opencv-python mediapipe numpy
     ```

### Running the Application

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/eye-gaze-controlled-wheelchair.git
    cd eye-gaze-controlled-wheelchair
    ```

2. **Create and activate a virtual environment**:
    ```bash
    python -m venv venv
    source venv/bin/activate  # On Windows use `venv\Scripts\activate`
    ```

3. **Install dependencies**:
    ```bash
    pip install -r requirements.txt
    ```

4. **Replace the placeholder IP address** in `app.py` with the actual IP address of your ESP32. Open `app.py` and find:
    ```python
    server_address_port = ("ip_of_esp32", 20001)
    ```
    Replace `"ip_of_esp32"` with the IP address of your ESP32.

5. **Run the application**:
    ```bash
    python app.py
    ```

6. **Follow the on-screen instructions** to control the wheelchair using your eye gaze.

## Setting Up the ESP32

1. **Open the `main.ino` file** located in the `esp32` directory with the Arduino IDE.

2. **Install necessary libraries**:
    - WiFi
    - WiFiUdp

3. **Update WiFi credentials** in the code with your network details:
    ```cpp
    const char* ssid = "your_ssid";
    const char* password = "your_password";
    ```

4. **Connect the ESP32** to your computer and select the correct board and port in the Arduino IDE.

5. **Upload the code** to the ESP32.

6. **Open the Serial Monitor** to see the connection status and incoming commands.

## Wiring for Motor Control

Connect the ESP32 to the motor driver as follows:
- `ENA_PIN` (GPIO 14) -> Motor Driver `ENA`
- `IN1_PIN` (GPIO 27) -> Motor Driver `IN1`
- `IN2_PIN` (GPIO 26) -> Motor Driver `IN2`
- `IN3_PIN` (GPIO 25) -> Motor Driver `IN3`
- `IN4_PIN` (GPIO 33) -> Motor Driver `IN4`
- `ENB_PIN` (GPIO 32) -> Motor Driver `ENB`

Ensure the motor driver is properly connected to the motors and powered.

## Testing

Add tests for critical parts of your project to ensure everything works as expected. Use a framework like `unittest` or `pytest` for Python.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request.

## Troubleshooting

- **ESP32 not connecting to WiFi**: Ensure that the SSID and password are correctly set in `main.ino` and that the ESP32 is within range of the network.

- **Motor not responding**: Check the wiring connections and ensure the motor driver is properly powered. Also, make sure the motor driver is correctly configured in the ESP32 code.

- **Errors running `app.py`**: Verify that all dependencies are correctly installed and that your Python environment is correctly set up. Ensure the webcam is properly connected and accessible.

- **No UDP communication**: Make sure that the ESP32 and Raspberry Pi are on the same network. Check if the port numbers in `app.py` and `main.ino` match.

- **Unexpected behavior**: Check the Serial Monitor on the ESP32 for debugging information. Ensure the gaze detection and command mapping in `app.py` are functioning as intended.

Feel free to add more troubleshooting tips based on common issues you encounter.
