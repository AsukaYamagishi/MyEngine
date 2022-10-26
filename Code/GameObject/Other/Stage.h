#pragma once
#include "../../DirectXBase/DirectXCommon.h"
#include "../../3d/Obj/ObjDraw.h"
#include "../../Manager/ModelManager.h"

class Stage {
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::��ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Stage();
	~Stage();
	void Initialize(DirectXCommon* dxCommon);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

public:
	ObjDraw* skydome = nullptr;
	ObjDraw* stage = nullptr;

private:
	DirectXCommon* dxCommon = nullptr;
};