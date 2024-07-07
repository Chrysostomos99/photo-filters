#include <string>
#include <iostream>
#include <fstream>
#include "ppm.h"

using namespace std;

namespace imaging {

	float * ReadPPM(const char * filename, int * w, int * h) {
		string type; //Stores format of ppm image ex. P6, P3
		unsigned int maxValuePixel; //Should belong in (0,255]
		char newLineChar; //Stores \n

		//Opens an existing ppm image
		ifstream imageFile(filename, ios::binary);

		if (!imageFile) { //If file cannot open
			cerr << "Cannot open image file!" << endl;
			return nullptr;
		}

		imageFile >> type >> *w >> *h >> maxValuePixel >> newLineChar; //Starts reading header until \n char

		if (type != "P6") { //If the format isn't P6 stop operation
			cerr << "Unsupported format! Only P6 format is supported.";
			return nullptr;
		}

		if (*w == 0) { //if the width doesn't exit then *w == 0 and operation must stop
			cerr << "Invalid image width!";
			return nullptr;
		}

		if (*h == 0) { //if the height doesn't exit then *h == 0 and operation must stop
			cerr << "Invalid image height!";
			return nullptr;
		}

		if ((maxValuePixel == 0) || (maxValuePixel > 255)) { //if max pixel values is out of bounds, operation must stop
			cerr << "Invalid value of the colour components for the pixels!";
			return nullptr;
		}


		unsigned char  *RGB1 = new unsigned char[3 * *w * *h];
		float  *RGB = new float[3 * *w * *h]; //Stores the rgb values
 
		imageFile.read(reinterpret_cast<char *>(RGB1), 3 * *w * *h); //reads the rgb values (NOT IN FLOAT YET)

		for (unsigned int i = 0; i < 3 * *w * *h; i++) { //cast thr char rgb values into float and into [0.0, 1.0]
			RGB[i] = (float)RGB1[i] / 255.0f;
		}

		delete[] RGB1;

		imageFile.close();

		return RGB; //return float array
	}

	bool WritePPM(const float * data, int w, int h, const char * filename) {

		//If there in no data to write into the ppm file the operation is cancelled
		if (data == nullptr) {
			cerr << "There is no data to write!" << endl;
			return false;
		}

		//Creat and open a ppm file for the negative image
		ofstream imageFile(filename, ios::binary);

		if (!imageFile) { //If the file cannot open cancel operation
			cerr << "Could not open image!" << endl;
			return false;
		}

		//if file can open
		imageFile << "P6" << endl << w << endl << h << endl << "255\n" << endl; //Create header
		for (unsigned int i = 0; i < 3 * w * h; i++) { //Cast data into char and write them into the new file
			unsigned int k = data[i] * 255;
			imageFile.write(reinterpret_cast<const char *>(&k), 1);
		}

		imageFile.close();

		return true;
	}
}