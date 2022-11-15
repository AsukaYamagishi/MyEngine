#pragma once
#include "../../DirectXBase/DirectXCommon.h"
#include "../../3d/Obj/ObjDraw.h"
#include "../../Manager/ModelManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../Player/PlayerBase.h"

class Stage : public GameObjectBase {
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::��ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Stage(DirectXCommon* dxCommon, PlayerBase* player);
	~Stage();
	void Init() override;

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update() override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

public:
	std::shared_ptr<ObjDraw> skydome = nullptr;
	std::shared_ptr<ObjDraw> stage = nullptr;
	PlayerBase* playerData;

private:
	DirectXCommon* dxCommon = nullptr;
};