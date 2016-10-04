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

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 norm;
		glm::vec3 uv;
	};

	// TODO: refactor for factory pattern
	// Mesh instance, your "renderables" should only hold a shared_ptr to an existing one stored in the meshes class
	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		Mesh(bool readable);

		// Shouldn't be using this constructor directly
		Mesh(
			bool readable,
			const std::string &name,
			const std::vector<Vertex> &vertices,
			const std::vector<GLuint> &indices
			);

		// Should only be used internally within Meshes class
		int set(
			const std::string &name,
			const std::vector<Vertex> &vertices,
			const std::vector<GLuint> &indices
			);

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
			bool threaded = true);

		const std::shared_ptr<Mesh> get(const std::string &name);

		// By the way, the whole purpose of a shared pointer is to not deallocate the memory if someone's still holding on to it
		// (be it one of your objects), so this is quite useless
		// Actually, I take that back, make it so when you delete your
		// Object instance, in the destructor, call this->mesh.reset(nullptr)
		// So that you'll decrement the "pointer counter" in this pool,
		// In the hopes that the removal of the last one will allow proper deletion here
		// That's actually really ducking handy, thanks smart memory
		int remove(const std::string &name);

	protected:


	private:
		Handler &handler; // Threaded creation of mesh instances

		std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;

		// By the way, trying to remove this - since it isn't in the map, it won't do anything
		std::shared_ptr<Mesh> fauxMesh = std::make_shared<Mesh>(false);

	};
}