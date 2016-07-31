/*
 * This is a simple Steganography encryption and decryption program.
 */

#include <iostream>
#include <string>
#include <bitset>
#include <cstring>
#include <cmath>
#include <fstream>
using namespace std;

#include "CImg.h"
using namespace cimg_library;

/* Source Image file is now loaded in variable sourceImage,
   option for Encryption/Decryption in variable option
   and file name in variable text. */                                                                             
void Stego(CImg<unsigned char>& sourceImage,char option,string &text){       

 
	int imageHeight = sourceImage.height();                       // We get height, width, depth and number of channels from the image.
	int imageWidth = sourceImage.width();
	int imageDepth = sourceImage.depth();
	int imageChannels = sourceImage.spectrum();        
        
	cout << "Image Height : "   << imageHeight 	<<endl;
	cout << "Image Width : "    << imageWidth   	<<endl;
	cout << "Image Depth : "    << imageDepth	<<endl;
	cout << "Image Channels : " << imageChannels 	<<endl;

	                                                              // Our image has 3 channels : R,G,B with indices 0,1,2.
	bitset<8> rComponent;
	bitset<8> gComponent;
	bitset<8> bComponent;


 if (option == 'e')
  {
         int hAscii;                                                   // hAscii is the ASCII value of charcter to be hidden.
         bitset<8> hBinary;                                            // hBinary is the binary representation of hAscii.
         char hLetter;                                                 // hLetter is the character to be hidden.
         ifstream filein(text.c_str());
         int i = 0;
         int j = 0;


       if (filein.is_open())
  	{

	 
    			while ( filein.good() )
    			{
     			  hLetter = filein.get();                      // get character from file
                          if (j==imageHeight)
                           {j=0;i++;}
    			  if (filein.good() && i < imageWidth && j < imageHeight)
      			    { hAscii = hLetter;
      
              		        for (int x=0;x<8;x++)                   //This is the code for coverting an askii value to its binary form.
	       		        {hBinary[x]=0;}
              		        for (int x=0;x<8;x++)
               		         { if (hAscii != 0)
                  	           { hBinary[x] = hAscii % 2;
                     	             hAscii = hAscii / 2;
                  	           }  
               		         }
              		        
                  rComponent = sourceImage(i,j,0,0);                   // Here we put the original R, G, B values at (i,j)
                  gComponent = sourceImage(i,j,0,1);                   // in rComponent, gComponent and bComponent.
		  bComponent = sourceImage(i,j,0,2);
                


/* Following part replaces the rComponent's last 3 bits with hBinary's first 3 bits and makes 
   respective changes in sourceImage pixel at (i,j)
   by using Bitwise XOR(^) operator.*/


          if ( rComponent[2]==0 && rComponent[1]==0 && rComponent[0]==1)
             { 
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=0;}
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=1;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=2;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=3;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=4;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=5;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=6;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=7;}
             }

          if ( rComponent[2]==0 && rComponent[1]==0 && rComponent[0]==0)
             { 
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=1;}
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=0;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=3;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=2;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=5;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=4;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=7;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=6;}
             }

          if ( rComponent[2]==0 && rComponent[1]==1 && rComponent[0]==1)
             { 
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=2;}
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=3;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=0;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=1;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=6;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=7;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=4;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=5;}
             }

          if ( rComponent[2]==0 && rComponent[1]==1 && rComponent[0]==0)
             { 
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=3;}
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=2;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=1;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=0;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=7;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=6;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=5;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=4;}
             }

          if ( rComponent[2]==1 && rComponent[1]==0 && rComponent[0]==1)
             { 
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=4;}
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=5;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=6;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=7;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=0;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=1;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=2;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=3;}
             }

          if ( rComponent[2]==1 && rComponent[1]==0 && rComponent[0]==0)
             { 
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=5;}
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=4;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=7;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=6;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=1;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=0;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=3;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=2;}
             }

          if ( rComponent[2]==1 && rComponent[1]==1 && rComponent[0]==1)
             { 
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=6;}
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=7;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=4;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=5;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=2;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=3;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=0;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=1;}
             }

          if ( rComponent[2]==1 && rComponent[1]==1 && rComponent[0]==0)
             { 
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=7;}
                 if ( hBinary[7]==0 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=6;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=5;}
                 if ( hBinary[7]==0 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=4;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=3;}
                 if ( hBinary[7]==1 && hBinary[6]==0 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=2;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==1)
                        {sourceImage(i,j,0,0)^=1;}
                 if ( hBinary[7]==1 && hBinary[6]==1 && hBinary[5]==0)
                        {sourceImage(i,j,0,0)^=0;}
             }


