#ifndef Mirobot_h
#define Mirobot_h

#include "Arduino.h"
#include "HotStepper.h"
#include "CmdProcessor.h"
#include <EEPROM.h>

#define STEPS_PER_TURN    2048.0
#define WHEEL_DIAMETER    80.0
#define CIRCUMFERENCE_MM  251.3		// wheel diameter * pi
#define STEPS_PER_MM      STEPS_PER_TURN / CIRCUMFERENCE_MM
#define WHEEL_DISTANCE    126.0
// when turning, the distance between the wheels is our circle diameter
#define STEPS_PER_DEGREE  ((WHEEL_DISTANCE * 3.1416) / 360) * STEPS_PER_MM 

#define WIFI_RESET 3
#define WIFI_READY 2
#define STATUS_LED 13

#define MIROBOT_VERSION "20141126"

#define MAGIC_BYTE_1 0xF0
#define MAGIC_BYTE_2 0x0D

#define SERVO_PIN 3
#define SERVO_PULSES 15

#define SPEAKER_PIN 9
#define NOTE_C4  262

#define LEFT_LINE_SENSOR  A0
#define RIGHT_LINE_SENSOR A1

#define LEFT_COLLIDE_SENSOR  A3
#define RIGHT_COLLIDE_SENSOR A2

typedef enum {POWERED_UP, CONNECTED} mainState_t;

typedef enum {UP, DOWN} penState_t;

typedef enum {NORMAL, RIGHT_REVERSE, RIGHT_TURN, LEFT_REVERSE, LEFT_TURN} collideState_t;

struct HwVersion {
  byte major;
  byte minor;
};

class Mirobot {
  public:
    Mirobot();
    void setup();
    void setup(Stream &s);
    void forward(int distance);
    void back(int distance);
    void right(int angle);
    void left(int angle);
    void arc2(int angle, int radius);
    void penup();
    void pendown();
    void pause();
    void resume();
    void stop();
    void reset();
    void follow();
    int  followState();
    void collide();
    void collideState(char &state);
    void beep(int);
    void setHwVersion(char&);
    boolean ready();
    void process();
    HwVersion hwVersion;
    boolean blocking;
    boolean collideNotify;
    boolean followNotify;
  private:
    void wait();
    void followHandler();
    void collideHandler();
    void ledHandler();
    void servoHandler();
    void autoHandler();
    void sensorNotifier();
    void checkState();
    void initHwVersion();
    char lastCollideState;
    int lastFollowState;
    mainState_t mainState;
    collideState_t _collideState;
    unsigned long lastLedChange;
    Mirobot& self() { return *this; }
    penState_t penState;
    void setPenState(penState_t);
    unsigned long next_servo_pulse;
    unsigned char servo_pulses_left;
    boolean paused;
    boolean following;
    boolean colliding;
};

#endif
