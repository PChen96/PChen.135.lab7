/*
  Author:Phillip Chen
  Course: 136
  Instructor: Alex Vikolaev
  Assignment: Lab 7 Task 1
  Description:
    The program reads a PGM image from the file "inImage.pgm",
    and outputs a modified image to "outImage.pgm". 
    Most code are from task 0 (code given),
    inserted code at 108-110 so that it outputs an inverse color image given
  
*/


#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAX_W = 512;
const int MAX_H = 512;

// reads a PGM file.
// Notice that: width and height are passed by reference!
void readImage(int image[MAX_W][MAX_H], int &width, int &height) {
	char c;
	int x;
	ifstream instr;
	instr.open("inImage.pgm");

	// read the header P2
	instr >> c;
	assert(c == 'P');
	instr >> c;
	assert(c == '2');

	// skip the comments (if any)
	while ((instr>>ws).peek() == '#') {
		instr.ignore(4096, '\n');
	}

	instr >> width;
	instr >> height;

	assert(width <= MAX_W);
	assert(height <= MAX_H);
	int max;
	instr >> max;
	assert(max == 255);

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			instr >> image[col][row];
	instr.close();
	return;
}

// Writes a PGM file
void writeImage(int image[MAX_W][MAX_H], int width, int height) {
	ofstream ostr;
	ostr.open("outImage.pgm");
	if (ostr.fail()) {
		cout << "Unable to write file\n";
		exit(1);
	};

	// print the header
	ostr << "P2" << endl;
	// width, height
	ostr << width << ' ';
	ostr << height << endl;
	ostr << 255 << endl;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			assert(image[col][row] < 256);
			assert(image[col][row] >= 0);
			ostr << image[col][row] << ' ';
			// lines should be no longer than 70 characters
			if ((col+1)%16 == 0) ostr << endl;
		}
		ostr << endl;
	}
	ostr.close();
	return;
}

int main() {

	int img[MAX_W][MAX_H];
	int w, h;

	readImage(img, w, h); // read it from the file "inImage.pgm"

	// w and h were passed by reference and now contain the dimensions of the picture
	// and the 2-dimesional array img contains the image data


	// Now we can manipulate the image the way we like

	// for example we copy its contents into a new array
	//white is 255, black is 0
	int out[MAX_W][MAX_H];

	for(int x = 0; x < w; x++) {
		for(int y = 0; y < h; y++) {
			int c = img[x][y];
			c = (c-255)*-1;//we want to change 0 to 255, 255 to 0 and 127 to 128
			out[x][y] = c;//saves changes into a different array
		}
	}

	// and save this new image to file "outImage.pgm"
	writeImage(out, w, h);

}

