//#include "ftextureloader.h"
#ifndef FTEXTURELOADER_CPP
#define FTEXTURELOADER_CPP
#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>
#include "ftextureloader.h"


namespace FOpenGL{
	//only for 24 bpp bitmaps
	int FLoadGLTextures(GLuint *textures, char *filenames[], GLint parameter[][3], int amount){//paramters:magfilter, minfilter, type (FGL_IMAGE_2D || FGL_MIPMAP_2D)
		int successful = 0;
		for(int i = 0; i < amount; i++){
			BYTE * data;
			FILE * file;
			BITMAPFILEHEADER header;
			BITMAPINFOHEADER bitmapinfoheader;
			fopen_s(&file, filenames[i], "r");
			if(file == NULL){
				continue;
			}
			fread(&header, sizeof(BITMAPFILEHEADER), 1, file);
			if(!(header.bfType == BITMAP_ID)){
				fclose(file);
				continue;
			}
			fread(&bitmapinfoheader, sizeof(BITMAPINFOHEADER), 1, file);
			
			if(bitmapinfoheader.biSizeImage == 0){
				bitmapinfoheader.biSizeImage = bitmapinfoheader.biWidth * bitmapinfoheader.biHeight * 3;
			}
			fseek(file, header.bfOffBits, SEEK_SET);
			data = (BYTE *)malloc(bitmapinfoheader.biSizeImage);
			if(!data){
				free(data);
				fclose(file);
				continue;
			}
			fread(data, bitmapinfoheader.biSizeImage, 1, file);

			if(data == 0){
				fclose(file);
				continue;
			}
			
			BYTE tmpcolor = 0;
			for(int index = 0; index < (int)bitmapinfoheader.biSizeImage; index += 3){
				
				tmpcolor = data[index];
				data[index] = data[index + 2];
				data[index + 2] = tmpcolor;
			}
			
			fclose(file);
			int imgwidth = bitmapinfoheader.biWidth;
			int imgheight = bitmapinfoheader.biHeight;
			glGenTextures(1, &textures[i]);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, parameter[i][0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, parameter[i][1]);
			switch(parameter[i][2]){
				case FGL_MIPMAP_2D:
					gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imgwidth, imgheight, GL_RGB, GL_UNSIGNED_BYTE, data);
					break;
				case FGL_IMAGE_2D:
				default:
					glTexImage2D(GL_TEXTURE_2D, 0, 3, imgwidth, imgheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			}
		
			if(data){
				free(data);
				successful ++;
			}

		}
		return successful;
	}
}
#endif
