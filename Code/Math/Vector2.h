#pragma once
#include <DirectXMath.h>
#include "Mathf.h"
#include "Vector3.h"
using namespace DirectX;

struct Vector2 : public XMFLOAT2
{
#pragma region �R���X�g���N�^
	Vector2() {
		x = 0.0f;
		y = 0.0f;
	}
	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Vector2(const XMFLOAT3& num) {
		this->x = num.x;
		this->y = num.y;
	}
	Vector2(const XMVECTOR& other) {
		XMVECTOR temp = other;
		XMStoreFloat2(this, temp);
	}
#pragma endregion

#pragma region �ÓI�����o�ϐ�
	static const Vector2 up;	  //( 0, 1) ��x�N�g��
	static const Vector2 down;	  //( 0,-1) ���x�N�g��
	static const Vector2 right;	  //( 1, 0) �E�x�N�g��
	static const Vector2 left;	  //(-1, 0) ���x�N�g��
	static const Vector2 zero;	  //( 0, 0) �[���x�N�g��
	static const Vector2 one;	  //( 1, 1) 1(�P��)�x�N�g��
	static const Vector2 positive_infinity; //( inf, inf) ���̖���
	static const Vector2 negative_infinity; //(-inf,-inf) ���̖���

#pragma endregion

#pragma region �ÓI�����o�֐�
	/// <summary>
	/// 2�_�Ԃ̊p�x�����߂�
	/// </summary>
	/// <param name="from">���茳�x�N�g��</param>
	/// <param name="to">�����x�N�g��</param>
	/// <returns>�p�x�Fdegree�ifloat�j</returns>
	static float Angle(const Vector2& from, const Vector2& to);

	/// <summary>
	/// 2�̃x�N�g���̓���
	/// </summary>
	/// <returns>���ρifloat�j</returns>
	static float Dot(const Vector2& lhs, const Vector2& rhs);

	/// <summary>
	/// 2�̃x�N�g���̊e���������ԑ傫�Ȓl�Ńx�N�g�����쐬
	/// </summary>
	/// <returns>�쐬�����x�N�g���iVector2�j</returns>
	static Vector2 Max(const Vector2& lhs, const Vector2& rhs);

	/// <summary>
	/// 2�̃x�N�g���̊e���������ԏ����Ȓl�Ńx�N�g�����쐬
	/// </summary>
	/// <returns>�쐬�����x�N�g���iVector2�j</returns>
	static Vector2 Min(const Vector2& lhs, const Vector2& rhs);

	/// <summary>
	/// �x�N�g���̑傫���𐧌�
	/// </summary>
	/// <param name="vec">�R�s�[����x�N�g��</param>
	/// <param name="max_length">�ő�̑傫��</param>
	/// <returns>�傫���� max_length �ȉ��ɐ������� vec �̃R�s�[</returns>
	static Vector2 ClampLength(const Vector2& vec, const float& max_length);

	/// <summary>
	/// �@���Œ�`���ꂽ���ʂŃx�N�g���𔽎�
	/// </summary>
	/// <param name="inDirection">���ʂɓ�������x�N�g��</param>
	/// <param name="inNormal">���ʂ��`���鐳�K���ς݂̐����x�N�g��</param>
	/// <returns>���ˌ�̃x�N�g���iVector2�j</returns>
	static Vector2 Reflect(const Vector2& inDirection, const Vector2& inNormal);

	/// <summary>
	/// 2�_�Ԃ̋��������߂�
	/// </summary>
	/// <returns>2�_�Ԃ̋����ifloat�j</returns>
	static float Distance(const Vector2& lhs, const Vector2& rhs);

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
	/// <returns>���K���x�N�g���iVector2�j</returns>
	Vector2 Normalized() const;

	/// <summary>
	/// 2�̃x�N�g���̓���(����1��)
	/// </summary>
	/// <returns>���ρifloat�j</returns>
	float Dot(const Vector2& vec);

#pragma endregion

#pragma region ���Z�q
	//�P�����Z�q
	Vector2 operator +() const { return *this; }
	Vector2 operator -() const
	{
		Vector2 temp = {
			-this->x,
			-this->y,
		};
		return temp;
	}

	//�񍀉��Z�q
	Vector2 operator +(const Vector2& vec) const
	{
		Vector2 temp = {
			this->x + vec.x,
			this->y + vec.y
		};
		return temp;
	}
	Vector2 operator -(const Vector2& vec) const 
	{ 
		return *this + -vec;
	}
	Vector2& operator +=(const Vector2& vec) {
		*this = *this + vec;
		return *this;
	}
	Vector2& operator -=(const Vector2& vec) {
		*this = *this + -vec;
		return *this;
	}
	//��Z�E���Z�͉���

	//��r���Z�q
	bool operator ==(const Vector2& vec) const
	{
		bool temp{
			x == vec.x &&
			y == vec.y
		};
		return temp;
	}
	bool operator !=(const Vector3& vec) const 
	{
		return !(*this == vec);
	}

	//�Y�������Z�q
	float operator [](const std::size_t& index) const
	{
		if (index == 0) return this->x;
		if (index == 1) return this->y;

		//�͈͊O�Q��
		return 0.0f;
	}

	//Vector3�ւ̃L���X�g
	operator Vector3() const
	{
		Vector3 temp{
			this->x,
			this->y,
			0.0f
		};
		return temp;
	}
};

inline Vector2 operator *(const Vector2& vec, const float& num)
{
	Vector2 temp = {
		vec.x * num,
		vec.y * num
	};
	return temp;
}
inline Vector2 operator *(const float& num, const Vector2& vec)
{
	Vector2 temp = vec * num;
	return temp;
}
inline Vector2 operator *(const Vector2& a, const Vector2& b)
{
	Vector2 temp = {
		a.x * b.x,
		a.y * b.y
	};
	return temp;
}
inline Vector2 operator /(const Vector2& vec, const float& num)
{
	Vector2 temp = {
			vec.x / num,
			vec.y / num
	};
	return temp;
}
inline Vector2& operator *=(Vector2& vec, const float& num) {
	vec = vec * num;
	return vec;
}
inline Vector2& operator /=(Vector2& vec, const float& num) {
	vec = vec / num;
	return vec;
}

#pragma endregion
