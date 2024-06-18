//Description: Photoshop Application that edit images using 15 different filters
//Author 1: Hager Ahmed Mohamed Tantawy 
//Author 2: Mohamed Ayman
//Author 3: Nada Shaaban Abd-El-Rahman
//Author 1 made invert image,rotate image, frame,blur,sunlight, purple,infra-red 
//Author 2 made Grayscale,lighten and darken,merge,image edge detection
//Author 3 made Black and white,flip image,crop image,resize
#include <iostream>
#include "Image_Class.h"
#include <string>
#include <filesystem> // for file system operations
#include <stdexcept> // for std::invalid_argument
#include <algorithm> // for std::min

using namespace std;
namespace fs = std::filesystem;

// Function declarations
void loadImage(Image& image);
void saveImage(Image image);
void applyFilter(Image& image, bool lighten);
void framefilter(Image& image);
void mergeImages();
void detectEdges(Image image);
void blurImage(Image& image);
void purpleFilter(Image& image);
void infraredFilter();
void croppingFilter(Image& image);
void resizeFilter(Image& image);
void sunlightFilter();
void black_white(Image& image);
int flipFilter();
void invertFilter(Image& image);
void rotationFilter();
void grayscaleFilter(Image& image);

void loadImage(Image& image) {
    string filename;
    while (true) {
        try {
            cout << "Enter the filename of the image: ";
            cin >> filename;
            image.loadNewImage(filename);
        }
        catch (const exception &e) {
            continue;
        }
        break;
    }
}

int main() {
    string filename;
    Image image;
    loadImage(image);

    while (true) {
        cout << "MENU:\n";
        cout << "1.Lighten or Darken filter  2.Add frame 3.Merge two images  4.Detect edges filter\n ";
        cout << "5.Blurred filter  6.Purple filter 7.Infrared filter  8.Cropping filter\n";
        cout << " 9.Resize filter  10.Sunlight filter 11.Black & white filter  12.Flipping filter\n";
        cout << " 13.Invert filter  14.Rotation filter  15.Grayscale filter\n";
        cout << " 16.Save current image  17.Exit\n";
        cout << "Enter your choice: ";

        string choice;
        cin >> choice;

        if (choice == "1") {
            applyFilter(image, true); // Lighten
        } else if (choice == "2") {
            framefilter(image);
        } else if (choice == "3") {
            // Load the second image
            Image secondImage;
            loadImage(secondImage);
            mergeImages();
        } else if (choice == "4") {
            detectEdges(image);
        } else if (choice == "5") {
            blurImage(image);
        } else if (choice == "6") {
            purpleFilter(image);
        } else if (choice == "7") {
            infraredFilter();
        } else if (choice == "8") {
            croppingFilter(image);
        } else if (choice == "9") {
            resizeFilter(image);
        } else if (choice == "10") {
            sunlightFilter();
        } else if (choice == "11") {
            black_white(image);
        } else if (choice == "12") {
            flipFilter();
        } else if (choice == "13") {
            invertFilter(image);
        } else if (choice == "14") {
            rotationFilter();
        } else if (choice == "15") {
            grayscaleFilter(image);
        } else if (choice == "16") {
            saveImage(image);
        } else if (choice == "17") {
            // Ask if the user wants to save the current image before exiting
            cout << "Do you want to save the current image before exiting? (yes/no): ";
            string saveChoice;
            cin >> saveChoice;
            if (saveChoice == "yes") {
                saveImage(image);
            }
            break; // Exit the loop
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

enum FlipDirection { Horizontal, Vertical };//defining flip direction image

void flipImage(Image& img, FlipDirection direction) {//function to flip the image
    int width = img.width;
    int height = img.height;
    int channels = img.channels;

    if (direction == Horizontal) {//if the direction is horizontel
        for (int i = 0; i < width / 2; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < channels; ++k) {
                    swap(img(i, j, k), img(width - 1 - i, j, k));
                    //swep pixels for image
                }
            }
        }
    } else { //if the direction is Vertical
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height / 2; ++j) {
                for (int k = 0; k < channels; ++k) {
                    swap(img(i, j, k), img(i, height - 1 - j, k));
                    //swep pixels for image
                }
            }
        }
    }
}

