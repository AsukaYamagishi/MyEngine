#pragma once
#include "Sprite.h"
#include <map>

class PostEffect :
    public Sprite
{
#pragma region �ϐ�
public:
    //�e�N�X�`���o�b�t�@
    ComPtr<ID3D12Resource> texBuff;
    //SVR�p�f�X�N���v�^�q�[�v
    ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //�[�x�o�b�t�@
    ComPtr<ID3D12Resource> depthBuff;
    //RTV�p�f�X�N���v�^�q�[�v(�����_�[�^�[�Q�b�g�r���[)
    ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV�p�f�X�N���v�^�q�[�v(�f�v�X�X�e���V���r���[)
    ComPtr<ID3D12DescriptorHeap> descHeapDSV;
    //�O���t�B�b�N�X�p�C�v���C��
    std::map<std::string, ComPtr<ID3D12PipelineState>> pipelineStates;
    //���[�g�V�O�l�`��
    std::map<std::string, ComPtr<ID3D12RootSignature>> rootSignatures;
    //��ʃN���A�J���[
    static const float clearColor[4];
#pragma endregion

#pragma region �֐�
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PostEffect();

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
    void Draw(ID3D12GraphicsCommandList* cmdList, const std::string& shaderName);

    /// <summary>
    /// �V�[���`��㏈��
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

   
private:

    /// <summary>
    /// �p�C�v���C������
    /// </summary>
    void CreateGraphicsPipelineState(const std::string& shaderName);

    /// <summary>
    /// �����̃p�C�v���C�����܂Ƃ߂Đ���
    /// </summary>
    void CreateManyPipelines();

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

