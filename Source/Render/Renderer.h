#pragma once

#include <memory>

#include <Render/Manager/Mesh/Meshes.h>
#include <Render/Manager/Shader/Shaders.h>
#include <Render/Manager/Texture/Textures.h>

namespace Sping
{
	class Handler;

	// Should be in the style of the Handler class
	// Should contain texture, mesh, shader manager, and scene graph too
	class Renderer
	{
	public:
		Renderer(Handler &handler);
		~Renderer();

		void draw();

		std::unique_ptr<Meshes> meshManager;
		std::unique_ptr<Shaders> shaderManager;
		std::unique_ptr<Textures> textureManager;

	protected:


	private:
		Handler &handler;

	};
}