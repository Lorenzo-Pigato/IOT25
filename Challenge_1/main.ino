#include <WiFi.h>
#include <esp_now.h>

/*
  Internet of Things - First Challenge
  Date: 11-03-2025 / 20-03-2025

  Abate Kevin:    10812892
  Pigato Lorenzo: 10766953 [Team Leader]

  Project Title: Parking occupancy node
*/

// Distance sensor HC-SR04 pinout

#define TRIG_PIN 12
#define ECHO_PIN 14

// Constants

#define SLEEP_TIME_SEC  8       // Formula: 53 % 50 + 5 = 8 
#define S_uS_CONV 1000000       // Conversion factor from us to s

#define SIM 1 // Simulation mode: 1 ON | 0 OFF

uint8_t broadcastAddress[] = {0x8C, 0xAA, 0xB5, 0x84, 0xFB, 0x90};

esp_now_peer_info_t ESP_sink; // peer data

// -- Functions' prototypes -- //
float getDistance();
void wifiInit();
void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void sendMessage(String message);
// --------------------------- //

void setup()
{

    // Open serial port: 115200
    Serial.begin(115200);

    // HC-SR04 configuration
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);

}

void loop()
{
    // -- loop will be executed only once per cycle due to deep sleep call -- //

    // Fetch distance
    int distance = getDistance();

    // Check parking status
    String message = distance < 50 ? "OCCUPIED" : "FREE";

    // Configure WiFi for transmission and send message to sink
    wifiInit();
    sendMessage(message);

    // Set delay to allow simulation to work correctly
    if (SIM)
        delay(250);

    Serial.println("Entering deep sleep...");
    Serial.flush(); // Flush serial buffer before entering deep sleep

    // Set wakeup timer
    esp_sleep_enable_timer_wakeup(SLEEP_TIME_SEC * S_uS_CONV);
    esp_deep_sleep_start();
}

// Functions' Definition //

// Fetch a new measure and convert the value in cm
float getDistance()
{

    digitalWrite(TRIG_PIN, HIGH); // Start emitting signal
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW); // Stop emitting signal

    // Calculate the time occurred between sending and receiving back the signal
    int duration = pulseIn(ECHO_PIN, HIGH);

    // Convert the result in cm according to sensor's datasheet
    float distance = duration / 58.3;

    Serial.print("Distance: ");
    Serial.println(distance);

    return distance;
}

void wifiInit()
{
    Serial.println("Initializing WiFi...");

    WiFi.mode(WIFI_STA);
    WiFi.setTxPower(WIFI_POWER_2dBm); // Set wifi transmission power
    esp_now_init();                   // Init ESP-NOW communication protocol

    esp_now_register_recv_cb(onDataRecv); // Set receiving callback
    esp_now_register_send_cb(onDataSent); // Set sending callback

    // Peer registration
    memcpy(ESP_sink.peer_addr, broadcastAddress, 6);
    ESP_sink.channel = 0;
    ESP_sink.encrypt = false;

    esp_now_add_peer(&ESP_sink); // Add sink to peers
}

// Receiving callback (for simulation purpouse)
void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
    char rcvstring[data_len];
    memcpy(rcvstring, data, data_len);
    
    Serial.print("Message received: ");
    Serial.println(String(rcvstring));
}

// Sending callback
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    Serial.print("Message sent - status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "SUCCESS" : "ERROR");
}

// Send message through WiFi with ESP-NOW protocol
void sendMessage(String message)
{

    uint8_t *addr = broadcastAddress;
    uint8_t *data = (uint8_t *)message.c_str(); // Casting string to uint8_t

    int len = message.length() + 1;

    esp_now_send(addr, data, len);
}