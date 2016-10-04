#include <Render/Manager/Texture/Textures.h>
#include <Handler/Handler.h>
#include <Util/Constants.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Sping::TextureFile::TextureFile()
{
}

Sping::TextureFile::TextureFile(const std::string & name, TextureType type, TextureCategory category, TextureFormat format, bool alpha) :
	name(name),
	type(type),
	category(category),
	format(format),
	alpha(alpha)
{
}

Sping::TextureMap::TextureMap()
{
}

Sping::Texture::Texture()
{
}

Sping::Texture::~Texture()
{
}

Sping::Texture::Texture(bool readable, const std::string &name) :
	readable(readable),
	name(name)
{
}

Sping::Textures::Textures(Handler & handler) :
	handler(handler)
{
	// TODO: constructor shiz for textures
}

Sping::Textures::~Textures()
{
	for (auto &texture : this->textures)
	{
		for (auto &textureMap : texture.second->textureMaps)
		{
			glDeleteTextures(1, &textureMap.texID);
		}
	}
}

const std::shared_ptr<Sping::Texture> Sping::Textures::load(const std::string & name, const std::vector<TextureFile>& textureFiles, bool threaded)
{
	try
	{
		return this->textures.at(name);
	}
	catch (std::exception err)
	{
		;
	}
	
	this->textures[name] = std::make_shared<Sping::Texture>(false, name);

	// Sorry, just bad at naming
	auto lambda = [&] {
		for (auto &textureFile : textureFiles)
		{
			int w, h, size;
			
			// magic string
			std::string filename = Sping::ROOT_DIR + "Textures/" + Sping::Textures::textureCategory[textureFile.category] + textureFile.name + Sping::Textures::textureFormat[textureFile.format];

			unsigned char *image = stbi_load(
				filename.c_str(),
				&w,
				&h,
				&size,
				(textureFile.alpha) ? STBI_rgb_alpha : STBI_rgb
				);

			if (image == nullptr)
			{
				throw Sping::Err::IMAGE_LOAD;
			}
			
			this->textures[name]->textureMaps.emplace_back(Sping::TextureMap());
			Sping::TextureMap *textureMap = &textures[name]->textureMaps.back();

			glGenTextures(1, &textureMap->texID);
			glBindTexture(GL_TEXTURE_2D, textureMap->texID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				(textureFile.alpha) ? GL_RGBA : GL_RGB,
				w,
				h,
				0,
				(textureFile.alpha) ? GL_RGBA : GL_RGB,
				GL_UNSIGNED_BYTE,
				image
				);

			glBindTexture(GL_TEXTURE_2D, 0);

			stbi_image_free(image);

			textureMap->type = textureFile.type;
		}
	};

	if (threaded == true)
	{
		this->handler.threadPool->enqueue([&]{
			lambda();
		});
	}
	else if (threaded == false)
	{
		lambda();
	}

	return this->textures.at(name);
}

const std::shared_ptr<Sping::Texture> Sping::Textures::get(const std::string & name)
{
	try
	{
		return this->textures.at(name);
	}
	catch (std::exception err)
	{
		Sping::debugLog({ "Numbo! Stop requesting for textures that don't exist!" });
		return this->fauxTexture;
	}
}

int Sping::Textures::remove(std::shared_ptr<Sping::Texture> &texture)
{
	try
	{
		if (this->textures.at(texture->name).use_count() <= 1)
		{
			for (auto &textureMap : texture->textureMaps)
			{
				glDeleteTextures(1, &textureMap.texID);
			}
			
			this->textures.at(texture->name).reset();
		}
		else
		{
			return -1;
		}

		texture.reset();
		return 0;
	}
	catch (std::exception err)
	{
		return -2;
	}
}

