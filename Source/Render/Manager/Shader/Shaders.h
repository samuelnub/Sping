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
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <Util/Constants.h>

namespace Sping
{
	class Handler;

	// The Shader class should search for this name in the Resources/Shaders/ folder and append .glsl
	// This should really just be a helper to pass in args to the Shader constructor
	struct ShaderFile
	{
		std::string name;
		GLenum type;

		ShaderFile();
		ShaderFile(const std::string &name, GLenum type);
	};
	
	struct ShaderUniform
	{
		std::string name; // Just do .c_str() when passing it, it's a constant time operation anyways
		GLfloat value;

		ShaderUniform();
		ShaderUniform(const std::string &name, GLfloat value);
	};
	
	// TODO: refactor as factory pattern for Shaders
	// Shader program holder, which just encapsulates a single pipeline
	// Your renderable class should have a shared ptr to this from the Shaders manager
	class Shader
	{
	public:
		Shader();
		~Shader();

		Shader(bool readable, const std::string &name);

		inline const bool &isReadable()
		{
			return this->readable;
		}
		
		inline const std::string &getName()
		{
			return this->name;
		}

	protected:


	private:
		friend class Shaders;
		friend class Renderer;

		bool readable;

		std::string name;

		GLuint programID;
		
		std::vector<ShaderUniform> uniforms;
		// TODO: support for other storage buffers, like SSBO's
	};

	// Shader manager, should manage each shader program
	class Shaders
	{
	public:
		Shaders(Handler &handler);
		~Shaders();

		// You shouldn't be loading and compiling shaders during regular runtime
		// Should be done internally on setup, for all shaders needed
		const std::shared_ptr<Shader> load(
			const std::string &name,
			const std::vector<ShaderFile> &shaderFiles,
			const std::vector<ShaderUniform> &uniforms,
			bool threaded = false
			);

		std::shared_ptr<Shader> get(const std::string &name);

		int remove(std::shared_ptr<Shader> &shader);

	protected:


	private:
		Handler &handler;

		std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

		std::shared_ptr<Shader> fauxShader = std::make_shared<Shader>(false, "faux-shader");
	};
}