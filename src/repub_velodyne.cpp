#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>

#include <sensor_msgs/PointCloud2.h>

#include <pcl/ros/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>




ros::Publisher* pubLaserCloudExtreCurPointer;
ros::Publisher* pubLaserCloudLastPointer;

bool odd_even = true;

void laserCloudHandler(const sensor_msgs::PointCloud2ConstPtr& laserCloudIn2)
{
	sensor_msgs::PointCloud2 laserCloudExtreCur2;
	sensor_msgs::PointCloud2 laserCloudLast2;

	if(odd_even)
	{
		laserCloudExtreCur2 = * laserCloudIn2;
	    laserCloudExtreCur2.header.stamp = ros::Time::now();
	    laserCloudExtreCur2.header.frame_id = "/camera";
	    pubLaserCloudExtreCurPointer->publish(laserCloudExtreCur2);
	    odd_even = false;
	}
	else
	{
	    laserCloudLast2 = * laserCloudIn2;
	    laserCloudLast2.header.stamp = ros::Time::now();
	    laserCloudLast2.header.frame_id = "/camera";
	    pubLaserCloudLastPointer->publish(laserCloudLast2);
	    odd_even = true;
	}

}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Repub_Velodyne");
  ros::NodeHandle nh;

  ros::Subscriber subLaserCloud = nh.subscribe<sensor_msgs::PointCloud2> 
                                  ("/velodyne_points", 20, laserCloudHandler);


  ros::Publisher pubLaserCloudExtreCur = nh.advertise<sensor_msgs::PointCloud2> 
                                         ("/laser_cloud_extre_cur", 2);

  ros::Publisher pubLaserCloudLast = nh.advertise<sensor_msgs::PointCloud2> 
                                     ("/laser_cloud_last", 2);

  pubLaserCloudExtreCurPointer = &pubLaserCloudExtreCur;
  pubLaserCloudLastPointer = &pubLaserCloudLast;

  ros::spin();

  return 0;
}