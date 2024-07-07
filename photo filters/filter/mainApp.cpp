#include <iostream>
#include "Image.h"
#include "Array.h"
#include "Filter.h"
#include "FilterLinear.h"
#include "FilterGamma.h"
#include "Vec3.h"
#include <string>

using namespace std;
using namespace imaging;
using namespace math;

int main(int argc, char *argv[]) {

	string args;

	if (argc == 1) { // if argument list is empty: ask for the file name
		cout << "> filter ";
		getline(cin, args); //reads the arguments from the user and stores them in args
		
	} 
	
	vector<string> arguments = vector<string>();
	unsigned int j = 0;
	for (unsigned int i=0; i <= args.length(); i++) {
		if (isspace(args[i]) || i == args.length()){ //until you find a space char or you reach the end of the string
			arguments.push_back(args.substr(j, i-j)); //put the argument into the vector
			j = ++i; //the char after the space char
		}
	}

	string filename = arguments.back(); //last object in vector is the image name

	Image myImage = Image();
	
	string format;
	for (unsigned int i = filename.length() - 3; i < filename.length(); i++) { //stores in format the string after '.'
		format = format + filename[i]; 
	}

	bool flag;
	flag = myImage.load(filename, format);
	if (!flag) { //if load operation has failed
		cout << "Load operation failed!" << endl;
		system("PAUSE");
		return 0;
	}

	if (arguments.at(0) != "-f") { //if a filter doesn't exist in the arguments
		cerr << "Filter not found!" << endl;
		system("PAUSE");
		return 0;
	}

	cout << "Image dimensions are: " << myImage.getWidth() << " x " << myImage.getHeight() << endl;

	unsigned int p = 0;
	while (p <= arguments.size() - 1) { //for each element in the vector
		if (arguments.at(p) == "gamma") { //if the filter is gamma
			p++; // after the position of gamma in vector there's the y value
			float y = stof(arguments.at(p));
			FilterGamma gamma(y); 
			myImage = gamma << myImage; 
		}

		if (arguments.at(p) == "linear") { //if the filter is linear
			p++; // after the position of linear in vector there's the 1st value of a
			//values of a
			float r1 = stof(arguments.at(p)); p++;
			float g1 = stof(arguments.at(p)); p++;
			float b1 = stof(arguments.at(p)); p++;
			//values of c
			float r2 = stof(arguments.at(p)); p++;
			float g2 = stof(arguments.at(p)); p++;
			float b2 = stof(arguments.at(p));
			Vec3<float> a = Vec3<float>(r1, g1, b1);
			Vec3<float> c = Vec3<float>(r2, g2, b2);
			FilterLinear linear = FilterLinear(a, c);
			myImage = linear << myImage;
		}

		p++;
	}


	filename = "filtered_" + filename; //creates name for negative image file
	flag = myImage.save(filename, format);
	if (!flag) { //if save operation has failed
		cout << "Save operation failed!" << endl;
		system("PAUSE");
		return 0;
	}

	system("PAUSE");

	return 0;
}