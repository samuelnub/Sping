#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>         /// remove the "3" for OpenGL versions < 3
#include <OpenGL/gl3ext.h>      /// ditto
#else 
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace Sping
{
	class Handler;

	class Texture
	{
	public:


	protected:


	private:


	};

	class Textures
	{
	public:
		Textures(Handler &handler);
		~Textures();



	protected:


	private:
		Handler &handler;

		std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

	};
}