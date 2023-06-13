#include "../include/ProcessImage.h"

using namespace std;

void processImagesInDirectory(const boost::filesystem::path& directory) {

    // Check if the directory exists and is a valid directory
    if (!boost::filesystem::exists(directory) || !boost::filesystem::is_directory(directory)) {
        throw runtime_error("Directory does not exist!");
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
            
            // execute several processing functions
            image = enhanceContrast(image);
            image = reduceNoise(image);
            image = quantizeColors(image);
            
            // define output directory
            boost::filesystem::path outputDir("output");

            // does output directory exist? - if not --> create
            if (!boost::filesystem::exists(outputDir)) boost::filesystem::create_directory(outputDir);

            // Save the processed image with a modified filename in output directory
            boost::filesystem::path outputFilePath = outputDir / entry.path().filename().replace_extension("_processed.jpg");
            saveImage(image, outputFilePath);
        }
    }
}

// read image and return as a matrix
cv::Mat readImage(const boost::filesystem::path& imagePath) {
    return cv::imread(imagePath.string(), cv::IMREAD_COLOR);
}

// enhance contrast
cv::Mat enhanceContrast(const cv::Mat& image) {
    cv::Mat img_gray;
    cv::cvtColor(image, img_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(img_gray, img_gray);
    return img_gray;
}

// reduce noise
cv::Mat reduceNoise(const cv::Mat& image) {
    cv::Mat blurredImage;
    cv::GaussianBlur(image, blurredImage, cv::Size(5, 5), 0);
    return blurredImage;
}


cv::Mat quantizeColors(const cv::Mat& image) {

    cv::Mat img_quantized = image.clone();
    // Divide & multiply with 64, quantizing the colors --> round
    img_quantized /= 64;
    img_quantized *= 64;
    // Return the quantized image
    return img_quantized;
}


void saveImage(const cv::Mat& image, const boost::filesystem::path& outputPath) {
    cv::imwrite(outputPath.string(), image);
}
