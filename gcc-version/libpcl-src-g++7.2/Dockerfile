FROM ubuntu:bionic

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get -qq update \
  && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    cmake \
    git-core \
    libboost-all-dev \
    libeigen3-dev \
    libflann-dev \
    libgl-dev \
    libgtest-dev \
    make \
    wget \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# downgrade g++ to 7.2
RUN cd /tmp \
  && wget https://launchpad.net/ubuntu/+source/gcc-7/7.2.0-16ubuntu1/+build/13734243/+files/g++-7_7.2.0-16ubuntu1_amd64.deb \
  && wget https://launchpad.net/ubuntu/+source/gcc-7/7.2.0-16ubuntu1/+build/13734243/+files/libstdc++-7-doc_7.2.0-16ubuntu1_all.deb \
  && wget https://launchpad.net/ubuntu/+source/gcc-7/7.2.0-16ubuntu1/+build/13734243/+files/gcc-7-base_7.2.0-16ubuntu1_amd64.deb \
  && wget http://lug.mtu.edu/ubuntu/pool/main/m/mpfr4/libmpfr4_3.1.6-1_amd64.deb \
  && wget https://launchpad.net/ubuntu/+source/gcc-7/7.2.0-16ubuntu1/+build/13734243/+files/libstdc++-7-dev_7.2.0-16ubuntu1_amd64.deb \
  && wget https://launchpad.net/ubuntu/+source/gcc-7/7.2.0-16ubuntu1/+build/13734243/+files/libgcc-7-dev_7.2.0-16ubuntu1_amd64.deb \
  && wget https://launchpad.net/ubuntu/+source/gcc-7/7.2.0-16ubuntu1/+build/13734243/+files/libgcc1_7.2.0-16ubuntu1_amd64.deb \
  && wget https://launchpad.net/ubuntu/+source/gcc-7/7.2.0-16ubuntu1/+build/13734243/+files/gcc-7_7.2.0-16ubuntu1_amd64.deb \
  && wget https://launchpad.net/ubuntu/+source/gcc-7/7.2.0-16ubuntu1/+build/13734243/+files/cpp-7_7.2.0-16ubuntu1_amd64.deb \
  && wget http://th.archive.ubuntu.com/ubuntu/pool/universe/i/isl-0.18/libisl15_0.18-4_amd64.deb \
  && dpkg -i gcc-7-base_7.2.0-16ubuntu1_amd64.deb \
  && dpkg -i libmpfr4_3.1.6-1_amd64.deb \
  && dpkg -i libgcc1_7.2.0-16ubuntu1_amd64.deb \
  && dpkg -i libgcc-7-dev_7.2.0-16ubuntu1_amd64.deb \
  && dpkg -i libstdc++-7-dev_7.2.0-16ubuntu1_amd64.deb \
  && dpkg -i libisl15_0.18-4_amd64.deb \
  && dpkg -i cpp-7_7.2.0-16ubuntu1_amd64.deb \
  && dpkg -i gcc-7_7.2.0-16ubuntu1_amd64.deb \
  && dpkg -i g++-7_7.2.0-16ubuntu1_amd64.deb \
  && rm *.deb

# clone debian/1.8.1+dfsg1-2 version of pcl
# build options are from https://launchpadlibrarian.net/343176867/buildlog_ubuntu-bionic-amd64.pcl_1.8.1+dfsg1-2ubuntu2_BUILDING.txt.gz
RUN cd /tmp \
  && git clone -b debian/1.8.1+dfsg1-2 --depth=1 https://salsa.debian.org/science-team/pcl.git \
  && mkdir -p pcl/build && cd pcl/build \
  && cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_BUILD_TYPE=None -DCMAKE_INSTALL_SYSCONFDIR=/etc -DCMAKE_INSTALL_LOCALSTATEDIR=/var -DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON -DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON -DLIB_INSTALL_DIR:STRING=lib/x86_64-linux-gnu -DCMAKE_SKIP_RPATH=ON -DBUILD_TESTS=OFF -DBUILD_apps=ON -DBUILD_common=ON -DBUILD_examples=ON -DBUILD_features=ON -DBUILD_filters=ON -DBUILD_geometry=ON -DBUILD_global_tests=OFF -DBUILD_io=ON -DBUILD_kdtree=ON -DBUILD_keypoints=ON -DBUILD_octree=ON -DBUILD_registration=ON -DBUILD_sample_consensus=ON -DBUILD_search=ON -DBUILD_segmentation=ON -DBUILD_surface=ON -DBUILD_tools=ON -DBUILD_tracking=ON -DBUILD_visualization=ON -DBUILD_apps_cloud_composer=OFF -DBUILD_apps_modeler=ON -DBUILD_apps_point_cloud_editor=ON -DBUILD_apps_in_hand_scanner=ON -DWITH_DOCS=ON \
  && make -j && make install && rm -rf /tmp/pcl

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
