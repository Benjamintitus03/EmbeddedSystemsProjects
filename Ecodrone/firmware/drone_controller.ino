#include <Wire.h>
#include <Servo.h>

#define TRIG_PIN 7
#define ECHO_PIN 6

#define MOTOR_FL 3
#define MOTOR_FR 5
#define MOTOR_BL 9
#define MOTOR_BR 10

Servo escFL;
Servo escFR;
Servo escBL;
Servo escBR;

long duration;
float distance;

int baseThrottle = 1200;

float readDistance()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2.0;

    return distance;
}

void setMotors(int fl, int fr, int bl, int br)
{
    escFL.writeMicroseconds(fl);
    escFR.writeMicroseconds(fr);
    escBL.writeMicroseconds(bl);
    escBR.writeMicroseconds(br);
}

void stabilize()
{
    setMotors(baseThrottle, baseThrottle, baseThrottle, baseThrottle);
}

void avoidObstacle(float d)
{
    if(d < 60)
    {
        setMotors(baseThrottle - 120, baseThrottle - 120, baseThrottle - 120, baseThrottle - 120);
        delay(250);
    }
}

void handleSerial()
{
    if(Serial.available())
    {
        char cmd = Serial.read();

        if(cmd == 'U')
            baseThrottle += 20;

        if(cmd == 'D')
            baseThrottle -= 20;

        if(baseThrottle < 1100)
            baseThrottle = 1100;

        if(baseThrottle > 1500)
            baseThrottle = 1500;
    }
}

void setup()
{
    Serial.begin(115200);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    escFL.attach(MOTOR_FL);
    escFR.attach(MOTOR_FR);
    escBL.attach(MOTOR_BL);
    escBR.attach(MOTOR_BR);

    setMotors(1000,1000,1000,1000);
    delay(3000);
}

void loop()
{
    float d = readDistance();

    stabilize();
    avoidObstacle(d);
    handleSerial();

    Serial.print("DIST:");
    Serial.println(d);

    delay(50);
}