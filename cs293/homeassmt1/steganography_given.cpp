/*
 * This is a template file to be used for assignment.
 * General instructions:
 * 1.Do not remove any included library file/namespace declaration.You can add more you need.
 * 2.Use function void yourCode(CImg<unsigned char>& sourceImage,int option,string &text)
 *  as a starting point to add your code.You may add more functions/classes etc if you need.
 * 3.Do not change main function.
 * 4.Use following commands to install necessary libs:
 * 		sudo apt-get install xorg-dev
 * 		sudo apt-get install imagemagick
 * 5.While compiling the code add -lpthread and -lX11.So your target will look like
 * 		g++ steganography.cpp  -lX11 -lpthread
 * 6.Help Page : http://cimg.sourceforge.net/
 * 7.Do not save image as jpeg.
 */

#include <iostream>
#include <string>
#include <bitset>
using namespace std;

#include "CImg.h"
using namespace cimg_library;

/*
 * Starting point for your code.
 * Source Image file is now loaded in variable sourceImage
*/
void yourCode(CImg<unsigned char>& sourceImage,char option,string &text){

	/*
	 ----------------------------------------------------------------------
	 This is sample code to show some of the operations you may need to do.
	 ----------------------------------------------------------------------
	 We get height, width and number of channels from the image.
	 What are channels?
	 check here : http://www.imagemagick.org/Usage/color_basics/
	*/
	int imageHeight = sourceImage.height();
	int imageWidth = sourceImage.width();
	int imageDepth = sourceImage.depth();
	int imageChannels = sourceImage.spectrum();

	cout << "Image Height : " 	<< imageHeight 		<<endl;
	cout << "Image Width : "  	<< imageWidth   	<<endl;
	cout << "Image Depth : " 	<< imageDepth	 	<<endl;
	cout << "Image Channels : " << imageChannels 	<<endl;


	//Lets access pixel (100,100,0) of image.
	//Our image has 3 channels : R,G,B with indices 0,1,2
	bitset<8> rComponent = sourceImage(100,100,0,0);
	bitset<8> gComponent = sourceImage(100,100,0,1);
	bitset<8> bComponent = sourceImage(100,100,0,2);

	cout << "Original Red Colour value :" << rComponent << endl;
	cout << "Original Green Colour value :" << gComponent << endl;
	cout << "Original Blue Colour value :" << bComponent << endl;


    /*
     You can perform above operation by using bitwise operators as well.
     For e.g. to set last 2 bits to 1 we will or rComponent by 00000011 i.e. 3 */
	sourceImage(100,100,0,0) |=16;
     

    //read r component again and print it, lets see if it is as expected 

    rComponent = sourceImage(100,100,0,0);

    cout << "Changed Red Colour value :" << rComponent << endl;

    //Now lets draw horizontal blue line halfway through the image
    for(int i = 0 ; i < imageHeight  ; i++)
    {
    	sourceImage(imageWidth/2,i,0,0) = 0;
    	sourceImage(imageWidth/2,i,0,1) = 0;
    	sourceImage(imageWidth/2,i,0,2) = 255;
    }

}

/*
 * Reads user input from console.Do not edit.
 */
void getUserInput(string& imageSource, string& filename, char& option) {
	cout << "Enter e for encrypt, d for decrypt :" << endl;
	cin >> option;
	cout << "Enter Image File Name" << endl;
	cin >> imageSource;
	if(option == 'e'){
		cout << "Enter file name of the message to be encrypted:" << endl;
		
	}
	else
	  cout << "Enter  name of file into which decrypted message will be written:" << endl; 

	cin >> filename;
}



int main() {
	string imageSource;
	string textFile;
	char option;

	// Read the source image 
	getUserInput(imageSource, textFile, option);

	
	CImg<unsigned char> sourceImage(imageSource.c_str());


	yourCode(sourceImage,option,textFile);

	if(option == 'e')
		sourceImage.save(imageSource.append("_encrypted.png").c_str());
	else
	  cout << "Decryption" << endl;
	return 0;
}

