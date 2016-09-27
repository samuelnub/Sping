#pragma once

#include <tinyxml2/tinyxml2.h>
#include <string>
#include <map>

namespace Sping
{
	class Handler;

	// Use this when specifying what y'want, less error-prone than runtime string mishaps
	enum class SettingCategory
	{
		WINDOW,
		CONTROLS
		// etc
	};
	
	enum class DataType
	{
		BOOL,
		INT,
		FLOAT,
		DOUBLE,
		STRING,
		NONE
	};

	// Stil too idiotic to get unions
	struct Data
	{
		DataType type;

		bool b;
		int i;
		float f;
		double d;
		std::string s;

		Data(bool b) : b(b), type(DataType::BOOL) {}
		Data(int i) : i(i), type(DataType::INT) {}
		Data(float f) : f(f), type(DataType::FLOAT) {}
		Data(double d) : d(d), type(DataType::DOUBLE) {}
		Data(const std::string &s) : s(s), type(DataType::STRING) {}

		// Dummy constructor, shouldn't be used normally
		Data(DataType type) : b(false), i(0), f(0.0f), d(0.0), s("None"), type(type) {}
	};

	// Embodiment of a settings category's file contents
	struct SettingFile
	{
		// Y'know, I could use std::atomic, but really? I'm not _that_ eager to write good code
		bool readable;

		std::map<std::string, Data> settingData = {};

		SettingFile(bool readable) : readable(readable) {}
	};

	class Settings
	{
	public:
		Settings(Handler &handler);
		~Settings();

		// Should only be used by the loader to access the xml file name strings
		std::map<SettingCategory, std::string> SettingCategoryStrings = {
			{ SettingCategory::WINDOW, "Window" },
			{ SettingCategory::CONTROLS, "Controls" }
		};

		Data &get(SettingCategory category, const std::string &name);

		void set(SettingCategory category, const std::string name, const Data &data);

	protected:


	private:
		Handler &handler;

		std::map<SettingCategory, SettingFile> settings;

		int load(SettingCategory category);
		int save(SettingCategory category); // TODO: make it when y'need it, should iterate through map and write attributes to file

		// In case you're stupid and request for something that doesn't exist, return these dummy values
		Data fauxData = { DataType::NONE };

	};
}