#pragma once
#include "DirectXCommon.h"
#include "KeyboardInput.h"
#include "Audio.h"

//シーンの基底クラス
class AbstructScene
{
public:
	virtual void Init(DirectXCommon* dxCommon, Audio* audio) {};
	virtual void Update() {};
	virtual void Draw() {};
};

