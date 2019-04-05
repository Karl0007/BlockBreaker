#pragma once
#include "Component.h"
#include <memory>

class Component;
enum class ComponentType;
class ComponentFactory
{
private:

	ComponentFactory();
	~ComponentFactory();
	ComponentFactory(ComponentFactory const&) = delete;
	ComponentFactory(ComponentFactory &&) = delete;
	ComponentFactory& operator= (ComponentFactory const&) = delete;
	ComponentFactory& operator= (ComponentFactory &&) = delete;

	static ComponentFactory * Instance;

public:

	static ComponentFactory& getInstance();

	Component* getComponent(ComponentType type);

};

