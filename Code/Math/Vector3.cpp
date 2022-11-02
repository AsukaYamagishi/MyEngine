#include "Vector3.h"

#pragma region Ã“Iƒƒ“ƒo•Ï”‚Ì‰Šú‰»
const Vector3 Vector3::forward{ 0.0f,0.0f,1.0f }; // (  0,  0,  1 )
const Vector3 Vector3::back{ 0.0f,0.0f,-1.0f };   // (  0,  0, -1 )
const Vector3 Vector3::up{ 0.0f,1.0f,0.0f };      // (  0,  1,  0 )
const Vector3 Vector3::down{ 0.0f,-1.0f,0.0f };   // (  0, -1,  0 )
const Vector3 Vector3::right{ 1.0f,0.0f,0.0f };   // (  1,  0,  0 )
const Vector3 Vector3::left{ -1.0f,0.0f,0.0f };   // ( -1,  0,  0 )
const Vector3 Vector3::zero{ 0.0f,0.0f,0.0f };    // (  0,  0,  0 )
const Vector3 Vector3::one{ 1.0f,1.0f,1.0f };     // (  1,  1,  1 )
const Vector3 Vector3::positive_infinity{ Mathf::infinity ,Mathf::infinity ,Mathf::infinity };
const Vector3 Vector3::negative_infinity{ Mathf::negative_infinity,Mathf::negative_infinity ,Mathf::negative_infinity };
#pragma endregion

float Vector3::Angle(const Vector3& from, const Vector3& to)
{
    float cos_sita = Dot(from, to) / (from.Length() * to.Length());
    float angle = acos(cos_sita);
    return angle;
}

float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
{
    float dot = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    return dot;
}

Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 cross = {
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    };
    return cross;
}

Vector3 Vector3::Nomalize(Vector3& valuse)
{
    valuse = valuse.Normalized();
    return valuse;
}

Vector3 Vector3::Max(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 max = {
        lhs.x > rhs.x ? lhs.x : rhs.x, //if(lhs.x > rhs.x)
        lhs.y > rhs.y ? lhs.y : rhs.y, //if(lhs.y > rhs.y)
        lhs.z > rhs.z ? lhs.z : rhs.z  //if(lhs.z > rhs.z)
    };
    return max;
}

Vector3 Vector3::Min(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 min = {
        lhs.x < rhs.x ? lhs.x : rhs.x, //if(lhs.x < rhs.x)
        lhs.y < rhs.y ? lhs.y : rhs.y, //if(lhs.y < rhs.y)
        lhs.z < rhs.z ? lhs.z : rhs.z  //if(lhs.z < rhs.z)
    };
    return min;
}

Vector3 Vector3::MoveTowards(const Vector3& current, const Vector3& target, float max_distance_delta)
{
    Vector3 normal{ Vector3(target - current) };
    float distance = Vector3::Distance(current, target);
    if (distance - max_distance_delta > 0.0f)
    {
        return current + normal.Normalized() * max_distance_delta;
    }
    return target;
}

Vector3 Vector3::ClampLength(const Vector3& vec, const float& max_length)
{
    Vector3 clamp = {
        vec.x < max_length ? vec.x : max_length, //if(vec.x < maxLength) true:vec.x/false:maxLength return
        vec.y < max_length ? vec.y : max_length, //if(vec.y < maxLength) true:vec.y/false:maxLength return
        vec.z < max_length ? vec.z : max_length  //if(vec.z < maxLength) true:vec.z/false:maxLength return
    };
    return clamp;
}

Vector3 Vector3::Reflect(const Vector3& inDirection, const Vector3& inNormal)
{
    Vector3 reflect = inDirection - 2.0f * Dot(inDirection, inNormal) * inNormal;
    return reflect;
}

float Vector3::Distance(const Vector3& lhs, const Vector3& rhs)
{
    float distance = (lhs - rhs).Length();
    return distance;
}

Vector3 Vector3::Scale(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 scale
    {
        lhs.x * rhs.x,
        lhs.y * rhs.y,
        lhs.z * rhs.z
    };
    return scale;
}

float Vector3::Length() const
{
    float length = sqrtf(x * x + y * y + z * z);
    return length;
}

float Vector3::SqrLength() const
{
    float length = this->Length();
    float sqrLength = length * length;
    return sqrLength;
}

Vector3 Vector3::Normalized() const
{
    float length = this->Length();
    Vector3 normalized =
    {
        this->x / length,
        this->y / length,
        this->z / length,
    };
    return normalized;
}
