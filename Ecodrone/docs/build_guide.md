# Eco Drone Build Guide

## Frame Construction

1 Cut four arms from recycled plastic containers.
2 Reinforce arms with carbon rods or wooden dowels.
3 Mount arms to a central plate using nylon bolts.
4 Attach motors at the ends of the arms.

## Electronics

1 Mount Arduino at center plate.
2 Attach ESC signal wires to Arduino pins.
3 Connect ultrasonic sensor to front of frame.
4 Route battery leads through power distribution board.

## Firmware

Upload drone_controller.ino to Arduino using Arduino IDE.

## Python Telemetry

Install required library.

pip install pyserial

Run telemetry script.

python telemetry.py

## Testing

Start with motors disarmed.

Verify distance readings appear in terminal.

Gradually increase throttle.