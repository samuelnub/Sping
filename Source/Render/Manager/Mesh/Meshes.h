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

	// Mesh instance, your "renderables" should only hold a shared_ptr to an existing one stored in the meshes class
	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		// This should be quite a heavy operation, might want to thread it
		Mesh(
			bool readable, 
			const std::string &name,
			const std::vector<Vertex> &vertices, 
			const std::vector<GLuint> &indices);

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

		// TODO: allow for option to load dynamic meshes etc.
		// but to be honest, you'd be 100x better off using geometry shaders instead
		const std::shared_ptr<Mesh> load(
			const std::string &name,
			const std::vector<Vertex> &vertices,
			const std::vector<GLuint> &indices,
			bool threaded = true);

		const std::shared_ptr<Mesh> get(const std::string &name);

		int remove(const std::string &name);

	protected:


	private:
		Handler &handler; // Threaded creation of mesh instances

		std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;

		// By the way, trying to remove this - since it isn't in the map, it won't do anything
		std::shared_ptr<Mesh> fauxMesh = std::make_shared<Mesh>();

	};
}