/* Following part replaces the gComponent's last 3 bits with hBinary's next 3 bits and makes 
   respective changes in sourceImage pixel at (i,j)
   by using Bitwise XOR(^) operator.*/

          if ( gComponent[2]==0 && gComponent[1]==0 && gComponent[0]==1)
             { 
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=0;}
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=1;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=2;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=3;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=4;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=5;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=6;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=7;}
             }

          if ( gComponent[2]==0 && gComponent[1]==0 && gComponent[0]==0)
             { 
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=1;}
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=0;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=3;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=2;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=5;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=4;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=7;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=6;}
             }

          if ( gComponent[2]==0 && gComponent[1]==1 && gComponent[0]==1)
             { 
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=2;}
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=3;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=0;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=1;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=6;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=7;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=4;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=5;}
             }

          if ( gComponent[2]==0 && gComponent[1]==1 && gComponent[0]==0)
             { 
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=3;}
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=2;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=1;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=0;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=7;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=6;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=5;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=4;}
             }

          if ( gComponent[2]==1 && gComponent[1]==0 && gComponent[0]==1)
             { 
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=4;}
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=5;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=6;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=7;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=0;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=1;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=2;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=3;}
             }

          if ( gComponent[2]==1 && gComponent[1]==0 && gComponent[0]==0)
             { 
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=5;}
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=4;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=7;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=6;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=1;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=0;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=3;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=2;}
             }

          if ( gComponent[2]==1 && gComponent[1]==1 && gComponent[0]==1)
             { 
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=6;}
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=7;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=4;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=5;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=2;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=3;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=0;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=1;}
             }

          if ( gComponent[2]==1 && gComponent[1]==1 && gComponent[0]==0)
             { 
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=7;}
                 if ( hBinary[4]==0 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=6;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=5;}
                 if ( hBinary[4]==0 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=4;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=3;}
                 if ( hBinary[4]==1 && hBinary[3]==0 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=2;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==1)
                        {sourceImage(i,j,0,1)^=1;}
                 if ( hBinary[4]==1 && hBinary[3]==1 && hBinary[2]==0)
                        {sourceImage(i,j,0,1)^=0;}
             }

