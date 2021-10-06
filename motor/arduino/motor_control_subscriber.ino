#define NOTE_C3  131
#define NOTE_C7  2093

#include <string.h>
#include <stdio.h>
#include <ros.h>
#include <std_msgs/UInt16MultiArray.h>

const int l_speed = 10;
const int l_motor = 12;
const int r_speed = 11;
const int r_motor = 13;
const int buzzer = 4;
//const int led = 5;

void Motor(int ls, int rs) {
    digitalWrite(l_motor, HIGH);
    digitalWrite(r_motor, HIGH);

    Buzzer(0);
    analogWrite(l_speed, ls);
    analogWrite(r_speed, rs);
}

void controller (const std_msgs::UInt16MultiArray keystroke) {
    int ls = keystroke.data[0];
    int rs = keystroke.data[1];

    ROS_INFO("ls: %d, rs: %d", ls, rs);

    Motor(ls, rs);
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
ros::Subscriber <std_msgs::UInt16MultiArray> sub("controller", controller);
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
