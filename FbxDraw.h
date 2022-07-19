#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>

#include "FbxModel.h"
#include "FbxInput.h"
#include "Camera.h"

class FbxDraw
{
#pragma region �萔
protected: //�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


public: //�萔
	//�{�[���̍ő吔
	static const int MAX_BONES = 32;

public: //�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����(���W�ϊ��s��p)
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};
	//�萔�o�b�t�@�p�f�[�^�\����(�X�L�j���O)
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};
#pragma endregion

#pragma region �֐�
public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// ���t���[���X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// ���f���̃Z�b�g
	/// </summary>
	/// <param name="model">FBX���f��</param>
	void SetModel(FbxModel* model) { this->model = model; }

	/// <summary>
	/// �A�j���[�V�����Đ�
	/// </summary>
	/// <param name="isLoop">���[�v���邩</param>
	void PlayAnimation(bool isLoop = false);

	/// <summary>
	/// �A�j���[�V�����Đ���~
	/// </summary>
	void StopAnimation() { isPlay = false; }

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);


	//�Q�b�^�[
	Vector3 GetScale() { return scale; }
	Vector3 GetPosition() { return position; }
	Vector3 GetRotation() { return rotation; }

	//�Z�b�^�[
	void SetScale(Vector3 nextScale) { scale = nextScale; }
	void SetPosition(Vector3 nextPos) { position = nextPos; }
	void SetRotation(Vector3 nextRotate) { rotation = nextRotate; }

public: //�ÓI�����o�֐�
	//�Z�b�^�[
	static void SetDevice(ID3D12Device* dev) { FbxDraw::dev = dev; }
	static void SetCamera(Camera* cam) { FbxDraw::cam = cam; }

	/// <summary>
	/// �O���t�B�b�N�X�p�C�v���C���̐���
	/// </summary>
	static void CreateGraphicsPipeline();
#pragma endregion
	
#pragma region �ϐ�
protected: //�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;
	//�萔�o�b�t�@(�X�L��)
	ComPtr<ID3D12Resource> constBuffSkin;

private: //�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* dev;
	//�J����
	static Camera* cam;
	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelineState;

	//���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	//xyz������̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	//���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	//���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	//���f��
	FbxModel* model = nullptr;
	//1�t���[���̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���(�A�j���[�V����)
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;
	//�A�j���[�V�������[�v�Đ�
	bool isLoop = false;
#pragma endregion
};

