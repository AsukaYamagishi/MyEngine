#pragma once
#include<Windows.h>
#include<string>

#include"../Sprite.h"

class DebugText
{
#pragma region �萔
public:
	//�萔�̐錾
	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	static const int maxCharCount = 256; //1�t���[���ł̍ő�\��������
	static const int fontWidth = 9; //1�������̉���
	static const int fontHeight = 18; //1�������̏c��
	static const int fontLineCount = 14; //�摜��1�s���̕�����
#pragma endregion

#pragma region �֐�
public: //�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="texnumber">�e�L�X�g�摜���[�ԍ�</param>
	void Init(UINT texnumber);

	/// <summary>
	/// ������̒ǉ�
	/// </summary>
	/// <param name="text">�\������</param>
	/// <param name="x">x�ʒu</param>
	/// <param name="y">y�ʒu</param>
	/// <param name="scale">�傫��</param>
	void PrintDebugText(const std::string& text, float x, float y, float scale = 1.0f);
	
	/// <summary>
	/// ������̕\��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void DrawAll(ID3D12GraphicsCommandList* cmdList);
#pragma endregion

#pragma region �ϐ�
private: //�����o�ϐ�
	//�X�v���C�g�̔z��
	Sprite* textSprites[maxCharCount];
	//�z��̓Y����
	int textIndex = 0;
#pragma endregion
};

