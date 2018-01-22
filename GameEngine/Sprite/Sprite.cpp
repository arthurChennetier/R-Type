#include <Scene/Scene.hpp>

namespace TacosEngine
{
	Sprite::Sprite(const std::string &myname, std::shared_ptr<Scene> scene)
		: Entity(myname)
	{
		if (scene)
			_scene = scene;
	}


	void Sprite::setScene(std::shared_ptr<Scene> scene)
	{
		_scene = std::move(scene);
	}

	std::list<std::shared_ptr<Component>>	Sprite::getComponentList()
	{

	}
}