FROM ubuntu:bionic

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get -qq update \
  && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    cmake \
    libpcl-dev \
    make \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /work

# build pcl tutorial code http://pointclouds.org/documentation/tutorials/passthrough.php
RUN echo '#include <iostream>\
#include <pcl/point_types.h>\
#include <pcl/filters/passthrough.h>\
\
int\
 main (int argc, char** argv)\
{\
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);\
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);\
\
  // Fill in the cloud data\
  cloud->width  = 5;\
  cloud->height = 1;\
  cloud->points.resize (cloud->width * cloud->height);\
\
  for (size_t i = 0; i < cloud->points.size (); ++i)\
  {\
    cloud->points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);\
    cloud->points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);\
    cloud->points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);\
  }\
\
  std::cerr << "Cloud before filtering: " << std::endl;\
  for (size_t i = 0; i < cloud->points.size (); ++i)\
    std::cerr << "    " << cloud->points[i].x << " " \
                        << cloud->points[i].y << " " \
                        << cloud->points[i].z << std::endl;\
\
  // Create the filtering object\
  pcl::PassThrough<pcl::PointXYZ> pass;\
  pass.setInputCloud (cloud);\
  pass.setFilterFieldName ("z");\
  pass.setFilterLimits (0.0, 1.0);\
  //pass.setFilterLimitsNegative (true);\
  pass.filter (*cloud_filtered);\
\
  std::cerr << "Cloud after filtering: " << std::endl;\
  for (size_t i = 0; i < cloud_filtered->points.size (); ++i)\
    std::cerr << "    " << cloud_filtered->points[i].x << " " \
                        << cloud_filtered->points[i].y << " " \
                        << cloud_filtered->points[i].z << std::endl;\
\
  return (0);\
}' > passthrough.cpp

RUN echo 'cmake_minimum_required(VERSION 2.8 FATAL_ERROR)\n\
\n\
project(passthrough)\n\
\n\
find_package(PCL 1.2 REQUIRED)\n\
\n\
include_directories(${PCL_INCLUDE_DIRS})\n\
link_directories(${PCL_LIBRARY_DIRS})\n\
add_definitions(${PCL_DEFINITIONS})\n\
\n\
add_executable (passthrough passthrough.cpp)\n\
target_link_libraries (passthrough ${PCL_LIBRARIES})' > CMakeLists.txt

RUN mkdir build && cd build && cmake .. && make

# run it
ENTRYPOINT ["bash", "-c"]
CMD ["'/work/build/passthrough && echo No error || eval echo Error $?'"]
