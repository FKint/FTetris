#include "FTetrisCube.h"

FTetrisCube::FTetrisCube(FColor *color, FVertex *position, float width, float height, float xrot, float yrot, float zrot, bool d3, bool texture, unsigned int textureid, bool selectable):FGLDrawObject(color,position, xrot, yrot, zrot, true, selectable, 0, 0, 0)
{
	this->width = width;
	this->height = height;
	this->texture = texture;
	this->textureid = textureid;
	this->d3 = d3;
}

FTetrisCube::~FTetrisCube(void)
{
}
void FTetrisCube::InternDraw(bool standalone){
	glPushMatrix();
		if(texture)
			glBindTexture(GL_TEXTURE_2D, textureid);
		glBegin(GL_QUADS);
			if(texture)
				glTexCoord2d(0, 0);
			glVertex3f(0, 0, 0);//FRONT
			if(texture)
				glTexCoord2d(1, 0);
			glVertex3f(this->width, 0, 0);
			if(texture)
				glTexCoord2d(1, 1);
			glVertex3f(this->width, -this->height, 0);
			if(texture)
				glTexCoord2d(0, 1);
			glVertex3f(0, -this->height, 0);
			
		//3D
			if(d3){
				float depth = width < height?-width:-height;
				
				if(texture)
					glTexCoord2d(1, 0);
				glVertex3f(0, 0, 0);//LEFT
				if(texture)
					glTexCoord2d(0, 0);
				glVertex3f(0, 0, depth);
				if(texture)
					glTexCoord2d(0, 1);
				glVertex3f(0, -this->height, depth);
				if(texture)
					glTexCoord2d(1, 1);
				glVertex3f(0, -this->height, 0);
				
				if(texture)
					glTexCoord2d(0, 0);
				glVertex3f(this->width, 0, 0);//RIGHT
				if(texture)
					glTexCoord2d(1, 0);
				glVertex3f(this->width, 0, depth);
				if(texture)
					glTexCoord2d(1, 1);
				glVertex3f(this->width, -this->height, depth);
				if(texture)
					glTexCoord2d(0, 1);
				glVertex3f(this->width, -this->height, 0);
				
				if(texture)
					glTexCoord2d(0, 1);
				glVertex3f(0, 0, 0);//TOP
				if(texture)
					glTexCoord2d(0, 0);
				glVertex3f(0, 0, depth);
				if(texture)
					glTexCoord2d(1, 0);
				glVertex3f(this->width, 0, depth);
				if(texture)
					glTexCoord2d(1, 1);
				glVertex3f(this->width, 0, 0);
				
				if(texture)
					glTexCoord2d(0, 0);
				glVertex3f(0, -this->height, 0);//BOTTOM
				if(texture)
					glTexCoord2d(0, 1);
				glVertex3f(0, -this->height, depth);
				if(texture)
					glTexCoord2d(1, 1);
				glVertex3f(this->width, -this->height, depth);
				if(texture)
					glTexCoord2d(1, 0);
				glVertex3f(this->width, -this->height, 0);

				if(texture)
					glTexCoord2d(1, 0);
				glVertex3f(0, 0, depth);//BACK
				if(texture)
					glTexCoord2d(1, 1);
				glVertex3f(0, -this->height, depth);
				if(texture)
					glTexCoord2d(0, 1);
				glVertex3f(this->width, -this->height, depth);
				if(texture)
					glTexCoord2d(0, 0);
				glVertex3f(this->width, 0, depth);
			}
		//end of 3D
		glEnd();
	glPopMatrix();
}