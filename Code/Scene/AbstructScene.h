#pragma once
#include "../DirectXCommon.h"
#include "../KeyboardInput.h"
#include "../Audio/Audio.h"

//�V�[���̊��N���X
class AbstructScene
{
public:
	virtual void Init() {};
	virtual void Update() {};
	virtual void Draw() {};
};

