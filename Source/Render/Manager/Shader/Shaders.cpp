#include <Render/Manager/Shader/Shaders.h>

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
	for (auto &shader : shaderFiles)
	{
		// TODO: gl stuff
	}

	this->uniforms = uniforms;

	return 0;
}
