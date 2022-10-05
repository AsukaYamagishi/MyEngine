#pragma once
#include "../Sprite.h"

class MultiRenderTarget :
    public Sprite
{
#pragma region �ϐ�
public:
    //�e�N�X�`���o�b�t�@
    ComPtr<ID3D12Resource> texBuff[2];
    //SVR�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //�[�x�o�b�t�@
    ComPtr<ID3D12Resource> depthBuff;
    //RTV�p�f�X�N���v�^�q�[�v(�����_�[�^�[�Q�b�g�r���[)
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV�p�f�X�N���v�^�q�[�v(�f�v�X�X�e���V���r���[)
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
    //�O���t�B�b�N�X�p�C�v���C��
    ComPtr<ID3D12PipelineState> pipelineState;
    //���[�g�V�O�l�`��
    ComPtr<ID3D12RootSignature> rootSignature;
    //��ʃN���A�J���[
    static const float clearColor[4];
#pragma endregion

#pragma region �֐�
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MultiRenderTarget();

    /// <summary>
    /// ������
    /// </summary>
    void Init();

    /// <summary>
    /// �V�[���`��O����
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void Draw(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �V�[���`��㏈��
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);


private:

    /// <summary>
    /// �p�C�v���C������
    /// </summary>
    void CreateGraphicsPipelineState();

    /// <summary>
    /// �e�N�X�`������
    /// </summary>
    void CreateTexture();

    /// <summary>
    /// SRV�쐬
    /// </summary>
    void CreateSRV();

    /// <summary>
    /// �����_�[�^�[�Q�b�g�r���[�쐬
    /// </summary>
    void CreateRTV();

    /// <summary>
    /// �[�x�o�b�t�@����
    /// </summary>
    void CreateDepthBuff();

    /// <summary>
    /// �f�v�X�X�e���V���r���[�쐬
    /// </summary>
    void CreateDSV();


#pragma endregion
};

