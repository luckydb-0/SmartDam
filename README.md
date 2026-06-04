# SmartDam

SmartDam is a distributed IoT system for monitoring and controlling a smart dam infrastructure.

The project combines embedded devices, remote sensors, backend services, a dashboard, and a mobile application to simulate a complete smart monitoring environment. The embedded components are responsible for collecting data and controlling actuators, while the software components provide communication, visualization, and user interaction.

## Project Structure

```text
SmartDam/
├── dam_controller/    # Embedded controller for dam actuation and local logic
├── dam_remotehyd/     # Remote hydrometer module for water-level/environment monitoring
├── dam_service/       # Backend service
├── dam_dashboard/     # Desktop/dashboard application
├── dam_mobileapp/     # Mobile application
└── doc/               # Documentation and project diagrams
```

## Main Components

### Dam Controller

The dam controller manages the local behavior of the dam system.  
It includes logic for communication, state management, LED signaling, and servo motor control.

### Remote Hydrometer

The remote hydrometer is an embedded module used to collect environmental data, such as water level and temperature, and communicate it to the rest of the system.

### Backend Service

The backend service acts as the central communication layer between the embedded devices and the user-facing applications.

### Dashboard

The dashboard provides a visual interface for monitoring the state of the system and interacting with the dam infrastructure.

### Mobile App

The mobile application allows users to interact with the system from a mobile device, including communication through Bluetooth-related components.

## Technologies

- Java
- C / C++
- Arduino
- Gradle
- Android
- Bluetooth communication
- Embedded systems concepts

## Documentation

Additional documentation, diagrams, and project material (in italian) can be found in the `doc/` folder.
