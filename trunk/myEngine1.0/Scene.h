#pragma once
#include <string>
#include <map>
#include <vector>
#include "myEngine_API.h"

namespace engine{
	class Renderer;
	class Mesh;
	class TileMap;
	class Timer;
	class NodeBSP;
	class Node;

	class MYENGINE_API Scene{
		public:
			Scene(std::string name); //le pasamos un nombre para identificarlo
			~Scene();
			void Update(Timer*);
			virtual void Draw(Renderer*);
			void Add(std::string, Mesh*);//agrego entidad
			void RemoveMesh(Mesh*);//quito entidad
			void RemoveMesh(std::string);//quito entidad por nombre
			Mesh* GetMesh(std::string);
			void SetName(std::string);
			std::string GetName();
			//colisiones
			bool AddClsGroup(std::string);
			bool RemoveClsGroup(std::string);
			bool AddMeshToClsGroup(Mesh*, std::string);
			bool RemoveMeshFromClsGroup(Mesh*);
			bool ChangeMeshFromClsGroup(Mesh*, std::string);
			void CheckColisions();
			//-----------------------------------------
		private:
			std::string m_sName;
			std::map<std::string, Mesh*> m_mapMesh;//entidades que tiene
			std::map<std::string, Mesh*>::iterator m_mIteratorMesh;//iterador para recorrerlas	
			typedef std::vector<Mesh*> Mesh3DVector;//defino
			typedef Mesh3DVector::iterator Mesh3DVectorIter;//defino	
			typedef std::map< std::string, Mesh3DVector*> CollisionGroupMap;// defino
			typedef std::map< std::string, Mesh3DVector*>::iterator CollisionGroupMapIter; //defino
			CollisionGroupMap m_pClsGroups;
			CollisionGroupMapIter m_pClsGroupsIter;
			//------------------
			//Todo esto es para el los for del check col
			CollisionGroupMapIter m_pClsGroupsIterA;
			CollisionGroupMapIter m_pClsGroupsIterB;
			Mesh3DVector *m_pEntVectorA;
			Mesh3DVector *m_pEntVectorB;
			Mesh *m_pEntA;
			Mesh *m_pEntB;
			//------------------

		public:	// Virtual functions to override if the user want to make his own scenes...
			virtual void OnStart() { }
			virtual void OnUpdate(Timer*) { } 
			virtual void OnShutdown() { }

	};
}