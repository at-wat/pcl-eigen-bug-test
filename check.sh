#!/bin/bash

set -e

dir=$(dirname $0)

cd $dir/pcl
rm -rf build || true
mkdir -p build
cd build

cmake .. -DWITH_LIBUSB=OFF -DWITH_PNG=OFF -DWITH_QHULL=OFF -DWITH_CUDA=OFF -DWITH_VTK=OFF -DWITH_PCAP=OFF -DWITH_OPENGL=OFF -DBUILD_io=OFF -DBUILD_2d=OFF -DBUILD_geometry=OFF -DBUILD_features=OFF -DBUILD_ml=OFF -DBUILD_segmentation=OFF -DBUILD_surface=OFF -DBUILD_registration=OFF -DBUILD_keypoints=OFF -DBUILD_tracking=OFF -DBUILD_recognition=OFF -DBUILD_stereo=OFF -DBUILD_tools=OFF -DBUILD_filters=ON

make -j
make install

cd $dir/test
rm -rf build
mkdir -p build
cd build
cmake ..
make

exec passthrough
