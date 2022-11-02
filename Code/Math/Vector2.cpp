#include "Vector2.h"

#pragma region Ã“Iƒƒ“ƒo•Ï”‚Ì‰Šú‰»
const Vector2 Vector2::up{ 0.0f,1.0f };			// (  0,  1 )
const Vector2 Vector2::down{ 0.0f,-1.0f };		// (  0, -1 )
const Vector2 Vector2::right{ 1.0f,0.0f };		// (  1,  0 )
const Vector2 Vector2::left{ -1.0f,0.0f };		// ( -1,  0 )
const Vector2 Vector2::zero{ 0.0f,0.0f };		// (  0,  0 )
const Vector2 Vector2::one{ 1.0f,1.0f };		// (  1,  1 )
const Vector2 Vector2::positive_infinity{ Mathf::infinity ,Mathf::infinity };		// (  inf,  inf )
const Vector2 Vector2::negative_infinity{ Mathf::negative_infinity ,Mathf::negative_infinity };		// ( -inf, -inf )
#pragma endregion

float Vector2::Angle(const Vector2& from, const Vector2& to)
{
	float cos_sita = Dot(from, to) / (from.Length() * to.Length());
	float angle = acos(cos_sita);
	return angle;
}

float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
{
	float dot = lhs.x * rhs.x + lhs.y * rhs.y;
	return dot;
}

Vector2 Vector2::Max(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 max = {
		lhs.x > rhs.x ? lhs.x : rhs.x, //if(lhs.x > rhs.x)
		lhs.y > rhs.y ? lhs.y : rhs.y, //if(lhs.y > rhs.y)
	};
	return max;
}

Vector2 Vector2::Min(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 min = {
		lhs.x < rhs.x ? lhs.x : rhs.x, //if(lhs.x < rhs.x)
		lhs.y < rhs.y ? lhs.y : rhs.y, //if(lhs.y < rhs.y)
	};
	return min;
}

Vector2 Vector2::ClampLength(const Vector2& vec, const float& max_length)
{
	Vector2 clamp = {
			vec.x < max_length ? vec.x : max_length, //if(vec.x < maxLength) true:vec.x/false:maxLength return
			vec.y < max_length ? vec.y : max_length, //if(vec.y < maxLength) true:vec.y/false:maxLength return
	};
	return clamp;
}

Vector2 Vector2::Reflect(const Vector2& inDirection, const Vector2& inNormal)
{
	Vector2 reflect = inDirection - 2.0f * Dot(inDirection, inNormal) * inNormal;
	return reflect;
}

float Vector2::Distance(const Vector2& lhs, const Vector2& rhs)
{
	float distance = (lhs - rhs).Length();
	return distance;
}

float Vector2::Length() const
{
	float length = XMVector2Length(XMLoadFloat2(this)).m128_f32[0];
	return length;
}

float Vector2::SqrLength() const
{
	float length = this->Length();
	float sqrLength = length * length;
	return sqrLength;
}

Vector2 Vector2::Normalized() const
{
	Vector2 normalized = XMVector2Normalize(XMLoadFloat2(this));
	return normalized;
}

float Vector2::Dot(const Vector2& vec)
{
	float dot = x * vec.x + y * vec.y;
	return dot;
}
