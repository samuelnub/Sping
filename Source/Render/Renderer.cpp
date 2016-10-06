#include <Render/Renderer.h>
#include <Handler/Handler.h>

Sping::Renderer::Renderer(Handler &handler) : 
	handler(handler),
	meshManager(std::make_unique<Sping::Meshes>(handler)),
	shaderManager(std::make_unique<Sping::Shaders>(handler)),
	textureManager(std::make_unique<Sping::Textures>(handler))
{
}

Sping::Renderer::~Renderer()
{
}
