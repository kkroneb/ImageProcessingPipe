// Include Guard: Verhindert mehrfache Einbindung der Header-Datei
#ifndef PROCESSIMAGE_H
#define PROCESSIMAGE_H

// Libraries
#include <opencv2/opencv.hpp>  
#include <boost/filesystem.hpp>
#include <opencv2/imgproc/imgproc.hpp>


/// FUNCTIONS ///

// Controller-Function: processes all images in given directory
void processImagesInDirectory(const boost::filesystem::path& directory);

// read image and return as a matrix
cv::Mat readImage(const boost::filesystem::path& imagePath);

// enhance contrast
cv::Mat enhanceContrast(const cv::Mat& image);

// reduce noise
cv::Mat reduceNoise(const cv::Mat& image);

// color quantization (reducing the number of colors)
cv::Mat quantizeColors(const cv::Mat& image);

// save file
void saveImage(const cv::Mat& image, const boost::filesystem::path& outputPath);


// end of include guard
#endif //PROCESSIMAGE_H
