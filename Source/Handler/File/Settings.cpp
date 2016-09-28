#include <Handler/File/Settings.h>
#include <Handler/Handler.h>

Sping::Settings::Settings(Handler &handler) :
	handler(handler)
{
	for (auto &category : this->SettingCategoryStrings)
	{
		this->load(category.first);
	}
}

Sping::Settings::~Settings()
{
}

Sping::Data &Sping::Settings::get(SettingCategory category, const std::string & name)
{
	try
	{
		return this->settings.at(category).settingData.at(name);
	}
	catch (std::exception err)
	{
		Sping::debugLog({ "You bugger! You tried to get a nonexistant setting!" });
		return fauxData;
	}
}

void Sping::Settings::set(SettingCategory category, const std::string name, const Data & data)
{
	try
	{
		Sping::Data *dataPtr = &this->settings.at(category).settingData.at(name);

		switch (data.type)
		{
		case Sping::DataType::BOOL:
			dataPtr->b = data.b;
			break;
		case Sping::DataType::INT:
			dataPtr->i = data.i;
			break;
		case Sping::DataType::FLOAT:
			dataPtr->f = data.f;
			break;
		case Sping::DataType::DOUBLE:
			dataPtr->d = data.d;
			break;
		case Sping::DataType::STRING:
			dataPtr->s = data.s;
			break;
		default:
			break;
		}
	}
	catch (std::exception err)
	{
		Sping::debugLog({ "You idiot hammond, you tried to set a nonexistant setting!" });
		return;
	}
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
		throw Sping::Err::FILE;
		return 1;
	}

	this->settings[category] = {false};

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

				Sping::Data *data = &this->settings[category].settingData[name];

				if (type == "Bool")
				{
					xmlEle->QueryBoolAttribute("value", &data->b);
					data->type = Sping::DataType::BOOL;
				}
				else if (type == "Int")
				{
					xmlEle->QueryIntAttribute("value", &data->i);
					data->type = Sping::DataType::INT;
				}
				else if (type == "Float")
				{
					xmlEle->QueryFloatAttribute("Value", &data->f);
					data->type = Sping::DataType::FLOAT;
				}
				else if (type == "Double")
				{
					xmlEle->QueryDoubleAttribute("Value", &data->d);
					data->type = Sping::DataType::DOUBLE;
				}
				else if (type == "String")
				{
					data->s = xmlEle->Attribute("value");
					data->type = Sping::DataType::STRING;
				}
				else
				{
					Sping::debugLog({ "Settings: Unknown type specified for the setting name " + name + "!" });
				}

				Sping::debugLog({ "Settings: Got the setting with the name " + name + "!" });

				xmlEle = xmlEle->NextSiblingElement("setting");
			}
		}
	}

	this->settings[category].readable = true;

	return 0;
}
