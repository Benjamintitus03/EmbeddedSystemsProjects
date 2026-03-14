import serial
import time
import csv
import sys

PORT = "/dev/ttyUSB0"
BAUD = 115200

class DroneTelemetry:

    def __init__(self, port, baud):
        self.ser = serial.Serial(port, baud, timeout=1)
        self.log = open("drone_log.csv","w",newline="")
        self.writer = csv.writer(self.log)
        self.writer.writerow(["timestamp","distance"])

    def send(self, cmd):
        self.ser.write(cmd.encode())

    def read(self):
        try:
            line = self.ser.readline().decode().strip()
            return line
        except:
            return None

    def parse(self, data):
        if data and data.startswith("DIST:"):
            return float(data.split(":")[1])
        return None

    def run(self):
        while True:

            data = self.read()

            if data:
                dist = self.parse(data)

                if dist is not None:
                    t = time.time()
                    self.writer.writerow([t, dist])

                    print("distance:", dist)

                    if dist < 40:
                        self.send("D")

            time.sleep(0.05)


def keyboard_control(drone):

    while True:
        key = input()

        if key == "u":
            drone.send("U")

        if key == "d":
            drone.send("D")


if __name__ == "__main__":

    drone = DroneTelemetry(PORT, BAUD)

    try:
        drone.run()
    except KeyboardInterrupt:
        print("stopping")
        sys.exit()