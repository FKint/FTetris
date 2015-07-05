#include "FGameUI.h"
#include "resource.h"

FGameUI *globalUI = NULL;
LRESULT CALLBACK ForwardWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	
	return globalUI->FGameWndProc(hWnd, uMsg, wParam, lParam);
}

FGameUI::FGameUI(FGame *game, char* className, char* title, int width, int height, int x, int y, int bits, bool fullscreenflag)
{
	glinitialized = false;
	globalUI = this;
	this->shown = false;
	this->className=className;
	this->title = title;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->bits = bits;
	this->fullscreen = fullscreenflag;
	this->WndProc = ForwardWndProc;
	this->game = game;
	scene = 0;
}

FGameUI::~FGameUI(void)
{
	KillWindow();
	if(this->scene != 0)
		delete this->scene;
	if(this->className != 0)
		delete [] className;
	if(this->title != 0)
		delete [] title;
}
bool FGameUI::KillWindow(){
	if(shown){
		bool success = true;
		if(fullscreen){
			ChangeDisplaySettings(0, 0);
			ShowCursor(true);
		}
		if(mHDC && !ReleaseDC(mHWND, mHDC)){
			MessageBox(0, "releasedc(globalHWND, globalHDC) failed", "error", 0);
			mHDC = 0;
		}
		if(mHWND && !DestroyWindow(mHWND)){
			MessageBox(0, "destroywindow(globalHWND) failed", "error", 0);
			mHWND = NULL;
		}
		if(!UnregisterClass(className, mHINSTANCE)){
			MessageBox(0, "unregisterclass(classname, globalHInstance) failed", "error", 0);
			mHINSTANCE = 0;
		}
		if(mHRC){
			if(!wglMakeCurrent(0, 0)){
				MessageBox(0, "wglmakecurrent(null, null) failed", "error", 0);
				success = false;
			}
			if(!wglDeleteContext(mHRC)){
				MessageBox(0, "wgldeletecontext(globalHRC) failed", "error", 0);
				success = false;
			}
			mHRC = 0;
		}
		this->shown = false;
		return success;
	}else{
		return false;
	}
}
bool FGameUI::Show(){
	if(shown){
		this->KillWindow();
	}
	if(!shown){
		unsigned int PixelFormat;
		WNDCLASSEX wc;
		DWORD dwExStyle;
		DWORD dwStyle;
		RECT WindowRect;

		WindowRect.left = (long)x;
		WindowRect.right = (long)(width + x);
		WindowRect.top = (long)y;
		WindowRect.bottom = (long)(height + y);

		mHINSTANCE = GetModuleHandle(NULL);

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = (WNDPROC)WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = mHINSTANCE;
		wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = className;
		wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);

		if(!RegisterClassEx(&wc)){
			MessageBox(NULL, "RegisterClassEx(&wc) failed", "error", NULL);
			return FALSE;
		}

		if(fullscreen){
			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = width;
			dmScreenSettings.dmPelsHeight = height;
			dmScreenSettings.dmBitsPerPel = bits;
			dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL){
			
				if(MessageBox(0, "Fullscreen not supported by your video card, try windowed mode instead?", "error", MB_YESNO | MB_ICONEXCLAMATION) == IDYES){
					fullscreen = false;
				}else{
					MessageBox(0, "Program will now close", "error", 0);
					game->Exit();
					return false;
				}
			}else{
				MessageBox(0, "fullscreen succeed", "", 0);
			}
		}
		if(fullscreen){
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP;
			WindowRect.left=0;
			WindowRect.right = width;
			WindowRect.top = 0;
			WindowRect.bottom = height;
		}else{
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW;
		}
		

		AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle);

		if(!(this->mHWND = CreateWindowEx(dwExStyle, wc.lpszClassName, title, dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WindowRect.left, WindowRect.top, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, NULL, NULL, mHINSTANCE, NULL))){
			KillWindow();
			MessageBox(0, "Error at window creation", "error", 0);
			return false;
		}
		

		static PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),
			1, 
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA,
			bits,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0, 
			0, 0, 0
		};

		if(!(mHDC = GetDC(mHWND))){
			KillWindow();
			MessageBox(0, "Error at getting mHDC", "error", 0);
			return false;
		}
		if(!(PixelFormat = ChoosePixelFormat(mHDC, &pfd))){
			KillWindow();
			MessageBox(0, "Error at choosing pixelformat", "error", 0);
			return false;
		}
		if(!SetPixelFormat(mHDC, PixelFormat, &pfd)){
			KillWindow();
			MessageBox(0, "Error at setting pixelformat", "error", 0);
			return false;
		}
		if(!(mHRC = wglCreateContext(mHDC))){
			KillWindow();
			MessageBox(0, "Error at creating hrc", "error", 0);
			return false;
		}
		if(!wglMakeCurrent(mHDC, mHRC)){
			KillWindow();
			MessageBox(0, "Error at making mHDC and hrc current", "error", 0);
			return false;
		}
		ShowWindow(mHWND, SW_SHOW);
		SetForegroundWindow(mHWND);
		SetFocus(mHWND);
		
		ReSizeGLScene(width, height);
		if(!(InitGL())){
			KillWindow();
			MessageBox(NULL, "Initialization of GL failed", "error", NULL);
			return FALSE;
		}
		this->shown = true;
		this->SetActive(true);
		return true;
	}else{
		return false;
	}
}
bool FGameUI::SetFullScreen(bool fullscreenflag){
	if(this->fullscreen != fullscreenflag){
		this->KillWindow();
		this->fullscreen = fullscreenflag;
		if(!this->Show()){
			this->fullscreen = !fullscreenflag;
			return false;
		}
	}
	return true;
}
bool FGameUI::DrawScene(){
	if(this->GetActive()){
		wglMakeCurrent(this->mHDC, this->mHRC);
		glRenderMode(GL_RENDER);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);

		this->SpecificDraw();
		glMatrixMode(GL_MODELVIEW);
		SwapBuffers(this->mHDC);
	}
	return true;
}
void FGameUI::ReSizeGLScene(int width, int height){
	if(height == 0)
		height = 1;
	glViewport(0, 0, width, height);
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (float)width/(float)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
bool FGameUI::InitGL(bool reset){
	if(!glinitialized || reset){
		glClearColor(0.4f, 0.4f, 0.9f, 0.5f);
		//glClearColor(1.0, 1.0, 1.0, 1.0);
		glClearDepth(1.0f);

		glShadeModel(GL_SMOOTH);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_BLEND);

		glEnable(GL_TEXTURE_2D);
		glinitialized = true;
	}
	return true;	
}
void FGameUI::Update(){
	if(scene != 0)
		this->scene->Action();
	this->DrawScene();
}
void FGameUI::SpecificDraw(){
	if(scene != 0)
		scene->Draw();
}
void FGameUI::SetScene(FScene *newscene){
	wglMakeCurrent(this->mHDC, this->mHRC);
	if(this->scene != 0){
		
		delete this->scene;
	}
	this->scene = newscene;
	if(scene != 0)
		this->scene->Start();
}
LRESULT CALLBACK FGameUI::FGameWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	if(this->scene){
		this->scene->EventHandler(uMsg, wParam, lParam);
	}
	switch(uMsg){
		case WM_CLOSE:
			PostQuitMessage(0);
			this->game->Exit();
			return 0;
		case WM_ACTIVATE:
			if(!HIWORD(wParam)){
				this->SetActive(true);
			}else{
				this->SetActive(false);
			}
			return 0;
		case WM_SYSCOMMAND:
			switch(wParam){
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			}
			break;
		case WM_SIZE:
			this->ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));
			return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}