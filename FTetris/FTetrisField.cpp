#include "FTetrisField.h"

FTetrisField::FTetrisField(int rows, int cols, FColor *color, FVertex *position, float width, float height, float scale, bool d3, float xrot, float yrot, float zrot):FGLDrawObject(color, new FVertex(position->GetX() * scale, position->GetY() * scale, position->GetZ()), xrot, yrot, zrot, true, false, 0, 0, 0)
{
	this->rows = rows;
	this->cols = cols;
	this->height = height;
	this->width = width;
	this->scale = scale;
	this->border = .015;
	this->startx = -GetTotalWidth() / 2;
	this->starty = GetTotalHeight() / 2;
	delete position;
	this->d3 = d3;
}

FTetrisField::~FTetrisField(void)
{
}
void FTetrisField::InternDraw(bool standalone){
	glPushMatrix();
		glTranslatef(startx, starty, 0);
		DrawCubes();
		float depth = this->GetBoxWidth()<this->GetBoxHeight()?-this->GetBoxWidth():-this->GetBoxHeight();
		if(color)
			glColor4f(this->color->GetR() * 1.5, this->color->GetG() * 1.5,/* this->color->GetB() * 1.5*/1, this->color->GetA());
		else
			MessageBox(0, "no color in ftetrisfield", "", 0);
		glPushMatrix();
		
			/*if(d3){
				glBegin(GL_QUADS);
			}else{
				glBegin(GL_LINES);
			}*/
			glBegin(GL_QUADS);
			for(int i = 1; i < rows; i ++){
				glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, 0);//FRONT
				glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, 0);
				glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, 0);
				glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, 0);

				if(d3){
					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, depth);//BACK
					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, depth);
					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, depth);
					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, depth);
					
					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, depth);//LEFT
					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, 0);
					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, 0);
					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, depth);

					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, 0);//RIGHT
					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, depth);
					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, depth);
					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, 0);

					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, depth);//TOP
					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, depth);
					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, 0);
					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() + GetBorder() / 2, 0);

					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, 0);//BOTTOM
					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, 0);
					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, depth);
					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight() - GetBorder() / 2, depth);
				}

				/*glVertex3f(0, (float)i / (float)rows * -GetTotalHeight(), 0);
				glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight(), 0);
				if(d3){
					glVertex3f(GetTotalWidth(), (float)i / (float)rows * -GetTotalHeight(), depth);
					glVertex3f(0, (float)i / (float)rows * -GetTotalHeight(), depth);
				}*/
			}
			for(int i = 1; i < cols; i ++){
				glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, 0, 0);//FRONT
				glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, 0, 0);
				glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, -GetTotalHeight(), 0);
				glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, -GetTotalHeight(), 0);

				if(d3){
					glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, 0, depth);//BACK
					glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, 0, depth);
					glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, -GetTotalHeight(), depth);
					glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, -GetTotalHeight(), depth);

					glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, 0, depth);//LEFT
					glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, 0, 0);
					glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, -GetTotalHeight(), 0);
					glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, -GetTotalHeight(), depth);

					glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, 0, 0);//RIGHT
					glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, 0, depth);
					glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, -GetTotalHeight(), depth);
					glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, -GetTotalHeight(), 0);

					glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, 0, depth);//TOP
					glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, 0, depth);
					glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, 0, 0);
					glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, 0, 0);

					glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, -GetTotalHeight(), 0);
					glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, -GetTotalHeight(), 0);
					glVertex3f((float)i / (float)cols * GetTotalWidth() + GetBorder() / 2, -GetTotalHeight(), depth);
					glVertex3f((float)i / (float)cols * GetTotalWidth() - GetBorder() / 2, -GetTotalHeight(), depth);
				}
				/*glVertex3f((float)i / (float)cols * width * scale, 0, 0);
				glVertex3f((float)i / (float)cols * width * scale, - height * scale, 0);					
				if(d3){
					glVertex3f((float)i / (float)cols * width * scale, - height * scale, depth);
					glVertex3f((float)i / (float)cols * width * scale, 0, depth);
				}*/
			}
			glEnd();
		glPopMatrix();
		if(color)
			glColor4f(this->color->GetR(), this->color->GetG(), this->color->GetB(), this->color->GetA());
		glBegin(GL_QUADS);
			glVertex3f(-GetBorder() / 2, GetBorder() / 2, 0);//LEFTFRONT
			glVertex3f(GetBorder() / 2, GetBorder() / 2, 0);
			glVertex3f(GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);
			glVertex3f(-GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);
			
			glVertex3f(-GetBorder() / 2, GetBorder() / 2, 0);//TOPFRONT
			glVertex3f(GetTotalWidth() + GetBorder() / 2, GetBorder() / 2, 0);
			glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetBorder() / 2, 0);
			glVertex3f(-GetBorder() / 2, -GetBorder() / 2, 0);

			glVertex3f(GetTotalWidth() - GetBorder() / 2, GetBorder() / 2, 0);//RIGHTFRONT
			glVertex3f(GetTotalWidth() + GetBorder() / 2, GetBorder() / 2, 0);
			glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);
			glVertex3f(GetTotalWidth() - GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);

			glVertex3f(-GetBorder() / 2, -GetTotalHeight() + GetBorder() / 2, 0);//BOTTOM
			glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() + GetBorder() / 2, 0);
			glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);
			glVertex3f(-GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);

			if(d3){
				glVertex3f(-GetBorder() / 2, GetBorder() / 2, depth);//LEFTLEFT
				glVertex3f(-GetBorder() / 2, GetBorder() / 2, 0);
				glVertex3f(-GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);
				glVertex3f(-GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);

				glVertex3f(GetBorder() / 2, GetBorder() / 2, 0);//LEFTRIGHT
				glVertex3f(GetBorder() / 2, GetBorder() / 2, depth);
				glVertex3f(GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);
				glVertex3f(GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);

				glVertex3f(GetBorder() / 2, GetBorder() / 2, depth);//LEFTBACK
				glVertex3f(-GetBorder() / 2, GetBorder() / 2, depth);
				glVertex3f(-GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);
				glVertex3f(GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);
				
				glVertex3f(-GetBorder() / 2, GetBorder() / 2, depth);//TOPTOP
				glVertex3f(GetTotalWidth() + GetBorder() / 2, GetBorder() / 2, depth);
				glVertex3f(GetTotalWidth() + GetBorder() / 2, GetBorder() / 2, 0);
				glVertex3f(-GetBorder() / 2, GetBorder() / 2, 0);

				glVertex3f(-GetBorder() / 2, -GetBorder() / 2, 0);//TOPBOTTOM
				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetBorder() / 2, 0);
				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetBorder() / 2, depth);
				glVertex3f(-GetBorder() / 2, -GetBorder() / 2, depth);

				glVertex3f(GetTotalWidth() + GetBorder() / 2, GetBorder() / 2, depth);//TOPBACK
				glVertex3f(-GetBorder() / 2, GetBorder() / 2, depth);
				glVertex3f(-GetBorder() / 2, -GetBorder() / 2, depth);
				glVertex3f(GetTotalWidth() + GetBorder() / 2, - GetBorder() / 2, depth);

				glVertex3f(GetTotalWidth() + GetBorder() / 2, GetBorder() / 2, 0);//RIGHTRIGHT
				glVertex3f(GetTotalWidth() + GetBorder() / 2, GetBorder() / 2, depth);
				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);
				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);

				glVertex3f(GetTotalWidth() - GetBorder() / 2, GetBorder() / 2, depth);//RIGHTLEFT
				glVertex3f(GetTotalWidth() - GetBorder() / 2, GetBorder() / 2, 0);
				glVertex3f(GetTotalWidth() - GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);
				glVertex3f(GetTotalWidth() - GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);

				glVertex3f(GetTotalWidth() + GetBorder() / 2, GetBorder() / 2, depth);//RIGHTBACK
				glVertex3f(GetTotalWidth() - GetBorder() / 2, GetBorder() / 2, depth);
				glVertex3f(GetTotalWidth() - GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);
				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);

				glVertex3f(-GetBorder() / 2, -GetTotalHeight() + GetBorder() / 2, depth);//BOTTOMTOP
				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() + GetBorder() / 2, depth);
				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() + GetBorder() / 2, 0);
				glVertex3f(-GetBorder() / 2, -GetTotalHeight() + GetBorder() / 2, 0);

				glVertex3f(-GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);//BOTTOMBOTTOM
				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, 0);
				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);
				glVertex3f(-GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);

				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() + GetBorder() / 2, depth);//BOTTOMBACK
				glVertex3f(-GetBorder() / 2, -GetTotalHeight() + GetBorder() / 2, depth);
				glVertex3f(-GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);
				glVertex3f(GetTotalWidth() + GetBorder() / 2, -GetTotalHeight() - GetBorder() / 2, depth);

			}
		glEnd();
		/*if(d3){
			glBegin(GL_QUADS);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, depth);
			glVertex3f(GetTotalWidth(), 0, depth);
			glVertex3f(GetTotalWidth(), 0, 0);

			glVertex3f(0, 0, 0);
			glVertex3f(0, -GetTotalHeight(), 0);
			glVertex3f(0, -GetTotalHeight(), depth);
			glVertex3f(0, 0, depth);

			glVertex3f(0, -GetTotalHeight(), 0);
			glVertex3f(GetTotalWidth(), -GetTotalHeight(), 0);
			glVertex3f(GetTotalWidth(), -GetTotalHeight(), depth);
			glVertex3f(0, -GetTotalHeight(), depth);

			glVertex3f(GetTotalWidth(), 0, 0);
			glVertex3f(GetTotalWidth(), 0, depth);
			glVertex3f(GetTotalWidth(), -GetTotalHeight(), depth);
			glVertex3f(GetTotalWidth(), -GetTotalHeight(), 0);
		}else{
			glBegin(GL_LINE_LOOP);
			glVertex3f(0, 0, 0);
			glVertex3f(width * scale, 0, 0);
			glVertex3f(width * scale, - height * scale, 0);
			glVertex3f(0, - height * scale, 0);
		}*/
		//glEnd();
	glPopMatrix();
}
void FTetrisField::SetCols(int cols){
	this->cols = cols;
}
void FTetrisField::SetRows(int rows){
	this->rows = rows;
}