//function to apply the flipping filter
int flipFilter() {
    Image image;
    char choice;
    bool vaildChoice = false;
    do {
        cout << "Choose flip direction: (H for Horizontal, V for Vertical): ";
        cin >> choice;
        FlipDirection direction;
        switch (choice) {
            case 'H':
            case 'h':
                flipImage(image, Horizontal);//flip Horizontal
                vaildChoice = true;
                break;
            case 'V':
            case 'v':
                flipImage(image, Vertical);//flip Vertical
                vaildChoice = true;
                break;
            default:
                cout << "Invalid choice. " << endl;
                break;
        }
    } while (!vaildChoice);
}
void saveImage(Image image) {
    string filename;
    cout << "Enter the filename to save the image with its extension: ";
    cin >> filename;

    int result = image.saveImage(filename);

    if (result == 1) {
        cout << "Image saved successfully." << endl;
    } else {
        cout << "Failed to save the image." << endl;
    }
}

void applyFilter(Image &image, bool lighten) {
    cout << "choose an option" << endl;
    cout << "1. lighten" << endl;
    cout << "2. Darken" << endl;
    int option;
    cin >> option;
    Image new_image(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            switch (option) {
                case 1:
                    for (int k = 0; k < 3; ++k) {
                        // Lighten the pixel by 50%
                        int New_image = image(i, j, k) + (255 - image(i, j, k)) / 2;
                        image(i, j, k) = (New_image > 255) ? 255 : New_image;
                    }
                    break;
                case 2:
                    for (int k = 0; k < 3; ++k) {
                        // Darken the pixel by 50%
                        int New_image = image(i, j, k) / 2;
                        image(i, j, k) = (New_image < 0) ? 0 : New_image;
                    }
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
                    break;
            }
        }
    }
    // Ask if the user wants to save the current image after applying the filter
    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    cin >> saveChoice;
    if (saveChoice == "yes") {
        saveImage(image);
    }
}
// Function to add a simple frame to the image
void addSimpleFrame(Image &image, int frameSize, int frameColorR, int frameColorG, int frameColorB) {

    // Iterating over each pixel in the image
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {

            // Checking if the pixel is on the frame boundary
            if (i < frameSize || i >= image.width - frameSize ||
                j < frameSize || j >= image.height - frameSize) {
                // Setting the frame color for the pixel
                image(i, j, 0) = frameColorR;
                image(i, j, 1) = frameColorG;
                image(i, j, 2) = frameColorB;
            }
        }
    }
}

// Function to add a fancy frame to the image
void addFancyFrame(Image &image) {

    // Setting parameters for the frame
    int frameSize = 10;
    int bigSquareSize = 60;
    int smallSquareSize = 20;

    int frameColorR = 0;
    int frameColorG = 230;
    int frameColorB = 255;

    int bigSquareColorR = 200;
    int bigSquareColorG = 0;
    int bigSquareColorB = 255;

    int smallSquareColorR = 0;
    int smallSquareColorG = 0;
    int smallSquareColorB = 0;

    // Iterating over each pixel in the image
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {

            // Checking if the pixel is on the big square boundary
            if ((i < bigSquareSize && j < bigSquareSize) ||
                (i < bigSquareSize && j >= image.height - bigSquareSize) ||
                (i >= image.width - bigSquareSize && j < bigSquareSize) ||
                (i >= image.width - bigSquareSize && j >= image.height - bigSquareSize)) {

                // Setting the color for the big square
                image(i, j, 0) = bigSquareColorR;
                image(i, j, 1) = bigSquareColorG;
                image(i, j, 2) = bigSquareColorB;
            }
                // Checking if the pixel is on the frame boundary around the big square
            else if ((i < bigSquareSize + frameSize && j < bigSquareSize + frameSize) ||
                     (i < bigSquareSize + frameSize && j >= image.height - bigSquareSize - frameSize) ||
                     (i >= image.width - bigSquareSize - frameSize && j < bigSquareSize + frameSize) ||
                     (i >= image.width - bigSquareSize - frameSize && j >= image.height - bigSquareSize - frameSize)) {
                // Setting the color for the small squares in the frame
                if ((i - bigSquareSize - frameSize) % (smallSquareSize * 2) == 0 ||
                    (j - bigSquareSize - frameSize) % (smallSquareSize * 2) == 0) {
                    image(i, j, 0) = smallSquareColorR;
                    image(i, j, 1) = smallSquareColorG;
                    image(i, j, 2) = smallSquareColorB;
                }
            }
                // Setting the frame color for the rest of the image
            else if (i < frameSize || i >= image.width - frameSize ||
                     j < frameSize || j >= image.height - frameSize) {
                image(i, j, 0) = frameColorR;
                image(i, j, 1) = frameColorG;
                image(i, j, 2) = frameColorB;
            }
        }
    }
}

