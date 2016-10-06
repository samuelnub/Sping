#include <Render/Manager/Shader/Shaders.h>
#include <Handler/Handler.h>

Sping::ShaderFile::ShaderFile()
{
}

Sping::ShaderFile::ShaderFile(const std::string & name, GLenum type) :
	name(name),
	type(type)
{
}

Sping::ShaderUniform::ShaderUniform()
{
}

Sping::ShaderUniform::ShaderUniform(const std::string & name, GLfloat value) :
	name(name),
	value(value)
{
}

Sping::Shader::Shader()
{
}

Sping::Shader::~Shader()
{
}

Sping::Shader::Shader(bool readable, const std::string &name) :
	readable(readable),
	name(name)
{
}

Sping::Shaders::Shaders(Handler &handler) :
	handler(handler)
{
	// TODO: shader constructor shiz
}

Sping::Shaders::~Shaders()
{
	for (auto &shader : this->shaders)
	{
		glDeleteProgram(shader.second->programID);
	}
}

const std::shared_ptr<Sping::Shader> Sping::Shaders::load(const std::string & name, const std::vector<ShaderFile>& shaderFiles, const std::vector<ShaderUniform>& uniforms, bool threaded)
{
	try
	{
		return this->shaders.at(name);
	}
	catch (std::exception err)
	{
		;
	}

	this->shaders[name] = std::make_shared<Shader>(false, name);

	auto lambda = [&] {
		std::vector<GLuint> shaderIDs = {};

		GLint succ;
		GLchar log[2048]; // magic number here, and below too

		for (auto &shader : shaderFiles)
		{
			std::string code;
			std::ifstream file;

			file.exceptions(std::ifstream::badbit);

			try
			{
				// TODO: magic strings
				file.open({ Sping::ROOT_DIR + "Shaders/" + shader.name + ".glsl"
				});

				std::stringstream stream;

				stream << file.rdbuf();

				file.close();

				code = stream.str();
			}
			catch (std::ifstream::failure err)
			{
				Sping::debugLog({ "Couldn't compile the shader with the name " + shader.name });
				throw Sping::Err::SHADER_COMPILE;
			}

			const GLchar *glCode = code.c_str();

			GLuint shaderID;

			shaderID = glCreateShader(shader.type);
			glShaderSource(shaderID, 1, &glCode, NULL);
			glCompileShader(shaderID);
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &succ);
			if (!succ)
			{
				glGetShaderInfoLog(shaderID, 2048, NULL, log);
				Sping::debugLog({ "Shader compilation for " + shader.name + " failed:\n" + log });
				throw Sping::Err::SHADER_COMPILE;
			}

			shaderIDs.push_back(shaderID);
		}

		this->shaders[name]->programID = glCreateProgram();

		for (auto &shaderID : shaderIDs)
		{
			glAttachShader(this->shaders[name]->programID, shaderID);
		}
		glLinkProgram(this->shaders[name]->programID);

		glGetProgramiv(this->shaders[name]->programID, GL_LINK_STATUS, &succ);
		if (!succ)
		{
			glGetProgramInfoLog(this->shaders[name]->programID, 2048, NULL, log);
			Sping::debugLog({ "Linking for shader " + name + " failed:\n" + log });
			throw Sping::Err::SHADER_LINK;
		}

		for (auto &shaderID : shaderIDs)
		{
			glDeleteShader(shaderID);
		}

		this->shaders[name]->uniforms = uniforms;

		if (succ)
		{
			Sping::debugLog({ "Loaded a shader with the name " + name + " Exit code: " + std::to_string(glGetError()) });
		}

		this->shaders[name]->readable = true;
	};

	if (threaded == true)
	{
		this->handler.threadPool->enqueue(lambda);
	}
	else if (threaded == false)
	{
		lambda();
	}

	return this->shaders.at(name);
}

std::shared_ptr<Sping::Shader> Sping::Shaders::get(const std::string & name)
{
	try
	{
		return this->shaders.at(name);
	}
	catch (std::exception err)
	{
		Sping::debugLog({ "You nincompoop! You tried to get a nonexistant shader with the name " + name });
		return this->fauxShader;
	}
}

int Sping::Shaders::remove(std::shared_ptr<Sping::Shader>& shader)
{
	try
	{
		// It needs your shared_ptr and the pool's shared ptr to guarantee this, so the minimum is a 2
		if (this->shaders.at(shader->name).use_count() <= 2)
		{
			glDeleteProgram(shader->programID);

			this->shaders.at(shader->name).reset();
			this->shaders.erase(shader->name);
		}
		else
		{
			shader.reset();
			return -1;
		}

		shader.reset();
		return 0;
	}
	catch (std::exception err)
	{
		shader.reset();
		return -2;
	}
}
