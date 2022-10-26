#pragma once
#include <iostream>
#include <limits> //���l�̍ő�l��ŏ��l�Ȃǂ��`

namespace Mathf // f = float
{
	//�C�v�V�����萔�iC++�ŕ\���ł���ŏ��l�j
	//constexpr : �萔�݂����Ȃ���
	static constexpr float epsilon{ FLT_EPSILON };
	// �~����
	static const float pi = 3.14159265358979f;
	// ���̖���
	static const float infinity = std::numeric_limits<float>::infinity();
	// ���̖���
	static const float negative_infinity = -std::numeric_limits<float>::infinity();
	// �x���烉�W�A���֕ϊ�����萔
	static const float deg_to_rad = pi / 180.0f;
	// ���W�A������x�֕ϊ�����萔
	static const float rad_to_deg = 180.0f / pi;

	/// <summary>
	/// 2�̒l�̍������e�͈͓��ɂ��邩�`�F�b�N(�덷����������΁Z)
	/// </summary>
	/// <param name="lhs">1�ڂ̒l</param>
	/// <param name="rhs">2�ڂ̒l</param>
	/// <param name="tolerance">���e�͈�</param>
	/// <returns>�ߎ����Ă邩(�덷�����Ȃ���)</returns>
	inline static bool Approximately(const float& lhs, const float& rhs, const float& tolerance = epsilon)
	{
		//2�̒l�̍�(�Ⴂ)�����߂�
		float difference = fabsf(lhs - rhs);

		//���Ƌ��e�͈͂��ׂČ��ʂ�Ԃ�
		if (difference < tolerance)
		{
			return true;
		}
		return false;
	}

	/// <summary>
	/// �l���w�肵���͈͓��Ɏ��߂�
	/// </summary>
	/// <param name="value">�����������l</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>�v�Z����(float)</returns>
	inline static float Clamp(const float& value, const float& min, const float& max)
	{
		//���傫��������max��Ԃ�
		if (value > max)
		{
			return max;
		}
		//��菬����������min��Ԃ�
		else if (value < min)
		{
			return min;
		}
		//�ǂ���ɂ����Ă͂܂�Ȃ������炻�̂܂ܕԂ�
		return value;
	}

	/// <summary>
	/// �ڕW�l�܂Ŏw�肵���ړ��ʂňړ�����
	/// </summary>
	/// <param name="current">���ݒl</param>
	/// <param name="target">�ڕW�l</param>
	/// <param name="max_delta">�ړ���</param>
	/// <returns>�ړ�����(float)</returns>
	inline static float MoveTowards(const float& current, const float& target, const float& max_delta)
	{
		//�ړ��\��l���ڕW�l�܂ŏ�������Έړ���̒l��Ԃ�
		if (current + max_delta < target)
		{
			return current + max_delta;
		}
		//�傫���Ȃ����ꍇ�͖ڕW�l��Ԃ�
		return target;
	}

	/// <summary>
	/// 2�̒l�̒�����ő�l��Ԃ�
	/// </summary>
	/// <param name="lhs">1��</param>
	/// <param name="rhs">2��</param>
	/// <returns>�ő�l(float)</returns>
	inline static float Max(const float& lhs, const float& rhs)
	{
		if (lhs > rhs)
		{
			return lhs;
		}
		return rhs;
	}

	/// <summary>
	/// �����̒l�̒�����ő�l��Ԃ�
	/// </summary>
	/// <param name="a">1��</param>
	/// <param name="b">2��</param>
	/// <param name="...args">3�ڈȍ~(���ł�)</param>
	/// <returns>�ő�l(float)</returns>
	template<class ...Args>
	inline static float Max(float a, float b, Args ...args)
	{
		//�ŏ���2���ׂĂ��Ƃɂ���l�����߂�
		float max = Max(a, b);
		//���������߂��l��3�ڈȍ~�̒l��1���S�Ĕ�ׂ�
		for (float i : std::initializer_list<float>{ args... })
		{
			max = Max(max, i);
		}
		//�ŏI�I�Ɉ�ԑ傫�������l��Ԃ�
		return max;
	}

	/// <summary>
	/// 2�̒l�̒�����ŏ��l��Ԃ�
	/// </summary>
	/// <param name="lhs">1��</param>
	/// <param name="rhs">2��</param>
	/// <returns>�ŏ��l(float)</returns>
	inline static float Min(const float& lhs, const float& rhs)
	{
		if (lhs < rhs)
		{
			return lhs;
		}
		return rhs;
	}

	/// <summary>
	/// �����̒l�̒�����ŏ��l��Ԃ�
	/// </summary>
	/// <param name="a">1��</param>
	/// <param name="b">2��</param>
	/// <param name="...args">3�ڈȍ~(���ł�)</param>
	/// <returns>�ŏ��l(float)</returns>
	template<class ...Args>
	inline static float Min(float a, float b, Args ...args)
	{
		//�ŏ���2���ׂĂ��Ƃɂ���l�����߂�
		float min = Min(a, b);
		//���������߂��l��3�ڈȍ~�̒l��1���S�Ĕ�ׂ�
		for (float i : std::initializer_list<float>{ args... })
		{
			min = Min(min, i);
		}
		//�ŏI�I�Ɉ�ԏ����������l��Ԃ�
		return min;
	}

};
