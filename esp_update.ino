#include <WiFi.h>
#include <WiFiUdp.h>
#include <NewPing.h>

// WiFi network settings
const char* ssid = "your_ssid";
const char* password = "your_password";

// UDP settings
const int localUdpPort = 20001;
char incomingPacket[255];  // Buffer for incoming packets
WiFiUDP udp;

// Motor control pins
#define ENA_PIN 14  
#define IN1_PIN 27  
#define IN2_PIN 26  
#define IN3_PIN 25  
#define IN4_PIN 33  
#define ENB_PIN 32  

// Ultrasonic sensor pins
#define TRIGGER_PIN 12
#define ECHO_PIN 13
#define MAX_DISTANCE 200 // Maximum distance (in cm) to measure

// Buzzer pin
#define BUZZER_PIN 15

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(115200);

  // Initialize motor control pins
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);

  analogWrite(ENA_PIN, 150); 
  analogWrite(ENB_PIN, 150);

  // Initialize buzzer pin
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN); // Ensure buzzer is off initially

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start UDP
  udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    // Receive incoming UDP packets
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);

    String command = String(incomingPacket);

    if (command == "Center" || command == "Empty Package") {
      CAR_stop();
    }
    if (command == "Up") {
      CAR_moveForward();
    }
    if (command == "Down") {
      CAR_moveBackward();
    }
    if (command == "Right" || command == "Upper Right" || command == "Right Down" ) {
      CAR_turnRight();
    }
    if (command == "Left" || command == "Upper Left" || command == "Left Down") {
      CAR_turnLeft();
    }
  }

  // Measure distance
  unsigned int distance = sonar.ping_cm();
  if (distance > 0) { // Ensure valid distance measurement
    if (distance < 5) {
      // Stop the car and sound buzzer continuously
      CAR_stop();
      tone(BUZZER_PIN, 1000); // Continuous beep
    } else if (distance < 30) {
      // Sound buzzer with increasing frequency
      int buzzerFrequency = map(distance, 5, 30, 1000, 2000); // Map distance to buzzer frequency
      tone(BUZZER_PIN, buzzerFrequency);
    } else {
      // Turn off buzzer if distance is greater than 30 cm
      noTone(BUZZER_PIN);
    }
  } else {
    // If distance measurement fails, turn off buzzer
    noTone(BUZZER_PIN);
  }

  delay(100); // Short delay to avoid overwhelming the ESP32
}

void CAR_moveForward() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_moveBackward() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void CAR_turnLeft() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_turnRight() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void CAR_stop() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}