void framefilter(Image &image) {
    // Main program loop
    while (true) {
        // Displaying menu options
        cout << "Choose an option:\n1. Add simple frame\n2. Add fancy frame\n3. exit\nEnter your choice: ";
        int choice;
        cin >> choice;

        // Processing user choice
        if (choice == 1 || choice == 2) {
            // Adding frame based on user choice
            if (choice == 1) {
                int frameSize = 15;
                int frameColorR, frameColorG, frameColorB;
                cout << "Choose frame color:\n1. Pink\n2. Red\n3. Black\nEnter your choice: ";
                int colorChoice;
                cin >> colorChoice;
                cin.ignore();

                // Setting frame color based on user choice
                if (colorChoice == 1) {
                    frameColorR = 255;
                    frameColorG = 0;
                    frameColorB = 255; // Pink
                } else if (colorChoice == 2) {
                    frameColorR = 255;
                    frameColorG = 0;
                    frameColorB = 0; // Red
                } else if (colorChoice == 3) {
                    frameColorR = 0;
                    frameColorG = 0;
                    frameColorB = 0; // Black
                } else {
                    cout << "Invalid choice, please enter number between (1-3)." << endl;
                    continue; // Return to choosing frame color
                }
                // Adding simple frame to the image
                addSimpleFrame(image, frameSize, frameColorR, frameColorG, frameColorB);
            } else {
                // Adding fancy frame to the image
                addFancyFrame(image);
            }
            // Saving the modified image with a new filename
            cout << "Enter the new file name for the image (including extension): ";
            string newFilename;
            getline(cin, newFilename);

            // Saving the image and providing feedback
            int success = image.saveImage(newFilename);
            if (success == 1) {
                cout << "Image saved successfully." << endl;
            } else {
                cout << "Failed to save image." << endl;
            }
            break;
        } else if (choice == 3) {
            // Exiting the program
            cout << "Exiting program..." << endl;
            break;
        } else {
            // Handling invalid choice
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }
    }

    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    cin >> saveChoice;
    if (saveChoice == "yes") {
        saveImage(image);
    }
}

void mergeImages() {
    string filename, second_image, image_name;
    cout << "Please enter name the second image : ";
    cin >> second_image;

    // Read the images
    Image image1(filename);
    Image image2(second_image);

    // Calculate the common dimensions between the two images
    int common_width = min(image1.width, image2.width);
    int common_height = min(image1.height, image2.height);

    // merge the two image
    Image merged_image(common_width, common_height);
    for (int i = 0; i < common_width; ++i) {
        for (int j = 0; j < common_height; ++j) {
            for (int k = 0; k < image1.channels; ++k) {
                // Calculate the average of the shared values between the two images
                merged_image(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
            }
        }
    }
    // Ask if the user wants to save the current image after applying the filter
    cout << "Do you want to save the current image after merging the two images? (yes/no): ";
    string saveChoice;
    cin >> saveChoice;
    if (saveChoice == "yes") {
        saveImage(merged_image);
    }
}

void detectEdges(Image image) {
    const int sobel_x[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };

    const int sobel_y[3][3] = {
            {-1, -2, -1},
            {0,  0,  0},
            {1,  2,  1}
    };

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image.getPixel(i, j, k);
            }
            avg /= image.channels;
            for (int k = 0; k < image.channels; ++k) {
                image.setPixel(i, j, k, avg);
            }
        }

        Image Edge_image(image.width, image.height);

        const float threshold = 100.0;

        for (int y = 1; y < image.height - 1; ++y) {
            for (int x = 1; x < image.width - 1; ++x) {
                float gx = 0, gy = 0;
                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        unsigned char currentPixel = image.getPixel(x + dx, y + dy, 0);
                        gx += currentPixel * sobel_x[dy + 1][dx + 1];
                        gy += currentPixel * sobel_y[dy + 1][dx + 1];
                    }
                }
                float edgeStrength = sqrt(gx * gx + gy * gy);
                unsigned char edge_value = edgeStrength > threshold ? 0 : 255;
                Edge_image.setPixel(x, y, 0, edge_value);
                Edge_image.setPixel(x, y, 1, edge_value);
                Edge_image.setPixel(x, y, 2, edge_value);
            }
        }
        // Ask if the user wants to save the current image after applying the filter
        cout << "Do you want to save the current image after applying the filter? (yes/no): ";
        string saveChoice;
        cin >> saveChoice;
        if (saveChoice == "yes") {
            saveImage(Edge_image);
        }
    }
}
void blurImage(Image &image) {

    // Define kernel size for blurring
    int kernel_size = 14;

    // Apply Box blur
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {

                int sum = 0;
                int count = 0;

                // Calculate the sum of pixel values in the kernel window
                for (int x = -kernel_size; x <= kernel_size; x++) {
                    for (int y = -kernel_size; y <= kernel_size; y++) {
                        if (i + x >= 0 && i + x < image.width && j + y >= 0 && j + y < image.height) {
                            sum += image(i + x, j + y, k);
                            count++;
                        }
                    }
                }
                // Calculate the average value of the pixels in the kernel window
                int average = sum / count;
                // Set the pixel value to the average value
                image(i, j, k) = average;
            }
        }
    }
    // Ask if the user wants to save the current image after applying the filter
    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    getline(cin, saveChoice);
    if (saveChoice == "yes") {
        saveImage(image);
    }
}
void purpleFilter(Image& image) {
    // Loop through each pixel of the image and modify the red channel only
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                // Scaling the green channel value by multiplying with 0.88
                image(i, j, 1) *= 0.88;
            }
        }
    }
    // Ask if the user wants to save the current image after applying the filter
    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    getline(cin, saveChoice);
    if (saveChoice == "yes") {
        saveImage(image);
    }
}

