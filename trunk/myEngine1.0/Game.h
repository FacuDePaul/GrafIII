#pragma once
#include "myEngine_API.h"
#include <string>
#include <map>
namespace engine{
	class Renderer;
	class DirectInput;
	class Timer;
	class Scene;
	class MYENGINE_API Game{
		public:
			Game() { GameOn = true;}
			~Game();
			virtual bool Init(engine::Renderer&) = 0;
			virtual void Frame(engine::Renderer&, engine::DirectInput&, engine::Timer&) = 0;
			virtual void DeInit() = 0;
			bool GameOn;
			void setGame(const bool b){ GameOn = b;}
			bool getGame(){ return GameOn;}

			void CreateScene(std::string);
			Scene* GetScene(std::string);
			void DrawScenes(Renderer*, Timer*);

		protected:
			std::map<std::string, Scene*> m_mapa;//escenas
			std::map<std::string, Scene*>::iterator m_mIterator;

		public:
			void OnSceneInit();
			void OnSceneUpdate(Timer*);
			void OnSceneShutdown();
			void AddScene(Scene*);
	};
}