#!/usr/bin/env python3
import rospy
from std_msgs.msg import UInt16MultiArray
import sys, select, termios, tty


max_speed = 255
min_speed = 96
stop = 0

msg = """
  w
a s d

w/s : increase/decrease speed
a/d : increase/decrease L or R speed
space key, x : stop
CTRL-C : quit
================================================================================
"""

e = """
Communications Failed
"""

settings = termios.tcgetattr(sys.stdin)
def getKey():
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)

    return key


def vels(L_speed, R_speed):

    return f"L : {L_speed}       R : {R_speed}"


def constrain(input, min_speed, max_speed):
    if input < min_speed:
        input = min_speed
    elif input > max_speed:
        input = max_speed
    else:
        input = input

    return input


def main():
    pub = rospy.Publisher('controller', UInt16MultiArray, queue_size=10)
    rospy.init_node('roscar_teleop', anonymous=True)

    data_output = UInt16MultiArray()
    data_output.data = [0, 0]
    # data_output.data = [0, 0, 0, 0]

    L_speed = stop
    R_speed = stop

    try:
        print(msg)
        while (1):
            key = getKey()
            if key == 'w':
                if L_speed == R_speed:                    
                    L_speed += 2
                    R_speed += 2
                else:
                    sync_speed = max(L_speed, R_speed)
                    L_speed = sync_speed
                    R_speed = sync_speed
                L_speed = constrain(L_speed, min_speed, max_speed)
                R_speed = constrain(R_speed, min_speed, max_speed)
                print(vels(L_speed, R_speed))
            elif key == 's':
                if L_speed == R_speed:
                    L_speed -= 2
                    R_speed -= 2
                else:
                    sync_speed = max(L_speed, R_speed)
                    L_speed = sync_speed
                    R_speed = sync_speed
                L_speed = constrain(L_speed, min_speed, max_speed)
                R_speed = constrain(R_speed, min_speed, max_speed)
                print(vels(L_speed, R_speed))
            elif key == 'a':
                R_speed += 4
                R_speed = constrain(R_speed, min_speed, max_speed)
                print(vels(L_speed, R_speed))
            elif key == 'd':
                L_speed += 4
                L_speed = constrain(L_speed, min_speed, max_speed)
                print(vels(L_speed, R_speed))
            elif key == 'x' or key == ' ':
                L_speed = 0
                R_speed = 0
                print(vels(L_speed, R_speed))
        # let speed stay above min_speed always
            elif L_speed > max_speed:
                L_speed = max_speed
            elif L_speed < min_speed:
                L_speed = stop
            elif R_speed > max_speed:
                R_speed = max_speed
            elif R_speed < min_speed:
                R_speed = stop
        # ctl+c to close
            else:
                if (key == '\x03'):
                    break
        # data output
            data_output.data[0] = L_speed
            data_output.data[1] = R_speed
            # data_output.data[3] = L_speed
            # data_output.data[4] = R_speed
            pub.publish(data_output)

    except rospy.ROSInterruptException:
        pass

    finally:  # code publish
        pub.publish(data_output)
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)


if __name__ == '__main__':
    main()
