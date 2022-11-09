#pragma once
#include "Vector3.h"
#include "Quaternion.h"
#include "Mathf.h"
#include <DirectXMath.h>

class Matrix4x4 : public DirectX::XMFLOAT4X4
{
public:
#pragma region �R���X�g���N�^
	Matrix4x4()
	{
		_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0;
		_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0;
		_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0;
		_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0;
	}

	Matrix4x4(
		float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44)
	{
		this->_11 = _11; this->_12 = _12; this->_13 = _13; this->_14 = _14;
		this->_21 = _21; this->_22 = _22; this->_23 = _23; this->_24 = _24;
		this->_31 = _31; this->_32 = _32; this->_33 = _33; this->_34 = _34;
		this->_41 = _41; this->_42 = _42; this->_43 = _43; this->_44 = _44;
	}

	Matrix4x4(const XMFLOAT4X4& num)
	{
		*this = num;
	}

#pragma endregion

#pragma region �ÓI�����o�֐�
	/// <summary>
	/// ���W���畽�s�ړ��s����쐬
	/// </summary>
	/// <param name="trans">���W�iVector3�j</param>
	/// <returns>���s�ړ��s��iMatrix4x4�j</returns>
	static Matrix4x4 Translation(const Vector3& trans);

	/// <summary>
	/// �X�P�[������g��s����쐬
	/// </summary>
	/// <param name="scale">�X�P�[���iVector3�j</param>
	/// <returns>�g��s��iMatrix4x4�j</returns>
	static Matrix4x4 Scale(const Vector3& scale);

	/// <summary>
	/// �N�H�[�^�j�I�������]�s����쐬
	/// </summary>
	/// <param name="quat">��]�p�N�H�[�^�j�I���iQuaternion�j</param>
	/// <returns>��]�s��iMatrix4x4�j</returns>
	static Matrix4x4 Rotate(const Quaternion& quat);

	/// <summary>
	/// ��]�s�񂩂�N�H�[�^�j�I���ɂ���]�����擾
	/// </summary>
	/// <param name="rotaMatrix">��]�s��iMatrix4x4�j</param>
	/// <returns>�N�H�[�^�j�I���ɂ���]�iQuaternion�j</returns>
	static Quaternion GetRotation(const Matrix4x4& rotaMatrix);

	/// <summary>
	/// �N�H�[�^�j�I���̔��]�s��𐶐�
	/// </summary>
	/// <param name="quat">�N�H�[�^�j�I���iQuaternion�j</param>
	/// <returns>���]�s��iMatrix4x4�j</returns>
	static Matrix4x4 Inverse(const Quaternion& quat);

#pragma endregion

#pragma region �ÓI�����o�ϐ�
	static const Matrix4x4 identity; //�P�ʍs��
	static const Matrix4x4 zero; //��s��

#pragma endregion

#pragma region �����o�֐�
	/// <summary>
	/// �ʒu�������o��
	/// </summary>
	/// <returns>�ʒu���</returns>
	Matrix4x4 ExtractTranslation();

	/// <summary>
	/// �X�P�[�����O�������o��
	/// </summary>
	/// <returns>�X�P�[�����</returns>
	Matrix4x4 ExtractScale();

	/// <summary>
	/// ��]�������o��
	/// </summary>
	/// <returns>��]���</returns>
	Matrix4x4 ExtractRotation();

#pragma endregion

#pragma region ���Z�q
	//XMMATRIX�Ƃ̌݊�
	operator XMMATRIX() const
	{
		XMMATRIX xmMatrix =
		{
			_11,_12,_13,_14,
			_21,_22,_23,_24,
			_31,_32,_33,_34,
			_41,_42,_43,_44
		};
		return xmMatrix;
	}

};

Matrix4x4& operator *=(Matrix4x4& lhs, const Matrix4x4& rhs);
Matrix4x4& operator *(const Matrix4x4& lhs, const Matrix4x4& rhs);

#pragma endregion