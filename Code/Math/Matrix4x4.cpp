#include "Matrix4x4.h"

#pragma region ê√ìIÉÅÉìÉoïœêîÇÃèâä˙âª
const Matrix4x4 Matrix4x4::identity //íPà çsóÒ
{
	1.0f,0.0f,0.0f,0.0,
	0.0f,1.0f,0.0f,0.0,
	0.0f,0.0f,1.0f,0.0,
	0.0f,0.0f,0.0f,1.0
};

const Matrix4x4 Matrix4x4::zero //ãÛçsóÒ
{
	0.0f,0.0f,0.0f,0.0,
	0.0f,0.0f,0.0f,0.0,
	0.0f,0.0f,0.0f,0.0,
	0.0f,0.0f,0.0f,0.0
};

#pragma endregion

Matrix4x4 Matrix4x4::Translation(const Vector3& trans)
{
	Matrix4x4 mat
	{
		1.0f,    0.0f,    0.0f,    0.0f,
		0.0f,    1.0f,    0.0f,    0.0f,
		0.0f,    0.0f,    1.0f,    0.0f,
		trans.x, trans.y, trans.z, 1.0f
	};
	return mat;
}

Matrix4x4 Matrix4x4::Scale(const Vector3& scale)
{
	Matrix4x4 mat
	{
		scale.x, 0.0f,    0.0f,    0.0f,
		0.0f,    scale.y, 0.0f,    0.0f,
		0.0f,    0.0f,    scale.z, 0.0f,
		0.0f,    0.0f,    0.0f,    1.0f
	};
	return mat;
}

Matrix4x4 Matrix4x4::Rotate(const Quaternion& quat)
{
	Matrix4x4 mat
	{
		// 11Å`14
		1.0f - 2.0f * quat.y * quat.y - 2.0f * quat.z * quat.z,
		2.0f * quat.x * quat.y + 2.0f * quat.w * quat.z,
		2.0f * quat.x * quat.z - 2.0f * quat.w * quat.y,
		0.0f,

		// 21Å`24
		2.0f * quat.x * quat.y - 2.0f * quat.w * quat.z,
		1.0f - 2.0f * quat.x * quat.x - 2.0f * quat.z * quat.z,
		2.0f * quat.y * quat.z + 2.0f * quat.w * quat.x,
		0.0f,

		// 31Å`34
		2.0f * quat.x * quat.z + 2.0f * quat.w * quat.y,
		2.0f * quat.y * quat.z - 2.0f * quat.w * quat.x,
		1.0f - 2.0f * quat.x * quat.x - 2.0f * quat.y * quat.y,
		0.0f,

		// 41Å`44
		0.0f,
		0.0f,
		0.0f,
		1.0f
	};

	return mat;
}

Quaternion Matrix4x4::GetRotation(const Matrix4x4& rotaMatrix)
{
	float data[4];
	data[0] =  rotaMatrix.m[0][0] - rotaMatrix.m[1][1] - rotaMatrix.m[2][2] + 1.0f;
	data[1] = -rotaMatrix.m[0][0] + rotaMatrix.m[1][1] - rotaMatrix.m[2][2] + 1.0f;
	data[2] = -rotaMatrix.m[0][0] - rotaMatrix.m[1][1] + rotaMatrix.m[2][2] + 1.0f;
	data[3] =  rotaMatrix.m[0][0] + rotaMatrix.m[1][1] + rotaMatrix.m[2][2] + 1.0f;

	int index = 0;
	for (int i = 1; i < 4; i++)
	{
		if (data[i] > data[index])
		{
			index = i;
		}
	}

	if (data[index] < 0.0f)
	{
		assert(0);
	}

	Quaternion result;
	float v = sqrtf(data[index]) * 0.5f;
	result[index] = v;
	float mult = 0.25f / v;

	switch (index)
	{
	case 0:
		result[1] = (rotaMatrix.m[0][1] + rotaMatrix.m[1][0]) * mult;
		result[2] = (rotaMatrix.m[2][0] + rotaMatrix.m[0][2]) * mult;
		result[3] = (rotaMatrix.m[1][2] - rotaMatrix.m[2][1]) * mult;
		break;

	case 1:
		result[0] = (rotaMatrix.m[0][1] + rotaMatrix.m[1][0]) * mult;
		result[2] = (rotaMatrix.m[1][2] + rotaMatrix.m[2][1]) * mult;
		result[3] = (rotaMatrix.m[2][0] - rotaMatrix.m[0][2]) * mult;
		break;

	case 2:
		result[0] = (rotaMatrix.m[2][0] + rotaMatrix.m[0][2]) * mult;
		result[1] = (rotaMatrix.m[1][2] + rotaMatrix.m[2][1]) * mult;
		result[3] = (rotaMatrix.m[0][1] - rotaMatrix.m[1][0]) * mult;
		break;

	case 3:
		result[0] = (rotaMatrix.m[1][2] - rotaMatrix.m[2][1]) * mult;
		result[1] = (rotaMatrix.m[2][0] - rotaMatrix.m[0][2]) * mult;
		result[2] = (rotaMatrix.m[0][1] - rotaMatrix.m[1][0]) * mult;
		break;

	default:
		break;
	}

	return result;
}

Matrix4x4 Matrix4x4::Inverse(const Quaternion& quat)
{
	return Matrix4x4();
}

Matrix4x4 Matrix4x4::ExtractTranslation()
{
	Matrix4x4 mat = Translation({ this->m[3][0],this->m[3][1],this->m[3][2] });
	return mat;
}

Matrix4x4 Matrix4x4::ExtractScale()
{
	Matrix4x4 mat = Scale(
		{
			Vector3{ this->m[0][0],this->m[0][1],this->m[0][2] }.Length(),
			Vector3{ this->m[1][0],this->m[1][1],this->m[1][2] }.Length(),
			Vector3{ this->m[2][0],this->m[2][1],this->m[2][2] }.Length()
		});
	return mat;
}

Matrix4x4 Matrix4x4::ExtractRotation()
{
	return Matrix4x4();
}

Matrix4x4& operator*=(Matrix4x4& lhs, const Matrix4x4& rhs)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.m[i][j] = 0.0f;
			for (int k = 0; k < 4; k++)
			{
				result.m[i][j] += lhs.m[i][k] * rhs.m[k][j];
			}
		}
	}
	lhs = result;
	return result;
}

Matrix4x4& operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
	Matrix4x4 result = lhs;
	return result *= rhs;
}
