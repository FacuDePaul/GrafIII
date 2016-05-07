#pragma once
#include "./myEngine_API.h"
#include <d3dx9.h>
#include "Bone.h"
#include "Node.h"

namespace engine{
	class MYENGINE_API Skeleton
	{
	public:
		Skeleton(Node * nRoot);
		~Skeleton();
	};
}

