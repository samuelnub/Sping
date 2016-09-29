#include <Render/Manager/Mesh/Meshes.h>
#include <Handler/Handler.h>

Sping::Mesh::Mesh()
{
}

Sping::Mesh::~Mesh()
{
}

Sping::Mesh::Mesh(bool readable) :
	readable(readable)
{
}

int Sping::Mesh::set(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
	// TODO: GL code here

	this->readable = true;
}

Sping::Meshes::Meshes(Handler & handler) :
	handler(handler)
{
}

Sping::Meshes::~Meshes()
{
}

const std::shared_ptr<Sping::Mesh> Sping::Meshes::load(const std::string & name, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, bool threaded)
{
	try
	{
		return this->meshes.at(name);
	}
	catch (std::exception err)
	{
		;
	}

	this->meshes[name] = std::make_shared<Mesh>(false);

	if (threaded == true)
	{
		this->handler.threadPool->enqueue([=] {
			this->meshes[name]->set(
				vertices,
				indices
				);
		});
	}
	else if (threaded == false)
	{
		this->meshes[name]->set(
			vertices,
			indices
			);
	}

	
	return this->meshes.at(name);
}
