#ifdef __APPLE__
#include <OpenGL/gl3.h>         /// remove the "3" for OpenGL versions < 3
#include <OpenGL/gl3ext.h>      /// ditto
#else 
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <Handler/Window/Window.h>
#include <Handler/Handler.h>

Sping::Window::Window(Handler &handler) :
	handler(handler)
{
	// TODO: multithreading doesnt work when initting window :(
	this->init();
}

Sping::Window::~Window()
{
	SDL_GL_DeleteContext(this->glContext);
	SDL_DestroyWindow(this->window);
}

void Sping::Window::init()
{
	// TODO: proper read from settings (after it has initialized of course)

	this->window = SDL_CreateWindow("Wololo", 100, 100, 1280, 720, SDL_WINDOW_OPENGL);
	if (this->window == nullptr)
	{
		throw Sping::Err::OH_BOY;
	}
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	this->glContext = SDL_GL_CreateContext(this->window);

	glewExperimental = GL_TRUE;
	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		throw Sping::Err::OH_BOY;
	}

	// TODO: no magic numbers pls
	glViewport(0, 0, 1280, 720);

	Sping::debugLog("Initialized the window!");
}
