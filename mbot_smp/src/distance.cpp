#include <ros/ros.h>
#include <ros/console.h>
#include <std_msgs/Bool.h>
#include <geometry_msgs/Point32.h>
#include <sensor_msgs/LaserScan.h>

class Distance{
public:
  Distance():
  nh("~")
  {
    sub_scan = nh.subscribe("/scan", 20, &Distance::scan_cb, this);
    pub_dis  = nh.advertise<geometry_msgs::Point32>("dis", 20);
  }

  void scan_cb(const sensor_msgs::LaserScan scan){
    geometry_msgs::Point32 dis;

	//x : left tire, y : right tire
	if(scan.ranges[384]>=0.01 && scan.ranges[384]<=0.5){
		dis.x=scan.ranges[384]*800;
		dis.y=scan.ranges[384]*800;
	}

	pub_dis.publish(dis);

  }

private:
  ros::NodeHandle nh;
  ros::Subscriber sub_scan;
  ros::Publisher pub_dis;

};

// run as
// rosrun bs_start urg_bumpber /urg_bumper/scan:=/scan /urg_bumper/cmd_vel:=/ypspur/cmd_vel
int main(int argc, char** argv){
  std::cout << "Build:" << __DATE__ << " " << __TIME__ << std::endl;
  ros::init(argc, argv, "distance");
  Distance distance;

  while(ros::ok()){
	ros::spinOnce();
  }

  return 0;
}
