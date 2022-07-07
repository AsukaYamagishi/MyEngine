#pragma once
#include "Sprite.h"

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
    /// �`��
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    void Draw(ID3D12GraphicsCommandList* cmdList); 

   
private:
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
    /// �[�x�o�b�t�@/�f�v�X�X�e���V���r���[�쐬
    /// </summary>
    void CreateDSV();


#pragma endregion
};

