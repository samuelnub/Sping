#include <Handler/File/Settings.h>
#include <Handler/Handler.h>

Sping::Settings::Settings(Handler &handler) :
	handler(handler)
{
}

Sping::Settings::~Settings()
{
}

int Sping::Settings::load(Sping::SettingCategory category)
{
	std::string fullPath =
		"Resource/Settings/" +
		Sping::Settings::SettingCategoryStrings[category] +
		".xml";

	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError xmlErr = xmlDoc.LoadFile(fullPath.c_str());
	if (xmlErr != 0)
	{
		throw Sping::Err::FILE_ERROR;
		return 1;
	}

	this->settings[category] = {};

	tinyxml2::XMLElement *xmlEle = xmlDoc.FirstChildElement(Sping::Settings::SettingCategoryStrings[category].c_str());
	if (xmlEle != nullptr)
	{
		xmlEle = xmlEle->FirstChildElement("setting");
		if (xmlEle != nullptr)
		{
			while (xmlEle != nullptr)
			{
				std::string name = xmlEle->Attribute("name");
				std::string type = xmlEle->Attribute("type");

				Sping::Data *data = &this->settings[category][name];

				if (type == "Bool")
				{
					xmlEle->QueryBoolAttribute("value", &data->b);
				}
				else if (type == "Int")
				{
					xmlEle->QueryIntAttribute("value", &data->i);
				}
				else if (type == "Float")
				{
					xmlEle->QueryFloatAttribute("Value", &data->f);
				}
				else if (type == "Double")
				{
					xmlEle->QueryDoubleAttribute("Value", &data->d);
				}
				else if (type == "String")
				{
					data->s = xmlEle->Attribute("value");
				}

				xmlEle = xmlEle->NextSiblingElement("setting");
			}
		}
	}

	return 0;
}
