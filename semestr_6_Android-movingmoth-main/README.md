# MovingMoth



## Description

Android (Kotlin) application for steering the mobile robot.

## Features:

# Pilot
A view that allows you to control the direction of the robot's movement. It also allows you to set the appropriate height of the lift.

# Sensors
A view to preview obstacle distance data from US100 ultrasonic sensors and lift height level from LIDAR tfmini sensor.

# Camera
A view that allows you to look at what's directly in front of the robot by using a photo from a USB camera.

## Communication with RaspberryPi.
Data is sent to and received from the microcomputer with using the MQTT protocol, where the computer is the broker and the application is the client of the protocol.

## Usage
To run an application you need a working mqtt broker, with a known IP address. For example https://www.hivemq.com/demos/websocket-client/. To send the photo you need to setup a broker one your own computer, because online brokers doesn't allows us to send that much data.

## Authors
Marcel Garczyk, Paweł Hatka
