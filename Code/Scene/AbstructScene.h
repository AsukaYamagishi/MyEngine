#pragma once
#include "../DirectXBase/DirectXCommon.h"
#include "../Input/KeyboardInput.h"
#include "../Audio/Audio.h"

//�V�[���̊��N���X
class AbstructScene
{
public:
	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};
};

