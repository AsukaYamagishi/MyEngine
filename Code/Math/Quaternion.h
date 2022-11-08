#pragma once
#include "Vector3.h"
#include <DirectXMath.h>

class Quaternion : public XMFLOAT4
{
public:
#pragma region �R���X�g���N�^
	//�������w�肵�Đ����i�񐄏��j
	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//�C�ӎ�����̉�]�̎w�肩�琶��
	Quaternion(const Vector3& axis_normal, float degree)
	{
		float _sin = sin(degree / 2.0f);
		*this = Quaternion(_sin * axis_normal.x, _sin * axis_normal.y, _sin * axis_normal.z, cos(degree / 2.0f));
	}

#pragma endregion

#pragma region �ÓI�����o�֐�
	/// <summary>
	/// 2�̉�]�̊Ԃ̊p�x��Ԃ�
	/// </summary>
	/// <param name="from">���茳</param>
	/// <param name="to">�����</param>
	/// <returns>�p�x:degree�ifloat�j</returns>
	static float Angle(const Quaternion& from, const Quaternion& to);

	/// <summary>
	/// 2�̉�]�̓��ς�Ԃ�
	/// </summary>
	/// <returns>����:degree�ifloat�j</returns>
	static float Dot(const Quaternion& lhs, const Quaternion& rhs);

	/// <summary>
	/// �I�C���[���N�H�[�^�j�I���ϊ��ifloat3�v�f�j
	/// </summary>
	/// <param name="">roll,pitch,yaw�irad�j</param>
	/// <returns>�ϊ���iQuaternion�j</returns>
	static Quaternion Euler(const float& roll, const float& pitch, const float& yaw);

	/// <summary>
	/// �I�C���[���N�H�[�^�j�I���ϊ��iVector3�j
	/// </summary>
	/// <param name="">roll,pitch,yaw�irad�j</param>
	/// <returns>�ϊ���iQuaternion�j</returns>
	static Quaternion Euler(const Vector3& rotaVector);

	/// <summary>
	/// �N�H�[�^�j�I���̐��K���i������������j
	/// </summary>
	/// <returns>���K�������N�H�[�^�j�I���iQuaternion�j</returns>
	static Quaternion Normalize(Quaternion& quat);

#pragma endregion

#pragma region �����o�֐�
	/// <summary>
	/// ���K�������N�H�[�^�j�I����Ԃ��i���������Ȃ��j
	/// </summary>
	/// <returns>���K�������N�H�[�^�j�I���iQuaternion�j</returns>
	Quaternion Normalized() const;

	/// <summary>
	/// �N�H�[�^�j�I�����I�C���[�ϊ�
	/// </summary>
	/// <returns>�I�C���[�p�iVector3�j</returns>
	Vector3 EulerAngles() const;

#pragma endregion

#pragma region ���Z�q
	//�P�����Z�q�I�[�o�[���[�h
	Quaternion operator +()
	{
		return *this;
	}
	Quaternion operator -()
	{
		Quaternion temp = {
			-this->x,
			-this->y,
			-this->z,
			-this->w
		};
		return temp;
	}

	//������Z�q�I�[�o�[���[�h
	Quaternion& operator +=(const Quaternion& quat)
	{
		this->x += quat.x;
		this->y += quat.y;
		this->z += quat.z;
		this->w += quat.w;

		return *this;
	}
	Quaternion& operator -=(const Quaternion& quat)
	{
		this->x -= quat.x;
		this->y -= quat.y;
		this->z -= quat.z;
		this->w -= quat.w;

		return *this;
	}
	Quaternion& operator *=(float s)
	{
		this->x *= s;
		this->y *= s;
		this->z *= s;
		this->w *= s;

		return *this;
	}
	Quaternion& operator *=(const Quaternion& quat)
	{
		Quaternion temp{
			 this->x * quat.w + this->y * quat.z - this->z * quat.y + this->w * quat.x, //x����
			-this->x * quat.z + this->y * quat.w + this->z * quat.x + this->w * quat.y, //y����
			 this->x * quat.y - this->y * quat.x + this->z * quat.w + this->w * quat.z, //z����
			-this->x * quat.x - this->y * quat.y - this->z * quat.z + this->w * quat.w  //w����
		};
		*this = temp;
		return *this;
	}
	Quaternion& operator /=(float s)
	{
		return *this *= 1.0f / s;
	}

	//��r���Z�q
	bool operator ==(const Quaternion& quat) const
	{
		bool temp{
			x == quat.x &&
			y == quat.y &&
			z == quat.z &&
			w == quat.w
		};
		return temp;
	}
	bool operator !=(const Quaternion& quat) const
	{
		return !(*this == quat);
	}

	//�Y�������Z�q
	float& operator [](const std::size_t& index)
	{
		if (index == 0)return this->x;
		if (index == 1)return this->y;
		if (index == 2)return this->z;
		if (index == 3)return this->w;

		//�͈͊O�Q��
		assert(0);
	}
};

//�񍀉��Z�q�I�[�o�[���[�h
inline Quaternion operator +(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion result = q1;
	return result += q2;
}
inline Quaternion operator -(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion result = q1;
	return result -= q2;
}
inline Quaternion operator *(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion result = q1;
	return result *= q2;
}
inline Quaternion operator *(const Quaternion& q, float s)
{
	Quaternion result = q;
	return result *= s;
}
inline Quaternion operator *(float s, const Quaternion& q)
{
	Quaternion result = q;
	return result *= s;
}
inline Quaternion operator /(const Quaternion& q, float s)
{
	Quaternion result = q;
	return result /= s;
}
inline Vector3 operator *(const Quaternion& rota, const Vector3& point)
{
	float x = rota.x * 2.0f;
	float y = rota.x * 2.0f;
	float z = rota.x * 2.0f;
	float xx = rota.x * x;
	float yy = rota.y * y;
	float zz = rota.z * z;
	float xy = rota.x * y;
	float xz = rota.x * z;
	float yz = rota.y * z;
	float wx = rota.w * x;
	float wy = rota.w * y;
	float wz = rota.w * z;

	Vector3 res;
	res.x = (1.0f - (yy + zz)) * point.x + (xy - wz) * point.y + (xz + wy) * point.z;
	res.y = (xy + wz) * point.x + (1.0f - (xx + zz)) * point.y + (yz - wx) * point.z;
	res.z = (xz - wy) * point.x + (yz + wx) * point.y + (1.0f - (xx + yy)) * point.z;
	return res;
}

#pragma endregion