#include <Render/Manager/Mesh/Meshes.h>
#include <Handler/Handler.h>
#include <Util/Constants.h>

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

Sping::Mesh::Mesh(bool readable, const std::string & name, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) :
	readable(readable)
{
	this->set(name, vertices, indices);
}

int Sping::Mesh::set(const std::string &name, const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices)
{
	this->name = name;

	// Big ol' operation
	this->vertices = vertices;
	this->indices = indices;

	glGenVertexArrays(1, &this->vaoID);
	glGenBuffers(1, &this->vboID);
	glGenBuffers(1, &this->eboID);

	glBindVertexArray(this->vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(
		GL_ARRAY_BUFFER,
		this->vertices.size() * sizeof(Sping::Vertex),
		&this->vertices.at(0), // Gotta specify the first element lol,
		GL_STATIC_DRAW // TODO: maybe dynamic draw option in the future?
		);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboID);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		this->indices.size() * sizeof(GLuint),
		&this->indices.at(0),
		GL_STATIC_DRAW
		);

	// Vertex attributes
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Sping::Vertex),
		(GLvoid*)0
		);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Sping::Vertex),
		(GLvoid*)offsetof(Sping::Vertex, norm)
		);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Sping::Vertex),
		(GLvoid*)offsetof(Sping::Vertex, uv)
		);

	glBindVertexArray(0);

	this->readable = true;

	return 0;
}

Sping::Meshes::Meshes(Handler & handler) :
	handler(handler)
{
	// TODO: intial constructor shiz
}

Sping::Meshes::~Meshes()
{
	for (auto &mesh : this->meshes)
	{
		glDeleteVertexArrays(1, &mesh.second->vaoID);
		glDeleteBuffers(1, &mesh.second->vboID);
		glDeleteBuffers(1, &mesh.second->eboID);
	}
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
				name,
				vertices,
				indices
				);
		});
	}
	else if (threaded == false)
	{
		this->meshes[name]->set(
			name,
			vertices,
			indices
			);
	}

	return this->meshes.at(name);
}

const std::shared_ptr<Sping::Mesh> Sping::Meshes::get(const std::string & name)
{
	try
	{
		return this->meshes.at(name);
	}
	catch (std::exception err)
	{
		Sping::debugLog({ "You nincompoop! You tried to get a nonexistant mesh with the name " + name });
		return this->fauxMesh;
	}
}

int Sping::Meshes::remove(const std::string & name)
{
	try
	{
		this->meshes.erase(name);
		return 0;
	}
	catch (std::exception err)
	{
		return 1;
	}
}
