#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <DirectXTex.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3dcompiler.lib")
using namespace Microsoft::WRL;
using namespace DirectX;

class Sprite
{
#pragma region �\����
public: //�\����
	//���_�f�[�^�\����
	struct VertexPosUv
	{
		XMFLOAT3 pos; //xyz
		XMFLOAT2 uv; //uv
	};
	//�萔�o�b�t�@�f�[�^�\���́i���肽���f�[�^���������炱���ɏ����j
	struct ConstBufferData
	{
		XMFLOAT4 color; //�F(RGBA)
		XMMATRIX mat; //3D�ϊ��s��
		float time; //����
	};
#pragma endregion

#pragma region �ϐ�
protected: //�ÓI�����o�ϐ�
	//�e�N�X�`���̍ő喇��
	static const int spriteSRVCount = 512; //�e�N�X�`���̍ő喇��
	//���_��
	static const int vertNum = 4;
	//�f�o�C�X
	static ID3D12Device* device;
	//�f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	//�R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;
	//�f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	//�e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
	//�ˉe�s��
	static XMMATRIX matProjection;

protected: //�����o�ϐ�
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�e�N�X�`���ԍ�
	UINT texNumber = 0;
	//Z���̉�]�p
	float rotation = 0.0f;
	//���[�J�����W
	XMFLOAT2 position = {};
	//�X�v���C�g���A����
	XMFLOAT2 size = { 100.0f,100.0f };
	//�A���J�[�|�C���g
	XMFLOAT2 anchorpoint = { 0,0 };
	//���[���h�ϊ��s��
	XMMATRIX matWorld{};
	//�F
	XMFLOAT4 color = { 1,1,1,1 };
	//���E���]
	bool isFlipX = false;
	//�㉺���]
	bool isFlipY = false;
	//�e�N�X�`���n�_
	XMFLOAT2 texBase = { 0,0 };
	//�e�N�X�`�����A����
	XMFLOAT2 texSize = { 100.0f,100.0f };
	
#pragma endregion

#pragma region �֐�
public: //�ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="dev">�f�o�C�X</param>
	/// <param name="window_width">�E�B���h�E������</param>
	/// <param name="window_height">�E�B���h�E�c����</param>
	/// <returns>����</returns>
	static bool StaticInit(ID3D12Device* dev, int window_width, int window_height);

	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// �X�v���C�g(�摜)����
	/// </summary>
	/// <param name="texNumber">�e�N�X�`���ۑ��ꏊ�ԍ�</param>
	/// <param name="position">�ʒu</param>
	/// <param name="color">�F(RGBA)</param>
	/// <param name="anchorpoint">�A���J�[�|�C���g(����)</param>
	/// <param name="isFlipX">���E���]</param>
	/// <param name="isFlipY">�㉺���]</param>
	/// <returns>�X�v���C�g�������</returns>
	static Sprite* CreateSprite(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1,1,1,1 }, XMFLOAT2 anchorpoint = { 0.0f,0.0f }, bool isFlipX = false, bool isFlipY = false);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="texnumber">�e�N�X�`���ۑ��ꏊ�ԍ�</param>
	/// <param name="filename">�t�@�C����</param>
	/// <returns>����</returns>
	static bool LoadTexture(UINT texnumber, const wchar_t* filename);

public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texNumber">�e�N�X�`���ۑ��ꏊ�ԍ�</param>
	/// <param name="position">�ʒu</param>
	/// <param name="size">�T�C�Y</param>
	/// <param name="color">�F(RGBA)</param>
	/// <param name="anchorpoint">�A���J�[�|�C���g(����)</param>
	/// <param name="isFlipX">���E���]</param>
	/// <param name="isFlopY">�㉺���]</param>
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlopY);
	
	/// <summary>
	/// ������
	/// </summary>
	/// <returns>����</returns>
	bool Init();
	
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �p�x�ύX�ݒ�
	/// </summary>
	/// <param name="rotation">�p�x</param>
	void SetRotation(float rotation);
	
	/// <summary>
	/// ���W�ύX�ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(XMFLOAT2 position);
	
	/// <summary>
	/// �T�C�Y�ݒ�
	/// </summary>
	/// <param name="size">�T�C�Y</param>
	void SetSize(XMFLOAT2 size);

	/// <summary>
	/// �A���J�[�|�C���g�ύX�ݒ�
	/// </summary>
	/// <param name="anchorpoint">�A���J�[�|�C���g(�ǂ�����ɂ��邩)</param>
	void SetAnchorPoint(XMFLOAT2 anchorpoint);

	/// <summary>
	/// ���E���]�ݒ�
	/// </summary>
	/// <param name="isFlipX">���E���]</param>
	void SetIsFlipX(bool isFlipX);

	/// <summary>
	/// �㉺���]�ݒ�
	/// </summary>
	/// <param name="isFlipY">�㉺���]</param>
	void SetIsFlipY(bool isFlipY);
	
	/// <summary>
	/// �e�N�X�`���͈͐ݒ�(�g���~���O)
	/// </summary>
	/// <param name="texBase">�e�N�X�`���n�_</param>
	/// <param name="texSize">�n�_����ɂ����T�C�Y</param>
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);

private: //�����o�֐�
	/// <summary>
	/// ���_�f�[�^�]��
	/// </summary>
	void TransferVertices();

protected:
	/// <summary>
	/// ���_�o�b�t�@����
	/// </summary>
	void CreateVertBuff();
#pragma endregion

};

