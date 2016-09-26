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
	
	// Stil too idiotic to get unions
	struct Data
	{
		bool b;
		int i;
		float f;
		double d;
		std::string s;
	};

	class Settings
	{
	public:
		Settings(Handler &handler);
		~Settings();

		// Should only be used by the loader to access the xml file names
		std::map<SettingCategory, std::string> SettingCategoryStrings{
			{ SettingCategory::WINDOW, "Window" },
			{ SettingCategory::CONTROLS, "Controls" }
		};

	protected:


	private:
		Handler &handler;

		std::map<SettingCategory, std::map<std::string, Data>> settings;

		int load(SettingCategory category);

	};
}