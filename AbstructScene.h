#pragma once
#include "DirectXCommon.h"
#include "KeyboardInput.h"
#include "Audio.h"

//�V�[���̊��N���X
class AbstructScene
{
public:
	virtual void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio) {};
	virtual void Update() {};
	virtual void Draw() {};
};

