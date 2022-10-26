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
		Vector3 temp ={
			this->x + vec.x,
			this->y + vec.y,
			this->z + vec.z
		};
		return temp;
	}

	Vector3 operator += (const Vector3& r) {
		*this = *this + r;
		return *this;
	}
	Vector3 operator -= (const Vector3& r) {
		*this = *this + -r;
		return *this;
	}


	//���Z
	inline bool operator == (const Vector3& r) const { return x == r.x && y == r.y && z == r.z; }
	inline bool operator != (const Vector3& r) const { return x != r.x || y != r.y || z != r.z; }
	inline XMVECTOR operator * (const float r) const { return Vector3(x * r, y * r, z * r); }
	inline XMVECTOR operator / (const float r) const { return Vector3(x / r, y / r, z / r); }

	
	// �x�N�g���̓���
	float VDot(Vector3 In) { return x * In.x + y * In.y + z * In.z; }
	// �x�N�g���̊O��
	Vector3 VCross(Vector3 In) { return Vector3(y * In.z - z * In.y, z * In.x - x * In.z, x * In.y - y * In.x); }
	// �x�N�g���̃X�P�[�����O
	Vector3 VScale(float Scale) { Vector3 Result = { x * Scale, y * Scale, z * Scale }; return Result; }

	//���
	Vector3& operator = (const XMVECTOR& other) {
		XMVECTOR temp = other;
		XMStoreFloat3(this, temp);
		return *this;
	}
	//�L���X�g
	operator XMVECTOR() const {
		return XMLoadFloat3(this);
	}
	//����
	float Length() const {
		return (static_cast<Vector3>(XMVector3Length(XMVECTOR(*this)))).x;
	}

	//�x�N�g���̒��������߂�
	float length() const
	{
		return (float)sqrtf(x * x + y * y + z * z);
	}

	//�������
	float LengthSq() const {
		return (float)pow(this->Length(),2);
	}
	//���K��
	Vector3 Normal() {
		return XMVector3Normalize(XMVECTOR(*this));
	}
	void Normalize() {
		*this = XMVector3Normalize(XMVECTOR(*this));
	}

	//��]
	void RotationX(float angle) {
	}
	void AddRotationY(float angle) {
		*this = {
			this->x * cosf(angle)	+0			+this->z * sinf(angle),
			0						+this->y	+0,	
			this->x * -sinf(angle)	+0			+this->z * cosf(angle)
		};
	}
	void RotationZ(float angle) {
	}
};