void infraredFilter() {
    string filename;
    Image image;

    cin >> filename;
    // Loop through each pixel of the image and modify the channels
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                if (k == 0) {
                    // Set red channel to maximum value (255)
                    image(i, j, k) = 255;
                } else {
                    // Invert other channels by subtracting from maximum value (255)
                    image(i, j, k) = 255 - image(i, j, k);
                }
            }
        }
    }
    // Ask if the user wants to save the current image after applying the filter
    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    cin >> saveChoice;
    if (saveChoice == "yes") {
        saveImage(image);
    }
}

void croppingFilter(Image &image) {
    int x, y, w, h;
    cout << "Enter the starting point (x y) and dimensions (W H) to crop (e.g., x y W H): ";
    cin >> x >> y >> w >> h;

    if (x + w > image.width || y + h > image.height || x < 0 || y < 0 || w <= 0 || h <= 0) {
        cout << "Invalid dimensions. Please enter valid dimensions within the bounds of the original image."
             << endl;
    }

    Image cropped(w, h);

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            cropped(i, j, 0) = image(x + i, y + j, 0);
            cropped(i, j, 1) = image(x + i, y + j, 1);
            cropped(i, j, 2) = image(x + i, y + j, 2);
        }
    }
    // Ask if the user wants to save the current image after applying the filter
    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    cin >> saveChoice;
    if (saveChoice == "yes") {
        saveImage(cropped);
    }
}
void resizeFilter(Image &image) {

    int newWidth, newHeight;
    cout<< "Enter the new dimensions (width height) or the ratio of reduction/increase (e.g., 0.5 for 50% reduction): ";
    cin >> newWidth >> newHeight;

    // Calculate new dimensions if ratio is provided
    if (newWidth < 1 && newHeight < 1) {
        newWidth = image.width * newWidth;
        newHeight = image.height * newHeight;
    }

    // Create a new image with the calculated dimensions
    Image resized(newWidth, newHeight);

    // Resize the image by copying pixels
    for (int i = 0; i < newWidth; i++) {
        for (int j = 0; j < newHeight; j++) {
            int origX = i * image.width / newWidth;
            int origY = j * image.height / newHeight;
            resized(i, j, 0) = image(origX, origY, 0);
            resized(i, j, 1) = image(origX, origY, 1);
            resized(i, j, 2) = image(origX, origY, 2);
        }
    }
    // Ask if the user wants to save the current image after applying the filter
    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    cin >> saveChoice;
    if (saveChoice == "yes") {
        saveImage(resized);
    }
}
void sunlightFilter() {
    string filename;
    Image image;
    cout << "Enter the filename of the image: " << endl;
    cin >> filename;

    image.loadNewImage(filename);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {

            image(i, j, 2) -= image(i, j, 2) * 0.34;

        }
    }
    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    cin >> saveChoice;
    if (saveChoice == "yes") {
        saveImage(image);
    }

}

