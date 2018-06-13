VERSION_GOOD := 39901cd248cadd283378dd2e9881e201de679f96
VERSION_BAD  := master
MAKE_PATH    := $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))

.PHONY: init test

init:
	git clone https://github.com/PointCloudLibrary/pcl.git

test:
	cd pcl; git bisect start $(VERSION_BAD) $(VERSION_GOOD)
	cd pcl; git bisect run $(MAKE_PATH)/check.sh
