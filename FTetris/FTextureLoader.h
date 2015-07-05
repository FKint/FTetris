#define BITMAP_ID 0x4D42//for loading bitmaps
#define FGL_IMAGE_2D 0
#define FGL_MIPMAP_2D 1

namespace FOpenGL{
	int FLoadGLTextures(GLuint *textures, char *filenames[], GLint parameter[][3], int amount);
}