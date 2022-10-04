#pragma once
#include "DirectXCommon.h"
#include "KeyboardInput.h"
#include "Code/Audio/Audio.h"

//シーンの基底クラス
class AbstructScene
{
public:
	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};
};

