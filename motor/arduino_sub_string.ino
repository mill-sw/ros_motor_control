#define NOTE_C3  131
#define NOTE_C7  2093

#include <string.h>
#include <stdio.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

const int l_speed = 10;
const int l_motor = 12;
const int r_speed = 11;
const int r_motor = 13;
const int buzzer = 4;
//const int led = 5;

void Motor(char lm, int ls, char rm, int rs) {
    Buzzer(0);
    digitalWrite(l_motor, lm);
    analogWrite(l_speed, ls);
    digitalWrite(r_motor, rm);
    analogWrite(r_speed, rs);
//  ros::ROS_INFO("state: %d, data: %d", state, speed);
}

void controller (const std_msgs::String keystroke) {
    char l_m = keystroke.data[0];
    char l_s = keystroke.data[1];
    char r_m = keystroke.data[3];
    char r_s = keystroke.data[4];
    int minSpeed = 159;
    char lm;
    char rm;
    int ls;
    int rs;
// convert motor 0 to HIGH, else to LOW
    if (l_m == '0') {
        lm = HIGH;
    } else {
        lm = LOW;
    }
    if (r_m == '0') {
        rm = HIGH;
    } else {
        rm = LOW;
    }
// convert 1~9 to min~255
    if (l_s == '0') {
        ls = 0;
    } else {
        int lspe = (int)(l_s);
        ls = map(lspe, 1, 9, minSpeed, 255);
    }
    if (r_s == '0') {
        rs = 0;
    } else {
        int rspe = (int)(r_s);
        rs = map(rspe, 1, 9, minSpeed, 255);
    }

    Motor(lm, ls, rm, rs);
}

void Buzzer(int condition) {
    switch (condition) {
        default:
            //            tone(buzzer, NOTE_B0, 100);
        case 0:
            tone(buzzer, NOTE_C3, 100);
            delay(100);
            tone(buzzer, NOTE_C7, 100);
            delay(100);
        case 1:

            delay(250);

            delay(250);
        case 2:

            delay(250);

            delay(250);

            delay(250);
        case 3:

            delay(250);

            delay(250);

            delay(250);

            delay(250);
    }
}

void Led() {
}

ros::NodeHandle nh;
ros::Subscriber <std_msgs::String> sub("controller", controller);
//ros::Subscriber sub("cmd_vel", cmd_vel_cb);  // for teleop

void setup() {
    pinMode(r_speed, OUTPUT);
    pinMode(r_motor, OUTPUT);
    pinMode(l_speed, OUTPUT);
    pinMode(l_motor, OUTPUT);
    pinMode(buzzer, OUTPUT);
//  pinMode(led, OUTPUT);

    nh.initNode();
    nh.subscribe(sub);
}

void loop() {
    nh.spinOnce();
    delay(1);
}
