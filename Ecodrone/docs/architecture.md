# Eco Drone Architecture

## Overview

Eco Drone is a quadcopter platform designed around low-cost electronics and recycled materials.

The architecture separates real time control and monitoring.

Arduino handles:

- motor control
- sensor polling
- obstacle detection

Python handles:

- telemetry logging
- manual command input
- monitoring

## Data Flow

Sensor -> Arduino -> Serial -> Python

Distance readings are streamed continuously.

Python parses the data and logs the values to CSV.

## Behavior Model

Base State

Drone maintains hover throttle.

Obstacle Detection

If an object is detected within 60 cm the drone reduces thrust.

External Control

Python can send commands:

U = increase throttle  
D = decrease throttle