#include "Scene.h"
#include "timer\Timer.h"
#include "Renderer.h"
#include <iostream>

namespace MyGame{
	class MyCustomScene : public engine::Scene{
	public:
		MyCustomScene(std::string s) : Scene(s){ }
		~MyCustomScene() { }
		void OnStart();
		void OnUpdate(engine::Timer*);
		void OnShutdown();
		void Draw(engine::Renderer*);
	};
}