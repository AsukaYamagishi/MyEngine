#pragma once
#include "Vector3.h"

enum type
{
	In,
	Out,
	InOut
};

enum ease
{
	Quad,
	Cubic,
	Quart,
	Quint,
	Sine,
	Exp,
	Circ,
	Back,
	SoftBack,
	Elastic,
	Bounce,
	Linear
};

namespace EasingFunction
{
	double InQuad(double t);
	double InCubic(double t);
	double InQuart(double t);
	double InQuint(double t);
	double InSine(double t);
	double InExpo(double t);
	double InCirc(double t);
	double InBack(double t);
	double InSoftBack(double t);
	double InElastic(double t);
	double InBounce(double t);
	double InLinear(double t);
}

/// <summary>
/// �C�[�W���O
/// </summary>
/// <param name="Type">�^�C�v(In,Out)</param>
/// <param name="Ease">�����̎��</param>
/// <param name="t">����</param>
/// <param name="start">�n�_</param>
/// <param name="end">�I�_</param>
/// <returns>�ړ�����</returns>
double Ease(type InOutType, ease EaseType, double t, double start, double end);
/// <summary>
/// �C�[�W���O
/// </summary>
/// <param name="Type">�^�C�v(In,Out)</param>
/// <param name="Ease">�����̎��</param>
/// <param name="t">����</param>
/// <param name="start">�n�_</param>
/// <param name="end">�I�_</param>
/// <returns>�ړ�����</returns>
Vector3 Ease(type InOutType, ease EaseType, double t, Vector3 start, Vector3 end);

