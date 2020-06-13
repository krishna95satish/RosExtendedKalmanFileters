# RosExtendedKalmanFileters

Please follow these below mentioned setps to run this code,

1.  Create a new folder and name it "InputFiles" in your local cloned folder.
2.  Copy paste the SensorData.csv file into the above created folder.
3.  Create an empty folder and name it as "ROSBagFiles" and leave it blank(it will be automatically populated once you run the code)
4.  Perform catkin_make and wait till the completion.
5.  Source your code by typing the following command "source devel/setup.bash"
6.  Run the rosbag creator code by typing "rosrun extendedkalmanfilters RosBagCreator", you should see the bag files created in the "ROSBagFiles" folder
7.  Open the includes folder and find GlobalConsts.h file and find "gLidarNodeFile" and "gRadarNodeFile" variables and put in the absoulte path of the generated bag files
8.  Perform catkkin_make again
9.  Navigate to tha launch file located inside the "src/extendedkalmanfilters/launch" 
10. Perform the following command to run the code "roslaunch SensorFusion.launch"
11. You can open another terminal and source your code and echo the published message to look for RMS error getting published.


Thank you :)