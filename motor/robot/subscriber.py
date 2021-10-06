import rospy
from std_msgs.msg import UInt16MultiArray


pub = rospy.Publisher('controller', UInt16MultiArray, queue_size=10)
data_output = UInt16MultiArray()
data_output.data = [0, 0]


def callback(msg):
    rospy.loginfo(msg.data[0])
    data_output.data[0] = msg.data[0]
    data_output.data[1] = msg.data[1]

    pub.publish(data_output)


def motor_control():
    rospy.init_node('motor_control', anonymous=True)
    rospy.Subscriber("roscar_teleop_data_output", UInt16MultiArray, callback)
    pub.publish(data_output)
    rospy.spin()


def main():
    try:
        motor_control()
    except rospy.ROSInterruptException:
        pass


if __name__ == '__main__':
    main()
