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

Sping::Shader::Shader(bool readable) :
	readable(readable)
{
}

Sping::Shader::Shader(bool readable, const std::string & name, const std::vector<ShaderFile>& shaderFiles, const std::vector<ShaderUniform>& uniforms) :
	readable(readable)
{
	this->compile(name, shaderFiles, uniforms);
}

int Sping::Shader::compile(const std::string & name, const std::vector<ShaderFile>& shaderFiles, const std::vector<ShaderUniform>& uniforms)
{
	this->name = name;

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
			file.open("Resources/Shaders/" + shader.name + ".glsl");

			std::stringstream stream;

			stream << file.rdbuf();

			file.close();

			code = stream.str();
		}
		catch (std::ifstream::failure err)
		{
			Sping::debugLog({ "Couldn't compile the shader with the name " + shader.name });
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
		}

		shaderIDs.push_back(shaderID);
	}

	this->programID = glCreateProgram();
	
	for (auto &shaderID : shaderIDs)
	{
		glAttachShader(this->programID, shaderID);
	}
	glLinkProgram(this->programID);

	glGetProgramiv(this->programID, GL_LINK_STATUS, &succ);
	if (!succ)
	{
		glGetProgramInfoLog(this->programID, 2048, NULL, log);
		Sping::debugLog({ "Linking for shader " + name + " failed:\n" + log });
	}

	for (auto &shaderID : shaderIDs)
	{
		glDeleteShader(shaderID);
	}

	this->uniforms = uniforms;

	if (succ)
	{
		Sping::debugLog({ "Successfully compiled shaders and linked into " + name });
	}

	this->readable = true;

	return 0;
}

Sping::Shaders::Shaders(Handler & handler)
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

std::shared_ptr<Sping::Shader> Sping::Shaders::load(const std::string & name, const std::vector<ShaderFile>& shaderFiles, const std::vector<ShaderUniform>& uniforms, bool threaded)
{
	try
	{
		return this->shaders.at(name);
	}
	catch (std::exception err)
	{
		;
	}

	this->shaders[name] = std::make_shared<Shader>(false);

	if (threaded == true)
	{
		this->handler.threadPool->enqueue([=] {
			this->shaders[name]->compile(
				name,
				shaderFiles,
				uniforms
				);
		});
	}
	else if (threaded == false)
	{
		this->shaders[name]->compile(
			name,
			shaderFiles,
			uniforms
			);
	}

	return this->shaders.at(name);
}
