#include <Render/Manager/Mesh/Meshes.h>
#include <Handler/Handler.h>
#include <Util/Constants.h>

Sping::Vertex::Vertex()
{
}

Sping::Vertex::Vertex(const glm::vec3 & pos, const glm::vec3 & norm, const glm::vec2 & uv) :
	pos(pos),
	norm(norm),
	uv(uv)
{
}

Sping::Vertex::Vertex(bool test) :
	pos({test,test,test}),
	norm({test,test,test}),
	uv({test,test})
{
}

Sping::Mesh::Mesh()
{
}

Sping::Mesh::~Mesh()
{
}

Sping::Mesh::Mesh(bool readable, const std::string &name) :
	readable(readable),
	name(name)
{
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

const std::shared_ptr<Sping::Mesh> Sping::Meshes::load(const std::string & name, const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, Sping::GLDrawUsage usage, bool threaded)
{
	try
	{
		return this->meshes.at(name);
	}
	catch (std::exception err)
	{
		;
	}

	this->meshes[name] = std::make_shared<Mesh>(false, name);

	auto lambda = [&, this] {
		if (vertices.size() <= 0 || indices.size() <= 0)
		{
			Sping::debugLog({ "You numbo! Stop trying to make a mesh without any data! Looking at you, " + name});
			throw Sping::Err::GENERIC;
			return;
		}
		// Timely operation
		this->meshes[name]->vertices = vertices;
		this->meshes[name]->indices = indices;
		
		glGenVertexArrays(1, &this->meshes[name]->vaoID);
		glGenBuffers(1, &this->meshes[name]->vboID);
		glGenBuffers(1, &this->meshes[name]->eboID);

		glBindVertexArray(this->meshes[name]->vaoID);

		// You could make this an SSBO, tossing all OSX users out the window
		glBindBuffer(GL_ARRAY_BUFFER, this->meshes[name]->vboID);
		glBufferData(
			GL_ARRAY_BUFFER,
			this->meshes[name]->vertices.size() * sizeof(Sping::Vertex),
			&this->meshes[name]->vertices.at(0),
			static_cast<int>(usage)
			);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->meshes[name]->eboID);
		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			this->meshes[name]->indices.size() * sizeof(GLuint),
			&this->meshes[name]->indices.at(0),
			static_cast<int>(usage)
			);

		// Vert. attibs
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

		Sping::debugLog({ "Loaded a mesh with the name " + name + " Exit code: " + std::to_string(glGetError()) });

		this->meshes[name]->readable = true;
	};

	if (threaded == true)
	{
		this->handler.threadPool->enqueue(lambda);
	}
	else if (threaded == false)
	{
		lambda();
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

int Sping::Meshes::remove(std::shared_ptr<Sping::Mesh> &mesh)
{
	try
	{
		// It needs your shared_ptr and the pool's shared ptr to guarantee this, so the minimum is a 2
		if (this->meshes.at(mesh->name).use_count() <= 2)
		{
			glDeleteVertexArrays(1, &mesh->vaoID);
			glDeleteBuffers(1, &mesh->vboID);
			glDeleteBuffers(1, &mesh->eboID);

			this->meshes.at(mesh->name).reset();
			this->meshes.erase(mesh->name);
		}
		else
		{
			mesh.reset();
			return -1;
		}

		mesh.reset();
		return 0;
	}
	catch (std::exception err)
	{
		mesh.reset();
		return -2;
	}
}