/* Following part replaces the bComponent's last 2 bits with hBinary's last 2 bits and makes 
   respective changes in sourceImage pixel at (i,j)
   by using Bitwise XOR(^) operator.*/

          if ( bComponent[1]==1 && bComponent[0]==1)
             {
                 if ( hBinary[1]==0 && hBinary[0]==0)
                        {sourceImage(i,j,0,2)^=3;}
                 if ( hBinary[1]==0 && hBinary[0]==1)
                        {sourceImage(i,j,0,2)^=2;}
                 if ( hBinary[1]==1 && hBinary[0]==0)
                        {sourceImage(i,j,0,2)^=1;}
                 if ( hBinary[1]==1 && hBinary[0]==1)
                        {sourceImage(i,j,0,2)^=0;}
             }

          if ( bComponent[1]==1 && bComponent[0]==0)
             {
                 if ( hBinary[1]==0 && hBinary[0]==0)
                        {sourceImage(i,j,0,2)^=2;}
                 if ( hBinary[1]==0 && hBinary[0]==1)
                        {sourceImage(i,j,0,2)^=3;}
                 if ( hBinary[1]==1 && hBinary[0]==0)
                        {sourceImage(i,j,0,2)^=0;}
                 if ( hBinary[1]==1 && hBinary[0]==1)
                        {sourceImage(i,j,0,2)^=1;}
             }

          if ( bComponent[1]==0 && bComponent[0]==1)
             {
                 if ( hBinary[1]==0 && hBinary[0]==0)
                        {sourceImage(i,j,0,2)^=1;}
                 if ( hBinary[1]==0 && hBinary[0]==1)
                        {sourceImage(i,j,0,2)^=0;}
                 if ( hBinary[1]==1 && hBinary[0]==0)
                        {sourceImage(i,j,0,2)^=3;}
                 if ( hBinary[1]==1 && hBinary[0]==1)
                        {sourceImage(i,j,0,2)^=2;}
             }

          if ( bComponent[1]==0 && bComponent[0]==0)
             {
                 if ( hBinary[1]==0 && hBinary[0]==0)
                        {sourceImage(i,j,0,2)^=0;}
                 if ( hBinary[1]==0 && hBinary[0]==1)
                        {sourceImage(i,j,0,2)^=1;}
                 if ( hBinary[1]==1 && hBinary[0]==0)
                        {sourceImage(i,j,0,2)^=2;}
                 if ( hBinary[1]==1 && hBinary[0]==1)
                        {sourceImage(i,j,0,2)^=3;}
             }

                  rComponent = sourceImage(i,j,0,0);                             // Here we put the changed R, G, B values at (i,j)
                  gComponent = sourceImage(i,j,0,1);                             // in rComponent, gComponent and bComponent
                  bComponent = sourceImage(i,j,0,2);                             // by reading them from sourceImage.


                             j++;
                            }
  			}
                  sourceImage(i,j,0,0)^=sourceImage(i,j,0,0);            // This appends a null character at the end of file
                  sourceImage(i,j,0,1)^=sourceImage(i,j,0,1);            //  which is later used to detect the end of file in
                  sourceImage(i,j,0,2)^=sourceImage(i,j,0,2);            //  Decryption.
                  filein.close();
            
        }
      else cout << "Unable to open file"; 

  }

 else if (option == 'd')
  {
         bitset<8> sBinary;                                              // sBinary is the binary representation of sAskii.
         char sLetter;                                                   //  sLetter is the character to be derypted/shown.
         ofstream fileout;
         fileout.open (text.c_str());
         int y = 0;                                                      // (y,z) represents the image coordinate.
         int z = 0;


      if (fileout.is_open())
  	{
          
    			while ( fileout.good() )
    			{

                          if (z==imageHeight)
                           {z=0;y++;}
    			  if (fileout.good() && y < imageWidth && z < imageHeight)
      			    { rComponent = sourceImage(y,z,0,0);
                              gComponent = sourceImage(y,z,0,1);
		              bComponent = sourceImage(y,z,0,2);

       
        			sBinary[7]=rComponent[2];
        			sBinary[6]=rComponent[1];
        			sBinary[5]=rComponent[0];
        			sBinary[4]=gComponent[2];
       			        sBinary[3]=gComponent[1];
        			sBinary[2]=gComponent[0];
        			sBinary[1]=bComponent[1];
        			sBinary[0]=bComponent[0];   
        			
       				 int sAscii=0;
       				 for (int t=0;t<8;t++)
        			 {sAscii+=(sBinary[t]*pow(2,t));                       //sAscii is the ASCII value of sLetter
          			 }                                                     //derived from sBinary.
        			
         			 sLetter=sAscii;
                                if (sLetter=='\0')
                                {fileout.close();}
                                else
       				{fileout<< sLetter;
                                
                                z++;}
                               
                            }
  			}
                        fileout.close();
            
        }
      else cout << "Unable to open file"; 

  }

}

/*
 * Reads user input from console.
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

        // Handles the encryption-decryption 
	Stego(sourceImage,option,textFile);

	if(option == 'e')
		{sourceImage.save(imageSource.append("_encrypted.png").c_str());
                 cout << "Encryption done!"<<endl;
                }
	else if(option =='d')
	        cout << "Decryption done!" << endl;
        else
                cout << "Invalid Input"<<endl;
	return 0;
}

