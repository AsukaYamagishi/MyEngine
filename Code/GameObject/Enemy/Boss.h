#pragma once
#include "../SafeDelete.h"
#include "../../DirectXBase/DirectXCommon.h"
#include "../../3d/Obj/ObjDraw.h"
#include "../ModelManager.h"
#include <DirectXMath.h>


class Boss {
#pragma region �萔
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
#pragma endregion

#pragma region �֐�
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Boss();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Boss();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dxCommon">��b����</param>
	void Init(DirectXCommon *dxCommon);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
#pragma endregion

#pragma region �ϐ�
public:

private:
	DirectXCommon *dxCommon = nullptr;
#pragma endregion
};