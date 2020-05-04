#define trigPin 8
#define echoPin 7

int distance;

void setup()
{
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{
    int distance = readUltrasonicDistance();

    // Send results to Serial Monitor
    Serial.print("Distance = ");
    if (distance >= 400 || distance <= 2) // the sensor has the maximum range of 400 cm and minimum of 2cm
        Serial.println("Out of range");
    else
    {
        Serial.print(distance);
        Serial.println(" cm");
        delay(500);
    }
    delay(500);
}

// Retern the distance between the object and the ultrasonic sensor in cm
int readUltrasonicDistance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Must send the pulses rapidly during 10 microseconds
    digitalWrite(trigPin, LOW);

    // pulseIn() returns the amount of time the pulse stay high. 0.01723
    return 0.01723 * pulseIn(echoPin, HIGH);
    // 1 second = 10^6 microsecconds. Speed of sound in dry air: 343 m/s -> 0.0343 cm/microseconds
}
