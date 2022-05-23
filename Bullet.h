#pragma once
#include "ModelManager.h"
#include "ModelDraw.h"
#include "Vector3.h"
#include "DirectXCommon.h"


class Bullet
{
public:
	Bullet(DirectXCommon *dxCommon, Vector3 pos, Vector3 velosity);

	void Update();

	void Draw();

private:
	ModelDraw *model = nullptr;
	DirectXCommon* dxCommon = nullptr;

	Vector3 move;

};

