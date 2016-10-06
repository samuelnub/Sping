#pragma once

#include <Util/GLEWInclude.h>

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

	// Safer enum class wrapper for GL_STATIC_DRAW enum etc.
	enum class GLDrawUsage
	{
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW,
		STREAM = GL_STREAM_DRAW
	};

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 norm;
		glm::vec2 uv;

		Vertex();
		Vertex(
			const glm::vec3 &pos,
			const glm::vec3 &norm,
			const glm::vec2 &uv
			);

		// Stupid dummy constructor for ease
		Vertex(bool test);
	};
	
	// Mesh instance, your "renderables" should only hold a shared_ptr to an existing one stored in the meshes class
	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		Mesh(bool readable, const std::string &name);

		inline const bool &isReadable()
		{
			return this->readable;
		}

		// In case you want to remove it by name
		inline const std::string &getName()
		{
			return this->name;
		}

	protected:


	private:
		friend class Meshes;
		friend class Renderer;
		
		bool readable;

		std::string name; // should reflect its location in the meshes' map

		GLuint vboID;
		GLuint eboID;
		GLuint vaoID;

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		
	};

	// Mesh manager
	class Meshes
	{
	public:
		Meshes(Handler &handler);
		~Meshes();

		// TODO: overloaded load func to load from obj file, with assimp support (when you need it)

		// TODO: allow for option to load dynamic meshes etc.
		// but to be honest, you'd be 100x better off using geometry shaders instead
		const std::shared_ptr<Mesh> load(
			const std::string &name,
			const std::vector<Vertex> &vertices,
			const std::vector<GLuint> &indices,
			GLDrawUsage usage = GLDrawUsage::DYNAMIC,
			bool threaded = false);

		const std::shared_ptr<Mesh> get(const std::string &name);
		
		int remove(std::shared_ptr<Mesh> &mesh);

	protected:


	private:
		Handler &handler; // Threaded creation of mesh instances

		std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;

		// By the way, trying to remove this - since it isn't in the map, it won't do anything
		std::shared_ptr<Mesh> fauxMesh = std::make_shared<Mesh>(false, "faux-mesh");

	};
}