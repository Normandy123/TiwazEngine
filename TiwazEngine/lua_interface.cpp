#include "lua_interface.h"

template<typename TObject> const std::string TypeIDToStringName()
{
	const std::string a = typeid(TObject).name();
	const size_t b = a.find("Tiwaz::");
	return a.substr(b + 7);
};

void Tiwaz::Lua::test()
{
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);

	lua.new_usertype<EngineObject>
	(
		TypeIDToStringName<EngineObject>(), sol::constructors<EngineObject()>(),
		"object_ID", &EngineObject::object_ID
	);

	lua.new_usertype<Component::Component>
	(
		"Component", sol::constructors<Component::Component()>()
	);

	lua.new_usertype<Component::GraphicComponent>
	(
		"graphic_component", sol::constructors<Component::GraphicComponent()>()
	);

	try 
	{
		//lua.script_file("data/lua/map_init.lua");
	}
	catch (const sol::error& e) 
	{ 
		std::cout << e.what() << std::endl; 
	}

	Component::GraphicComponent* comp = lua["test_component"];
	comp = nullptr;
}
