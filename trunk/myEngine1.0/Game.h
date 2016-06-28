#pragma once
#include "myEngine_API.h"
#include <string>
#include <map>
#include <vector>
namespace engine{
	class Renderer;
	class DirectInput;
	class Timer;
	class Scene;
	class NodeBSP;
	class Node;
	class MYENGINE_API Game{
		public:
			Game() : BSP(NULL) { GameOn = true;}
			~Game();
			virtual bool Init(engine::Renderer&) = 0;
			virtual void Frame(engine::Renderer&, engine::DirectInput&, engine::Timer&);
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



			// BSP THINGS!
			std::vector<Node*> NodesToBSP;
			std::vector<Node*> ParentNodes;
			std::vector<NodeBSP*> BSPNodes;
			NodeBSP* BSP;

			public:	// BSP!!
				void AddBSPPlane(Node* node);
				void AddNodeToBSP(Node* node);
				void RegisterInBSPtree(Node* node, bool isBSP);
				void ArrangeBSPTree();
	};
}