void black_white(Image &image) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned char average = 0;
            for (int k = 0; k < image.channels; k++) {
                average += image(i, j, k);
            }
            average /= image.channels;
            for (int k = 0; k < image.channels; k++) {
                image(i, j, k) = average;
            }
        }
    }
    // Ask if the user wants to save the current image after applying the filter
    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    getline(cin, saveChoice);
    if (saveChoice == "yes") {
        saveImage(image);
    }
}
void invertFilter(Image &image) {
    // Loop through each pixel of the image and invert its color
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                // Invert the color by subtracting each channel value from 255
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    // Ask if the user wants to save the current image after applying the filter
    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    cin >> saveChoice;
    if (saveChoice == "yes") {
        saveImage(image);
    }
}
void rotationFilter() {
    string filename;
    Image image;

    while(true){
        try  {
            cout << "Enter the filename of the image: " << endl;
            cin >> filename;

            image.loadNewImage(filename);//loading the image

        } catch (const exception& e) {
            continue;
        }
        break;
    }


    Image rotated(image.height, image.width);

    int degree;
    bool validDegree = false;
    do {
        cout << "Enter rotation degree (90 , 180, or 270)";
        cin >> degree;
        if (degree == 90) {// rotate the image by 90 deg
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    rotated(image.height - 1 - j, i, 0) = image(i, j, 0);
                    rotated(image.height - 1 - j, i, 1) = image(i, j, 1);
                    rotated(image.height - 1 - j, i, 2) = image(i, j, 2);
                }
            }
            validDegree = true;
        } else if (degree == 180) {// rotate the image by 180 deg
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    rotated(image.height - 1 - j, i, 0) = image(i, j, 0);
                    rotated(image.height - 1 - j, i, 1) = image(i, j, 1);
                    rotated(image.height - 1 - j, i, 2) = image(i, j, 2);
                }
            }
            Image rotated2(image.width, image.height);
            for (int i = 0; i < rotated.width; i++) {
                for (int j = 0; j < rotated.height; j++) {
                    rotated2(rotated.height - 1 - j, i, 0) = rotated(i, j, 0);
                    rotated2(rotated.height - 1 - j, i, 1) = rotated(i, j, 1);
                    rotated2(rotated.height - 1 - j, i, 2) = rotated(i, j, 2);
                }
            }
            cout << "pls enter name of image to store \n";
            cout << "enter your extension you make.jpg, .bmp, .png, .tga:";
            string newfilename;
            cin >> newfilename;
            int x = rotated2.saveImage(newfilename);
            if (x == 1) {
                cout << "rotated2 saved successfully";
            } else {
                cout << " Failed to save rotated2";
            }
            validDegree = true;
        } else if (degree == 270) {// rotate the image by 270 deg
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    rotated(j, image.width - 1 - i, 0) = image(i, j, 0);
                    rotated(j, image.width - 1 - i, 1) = image(i, j, 1);
                    rotated(j, image.width - 1 - i, 2) = image(i, j, 2);
                }
            }
            validDegree = true;
        } else {
            cout << "invalid degree, please enter a valid one" << endl;
        }
    } while (!validDegree);

    if (degree == 90 || degree == 270){
        cout<< "pls enter image name to store new image \n";
        cout << "and specify extension .jpg, .png, .bmp, .tga:";
        string newfilename;
        cin >> newfilename;
        int x = rotated.saveImage(newfilename);//saving the rotated image
        if (x==1){
            cout <<"rotated2 saved successfully";
        }else {
            cout <<"failed to save ";
        }


    }

}

void grayscaleFilter(Image &image) {
    // Loop through each pixel of the image and convert it to grayscale
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0;;

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }

            avg /= 3; // Calculate average

            // Set all channels to the average value
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }

    // Ask if the user wants to save the current image after applying the filter
    cout << "Do you want to save the current image after applying the filter? (yes/no): ";
    string saveChoice;
    cin >> saveChoice;
    if (saveChoice == "yes") {
        saveImage(image);
    }
}