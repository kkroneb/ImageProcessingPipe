#include "ProcessImage.h"

using namespace std;

void processImagesInDirectory(const boost::filesystem::path& directory) {
    
    // Check if the directory exists and is a valid directory
    if (!boost::filesystem::exists(directory) || !boost::filesystem::is_directory(directory)) {
        throw runtime_error("Directory does not exist");
        if (!boost::filesystem::exists(directory)) cerr << "Directory not found." << endl;
        else cerr << "Given file is not a directory" << endl;
    }

    // Iterate over each entry (file or subdirectory) in the specified directory
    for (const auto& entry : boost::filesystem::directory_iterator(directory)) {
        // Check if the entry is a regular file and has a supported image extension
        if (boost::filesystem::is_regular_file(entry) && 
            (entry.path().extension() == ".jpg" || entry.path().extension() == ".png")) {
            // Read the image from the entry
            cv::Mat image = readImage(entry.path());
            
            // Apply image processing functions to enhance the image
            image = enhanceContrast(image);
            image = reduceNoise(image);
            image = highlightEdges(image);
            image = quantizeColors(image);
            
            // Save the processed image with a modified filename
            saveImage(image, entry.path().filename().replace_extension("_processed.jpg"));
        }
    }
}


cv::Mat readImage(const boost::filesystem::path& imagePath) {
    return cv::imread(imagePath.string(), cv::IMREAD_COLOR);
}

cv::Mat enhanceContrast(const cv::Mat& image) {
    cv::Mat img_gray;
    cv::cvtColor(image, img_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(img_gray, img_gray);
    return img_gray;
}

cv::Mat reduceNoise(const cv::Mat& image) {
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(5, 5), 0);
    return blurredImage;
}

cv::Mat highlightEdges(const cv::Mat& image) {
    cv::Mat edges;
    cv::Canny(image, edges, 50, 150);
    return edges;
}

cv::Mat quantizeColors(const cv::Mat& image) {
    cv::Mat img_quantized;
    img_quantized = image.clone();
    img_quantized /= 64;
    img_quantized *= 64;
    return img_quantized;
}

void saveImage(const cv::Mat& image, const boost::filesystem::path& outputPath) {
    cv::imwrite(outputPath.string(), image);
}
