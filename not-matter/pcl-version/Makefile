VERSION_GOOD := pcl-1.7.2
VERSION_BAD  := pcl-1.8.1
MAKE_PATH    := $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))

.PHONY: init test

init:
	git clone https://github.com/PointCloudLibrary/pcl.git

test:
	cd pcl; git bisect start
	cd pcl; git bisect good $(VERSION_GOOD)
	cd pcl; git bisect bad $(VERSION_BAD)
	cd pcl; git bisect run $(MAKE_PATH)/check.sh
	cd pcl; git bisect view
