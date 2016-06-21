#pragma once
#include <functional>

#include "SceneMgr.h"

class ISceneBase;

template<class T>
class SceneRegistrar {
public:
	SceneRegistrar(const string& sceneName)
	{
		// register the class factory function 
		CSceneMgr::GetInstance()->RegisterScene(sceneName,
												[](void) -> shared_ptr<ISceneBase> 
												{
													return make_shared<T>(); 
												}
											   );
	}
};