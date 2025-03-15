# ESP32 Parking Sensor

A simple parking occupancy sensor made with an ESP32 node using an HC-SR04 ultrasonic distance sensor to estimate the presence of a car in a parking spot. The communication is achieved with the ESP-NOW protocol.

## Building

This is a [PlatformIO](https://platformio.org) project. To build it, [install PlatformIO](https://docs.platformio.org/en/latest/core/installation/index.html), and then run the bash script **compile.sh**:

```
bash compile.sh <project_folder_dir>
```

## Simulation

To simulate this project, [Wokwi for VS Code](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode) can be used after compiling.
