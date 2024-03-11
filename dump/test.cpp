#include <opencv4/opencv2/opencv.hpp>
#include<vector>

using namespace cv;

int main() {
  // Read the image
  Mat image = imread("../images/image.jpg");

  // Convert the image to grayscale
  Mat gray_image;
  cvtColor(image, gray_image, COLOR_BGR2GRAY);

  // Create a vector to store the image data
  std::vector<uchar> image_data;
  imencode(".jpg", gray_image, image_data);

  // Send the image data to the CLI
  std::cout << image_data << std::endl;

  return 0;
}