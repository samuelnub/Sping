#include <Util/GLEWInclude.h>

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
	int32_t windowFlags = SDL_WINDOW_OPENGL;
	if (this->handler.settings->get(Sping::SettingCategory::WINDOW, "Fullscreen").b)
	{
		windowFlags = windowFlags | SDL_WINDOW_FULLSCREEN;
	}
	if (this->handler.settings->get(Sping::SettingCategory::WINDOW, "Borderless").b)
	{
		windowFlags = windowFlags | SDL_WINDOW_BORDERLESS;
	}

	this->window = SDL_CreateWindow(
		this->handler.settings->get(Sping::SettingCategory::WINDOW, "Name").s.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->handler.settings->get(Sping::SettingCategory::WINDOW, "Width").i,
		this->handler.settings->get(Sping::SettingCategory::WINDOW, "Height").i,
		windowFlags);
	if (this->window == nullptr)
	{
		throw Sping::Err::WINDOW;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, this->handler.settings->get(Sping::SettingCategory::WINDOW, "GLMajorVer").i);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, this->handler.settings->get(Sping::SettingCategory::WINDOW, "GLMinorVer").i);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, this->handler.settings->get(Sping::SettingCategory::WINDOW, "DepthBits").i);

	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, this->handler.settings->get(Sping::SettingCategory::WINDOW, "StencilBits").i);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, this->handler.settings->get(Sping::SettingCategory::WINDOW, "MultisampleBuffers").b);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, this->handler.settings->get(Sping::SettingCategory::WINDOW, "Multisamples").i);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, this->handler.settings->get(Sping::SettingCategory::WINDOW, "DoubleBuffer").b);

	this->glContext = SDL_GL_CreateContext(this->window);

	glewExperimental = GL_TRUE;
	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		throw Sping::Err::WINDOW;
	}

	// TODO: no magic numbers pls
	glViewport(0, 0, 1280, 720);

	Sping::debugLog({"Initialized the window! Return code: " + std::to_string(glGetError())});
}
