#pragma once
///<summary>
///�����蔻��v���~�e�B�u
///</summary>

#include <DirectXMath.h>

///<summary>
///��
///</summary>
struct Sphere {
	//���S���W
	DirectX::XMVECTOR centor = { 0,0,0 };
	//���a
	float radius = 1.0f;
};

///<summary>
///OBB
///</summary>
struct OBB {
	//���S���W
	DirectX::XMVECTOR centor = { 0,0,0 };
	//�����x�N�g��
	DirectX::XMVECTOR normalDirect[3];
	//�e�������̒���
	float length[3];
};
///<summary>
///����
///</summary>
struct Plane {
	//�@���x�N�g��
	DirectX::XMVECTOR normal = { 0,1,0 };
	//���_����̋���
	float distance = 0.0f;
};

///<summary>
///�@���t���O�p�`(���v��肪�\��)
///</summary>
class Triangle{
public:
	//���_���W3��
	DirectX::XMVECTOR p0;
	DirectX::XMVECTOR p1;
	DirectX::XMVECTOR p2;
	//�@���x�N�g��
	DirectX::XMVECTOR normal;
	//�@���̌v�Z
	void ComputeNormal();
};

/// <summary>
/// ���C
/// </summary>
struct Ray {
	//�n�_
	DirectX::XMVECTOR start = { 0,0,0,1 };
	//����
	DirectX::XMVECTOR dir = { 1,0,0,0 };
};