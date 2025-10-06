#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Loading blurred face image;
    Mat img = imread("test.JPG");
    if (img.empty()) {
        cerr << "Error: Could not load image!" << endl;
        return -1;
    }

    // Resize for display;
    int newWidth = 400;
    int newHeight = (img.rows * newWidth) / img.cols;
    Mat imgResized;
    resize(img, imgResized, Size(newWidth, newHeight));

    // -------------------------
    // Step 1: Edge Detection (Laplacian);
    // -------------------------
    Mat gray, edges;
    cvtColor(imgResized, gray, COLOR_BGR2GRAY);
    Laplacian(gray, edges, CV_16S, 3);
    convertScaleAbs(edges, edges);

    // Create a mask where edges are strong;
    Mat edgeMask;
    threshold(edges, edgeMask, 30, 255, THRESH_BINARY);

    // -------------------------
    // Step 2: Multi-pass Unsharp Masking on edges;
    // -------------------------
    Mat enhanced = imgResized.clone();
    for(int i = 0; i < 5; i++) {
        Mat blurred;
        GaussianBlur(enhanced, blurred, Size(0,0), 3);
        Mat sharpened;
        addWeighted(enhanced, 1.5, blurred, -0.5, 0, sharpened);
        // Apply only on edges;
        sharpened.copyTo(enhanced, edgeMask);
    }

    // -------------------------
    // Step 3: CLAHE (Contrast Enhancement);
    // -------------------------
    Mat lab;
    cvtColor(enhanced, lab, COLOR_BGR2Lab);
    vector<Mat> lab_planes(3);
    split(lab, lab_planes);

    Ptr<CLAHE> clahe = createCLAHE();
    clahe->setClipLimit(2.0);
    clahe->apply(lab_planes[0], lab_planes[0]);

    merge(lab_planes, lab);
    Mat finalImg;
    cvtColor(lab, finalImg, COLOR_Lab2BGR);

    // -------------------------
    // Show results side by side;
    // -------------------------
    Mat combined(imgResized.rows, imgResized.cols*2, imgResized.type());
    imgResized.copyTo(combined(Rect(0,0,imgResized.cols,imgResized.rows)));
    finalImg.copyTo(combined(Rect(imgResized.cols,0,finalImg.cols,finalImg.rows)));

    imshow("Original (Left) | Enhanced (Right)", combined);
    imwrite("face_edge_enhanced.jpg", finalImg);
    imwrite("face_comparison_edge.jpg", combined);

    waitKey(0);
    return 0;
}
