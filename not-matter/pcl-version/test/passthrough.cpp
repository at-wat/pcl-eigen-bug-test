#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

int main(int argc, char** argv) {
  class Test {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered_;

   public:
    Test()
        : cloud_(new pcl::PointCloud<pcl::PointXYZ>),
          cloud_filtered_(new pcl::PointCloud<pcl::PointXYZ>) {
      cloud_->width = 5;
      cloud_->height = 1;
      cloud_->points.resize(cloud_->width * cloud_->height);

      for (size_t i = 0; i < cloud_->points.size(); ++i) {
        cloud_->points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud_->points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud_->points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
      }
    }
    ~Test() {}  // Dead point
    void run() {
      pcl::PassThrough<pcl::PointXYZ> pass;
      pass.setInputCloud(cloud_);
      pass.setFilterFieldName("z");
      pass.setFilterLimits(0.0, 1.0);
      pass.filter(*cloud_filtered_);
      pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2(
          new pcl::PointCloud<pcl::PointXYZ>);
      cloud2 = cloud_filtered_;  // Dead point
      cloud_filtered_ = cloud_;  // Dead point
    }
  };

  {
    Test a;
    a.run();
  }

  return 0;
}
