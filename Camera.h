#pragma once
#include <DirectXMath.h>
#include "Vector3.h"
using namespace DirectX;

class Camera
{
#pragma region �萔
protected: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
#pragma endregion

#pragma region �֐�
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="eye">���_</param>
	/// <param name="target">�����_</param>
	/// <param name="up">��x�N�g��</param>
	Camera(Vector3 eye, Vector3 target = { 0,0,0 }, Vector3 up = { 0,1,0 });

	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �r���[�s��X�V
	/// </summary>
	void UpdateViewMatrix();

	/// <summary>
	/// �ˉe�s��X�V
	/// </summary>
	void UpdateProjectionMatrix();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="eye">���_</param>
	static void Init(const XMFLOAT3 eye = { 0,100,100 });


	//�Q�b�^�[�E�Z�b�^�[
	/// <summary>
	/// �J�����Z�b�g
	/// </summary>
	/// <param name="cam">�J�������</param>
	static void SetCam(Camera* cam);
	/// <summary>
	/// �r���[�ˉe�s��擾
	/// </summary>
	/// <returns>�r���[�ˉe�s��</returns>
	const XMMATRIX& GetViewProjectionMatrix() { return matViewProjection; }
	/// <summary>
	/// ���݂̃J�������擾
	/// </summary>
	/// <returns>���݂̃J�������</returns>
	static Camera* GetCam() { return NowMatView; }
	/// <summary>
	/// �r���[�s��擾
	/// </summary>
	/// <returns>�r���[�s��</returns>
	XMMATRIX GetMatView() { return matView; }
	/// <summary>
	/// �v���W�F�N�V�����s��擾
	/// </summary>
	/// <returns>�v���W�F�N�V�����s��</returns>
	XMMATRIX GetMatProj() { return matProjection; }
#pragma endregion

#pragma region �ϐ�
public:
	Vector3 eye;			//���_���W
	Vector3 target;			//�����_���W
	Vector3 up;				//������x�N�g��
	Vector3 front;			//���ʃx�N�g��
	Vector3 angle;			//�p�x

protected:
	//���̃J����
	static Camera* NowMatView;
	//�r���[�s��
	XMMATRIX matView = XMMatrixIdentity();
	//�ˉe�s��
	XMMATRIX matProjection = XMMatrixIdentity();
	//�r���[�ˉe�s��
	XMMATRIX matViewProjection = XMMatrixIdentity();//���݂̂̃J����
#pragma endregion
};

