#pragma once
#include <DirectXMath.h>
#include "Mathf.h"

using namespace DirectX;

struct Vector3 : public XMFLOAT3
{
#pragma region �R���X�g���N�^
	Vector3(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3(const XMFLOAT3& num) {
		this->x = num.x;
		this->y = num.y;
		this->z = num.z;
	}
	Vector3(const XMVECTOR& other) :XMFLOAT3() {
		XMVECTOR temp = other;
		XMStoreFloat3(this, temp);
	}
#pragma endregion

#pragma region �ÓI�����o�ϐ�
	static const Vector3 forward; //( 0, 0, 1) �O�x�N�g��
	static const Vector3 back;    //( 0, 0,-1) ���x�N�g��
	static const Vector3 up;	  //( 0, 1, 0) ��x�N�g��
	static const Vector3 down;	  //( 0,-1, 0) ���x�N�g��
	static const Vector3 right;	  //( 1, 0, 0) �E�x�N�g��
	static const Vector3 left;	  //(-1, 0, 0) ���x�N�g��
	static const Vector3 zero;	  //( 0, 0, 0) �[���x�N�g��
	static const Vector3 one;	  //( 1, 1, 1) 1(�P��)�x�N�g��
	static const Vector3 positive_infinity; //( inf, inf, inf) ���̖���
	static const Vector3 negative_infinity; //(-inf,-inf,-inf) ���̖���

#pragma endregion

#pragma region �ÓI�����o�֐�
	/// <summary>
	/// 2�_�Ԃ̊p�x�����߂�
	/// </summary>
	/// <param name="from">���茳�x�N�g��</param>
	/// <param name="to">�����x�N�g��</param>
	/// <returns>�p�x�Fdegree�ifloat�j</returns>
	static float Angle(const Vector3& from, const Vector3& to);

	/// <summary>
	/// 2�̃x�N�g���̓���
	/// </summary>
	/// <returns>���ρifloat�j</returns>
	static float Dot(const Vector3& lhs, const Vector3& rhs);

	/// <summary>
	/// 2�̃x�N�g���̊O��
	/// </summary>
	/// <returns>�O�ρiVector3�j</returns>
	static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

	/// <summary>
	/// ���K���x�N�g���̍쐬�i���l���������j
	/// </summary>
	/// <param name="valuse">���K���������x�N�g��</param>
	/// <returns>�쐬�������K���x�N�g���iVector3�j</returns>
	static Vector3 Nomalize(Vector3& valuse);

	/// <summary>
	/// 2�̃x�N�g���̊e���������ԑ傫�Ȓl�Ńx�N�g�����쐬
	/// </summary>
	/// <returns>�쐬�����x�N�g���iVector3�j</returns>
	static Vector3 Max(const Vector3& lhs, const Vector3& rhs);

	/// <summary>
	/// 2�̃x�N�g���̊e���������ԏ����Ȓl�Ńx�N�g�����쐬
	/// </summary>
	/// <returns>�쐬�����x�N�g���iVector3�j</returns>
	static Vector3 Min(const Vector3& lhs, const Vector3& rhs);

	/// <summary>
	/// �ڕW�l�܂Ŏw�肵���ړ��ʂňړ�����
	/// </summary>
	/// <param name="current">���ݒl</param>
	/// <param name="target">�ڕW�l</param>
	/// <param name="max_distance_delta">1�t���[���Ői�ދ���</param>
	/// <returns>�ړ����ʁiVector3�j</returns>
	static Vector3 MoveTowards(const Vector3& current, const Vector3& target, float max_distance_delta);

	/// <summary>
	/// �x�N�g���̑傫���𐧌�
	/// </summary>
	/// <param name="vec">�R�s�[����x�N�g��</param>
	/// <param name="max_length">�ő�̑傫��</param>
	/// <returns>�傫���� max_length �ȉ��ɐ������� vec �̃R�s�[</returns>
	static Vector3 ClampLength(const Vector3& vec, const float& max_length);

	/// <summary>
	/// �@���Œ�`���ꂽ���ʂŃx�N�g���𔽎�
	/// </summary>
	/// <param name="inDirection">���ʂɓ�������x�N�g��</param>
	/// <param name="inNormal">���ʂ��`���鐳�K���ς݂̐����x�N�g��</param>
	/// <returns>���ˌ�̃x�N�g���iVector3�j</returns>
	static Vector3 Reflect(const Vector3& inDirection, const Vector3& inNormal);

	/// <summary>
	/// 2�_�Ԃ̋��������߂�
	/// </summary>
	/// <returns>2�_�Ԃ̋����ifloat�j</returns>
	static float Distance(const Vector3& lhs, const Vector3& rhs);

	/// <summary>
	/// 2�̃x�N�g���̊e��������Z����
	/// </summary>
	/// <returns>��Z���ʁiVector3�j</returns>
	static Vector3 Scale(const Vector3& lhs, const Vector3& rhs);

#pragma endregion

#pragma region �����o�֐�
	/// <summary>
	/// �x�N�g���̒���
	/// </summary>
	/// <returns>�x�N�g���̒����ifloat�j</returns>
	float Length() const;

	/// <summary>
	/// �x�N�g���̒����̓��
	/// </summary>
	/// <returns>�x�N�g���̒����̓��ifloat�j</returns>
	float SqrLength() const;

	/// <summary>
	/// ���K���x�N�g��
	/// </summary>
	/// <returns>���K���x�N�g���iVector3�j</returns>
	Vector3 Normalized() const;

#pragma endregion

#pragma region ���Z�q
	//�P�����Z�q
	Vector3 operator +() const { return *this; }
	Vector3 operator -() const
	{
		Vector3 temp = {
			-this->x,
			-this->y,
			-this->z
		};
		return temp;
	}

	//�񍀉��Z�q
	Vector3 operator +(const Vector3& vec) const
	{
		Vector3 temp = {
			this->x + vec.x,
			this->y + vec.y,
			this->z + vec.z
		};
		return temp;
	}
	Vector3 operator -(const Vector3& vec) const { return *this + -vec; }
	Vector3& operator +=(const Vector3& vec) {
		*this = *this + vec;
		return *this;
	}
	Vector3& operator -=(const Vector3& vec) {
		*this = *this + -vec;
		return *this;
	}


	//��r���Z�q
	bool operator ==(const Vector3& vec) const
	{
		bool temp{
			x == vec.x &&
			y == vec.y &&
			z == vec.z
		};
		return temp;
	}
	bool operator !=(const Vector3& vec) const { return!(*this == vec); }

	//�Y�������Z�q
	float operator [](const std::size_t& index) const
	{
		if (index == 0) return this->x;
		if (index == 1) return this->y;
		if (index == 2) return this->z;

		//�͈͊O�Q��
		return 0.0f;
	}
};

inline Vector3 operator *(const Vector3& vec, const float& num) 
{
	Vector3 temp = {
		vec.x * num,
		vec.y * num,
		vec.z * num,
	};
	return temp;
}
inline Vector3 operator *(const float& num, const Vector3& vec)
{
	Vector3 temp = vec * num;
	return temp;
}
inline Vector3 operator /(const Vector3& vec, const float& num)
{
	Vector3 temp = {
			vec.x / num,
			vec.y / num,
			vec.z / num,
	};
	return temp;
}
inline Vector3& operator *=(Vector3& vec, const float& num) {
	vec = vec * num;
	return vec;
}
inline Vector3& operator /=(Vector3& vec, const float& num) {
	vec = vec / num;
	return vec;
}

#pragma endregion