#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>         /// remove the "3" for OpenGL versions < 3
#include <OpenGL/gl3ext.h>      /// ditto
#else 
#define GLEW_STATIC
#include <GL/glew.h>
#endif

#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <memory>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace Sping
{
	class Handler;

	// You can expand this with more use cases, like glow maps etc.
	// Should be switch case'd when used
	// in order to send the right GLchar string to the shader's uniform sampler2D
	enum class TextureType
	{
		DIFFUSE,
		SPECULAR,
		NORMAL
	};

	// Sorta like settings categories, but separated into folders
	// Be sure to update the string map below too
	enum class TextureCategory
	{
		TEST = -1
	};

	// Texture format specifier to append
	// Be sure to update the string map below too
	enum class TextureFormat
	{
		PNG,
		BMP,
		JPG,
		TGA,
		GIF
	};

	// For your constructor-pleasure
	struct TextureFile
	{
		std::string name; // will look in ROOT_DIR + Textures/ folder
		TextureType type;
		TextureCategory category;
		TextureFormat format;
		bool alpha;

		TextureFile();
		TextureFile(
			const std::string &name,
			TextureType type,
			TextureCategory category,
			TextureFormat format,
			bool alpha
			);
	};

	// The uniform sampler2D you'd be passing
	struct TextureMap
	{
		TextureType type;
		GLuint texID;

		TextureMap();
	};

	// May encapsulate maps such as diffuse, specular, normal, noise(?) that one object may have
	class Texture
	{
	public:
		Texture();
		~Texture();

		Texture(bool readable, const std::string &name);

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
		friend class Textures;
		friend class Renderer;

		bool readable;

		std::string name;

		std::vector<TextureMap> textureMaps;

	};

	class Textures
	{
	public:
		Textures(Handler &handler);
		~Textures();

		const std::shared_ptr<Texture> load(
			const std::string &name,
			const std::vector<TextureFile> &textureFiles,
			bool threaded = true
			);

		const std::shared_ptr<Texture> get(const std::string &name);

		// Literal suicide
		int remove(std::shared_ptr<Texture> &texture);

	protected:


	private:
		Handler &handler;

		std::map<TextureCategory, std::string> textureCategory = {
			{TextureCategory::TEST, "test/"}
		};

		std::map<TextureFormat, std::string> textureFormat = {
			{TextureFormat::PNG, ".png"},
			{TextureFormat::BMP, ".bmp"},
			{TextureFormat::JPG, ".jpg"},
			{TextureFormat::TGA, ".tga"},
			{TextureFormat::GIF, ".gif"}
		};

		std::unordered_map<std::string, std::shared_ptr<Texture>> textures;

		std::shared_ptr<Texture> fauxTexture = std::make_shared<Texture>(false, "faux-texture");
	};
}