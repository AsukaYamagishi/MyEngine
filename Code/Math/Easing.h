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
/// イージング
/// </summary>
/// <param name="Type">タイプ(In,Out)</param>
/// <param name="Ease">挙動の種類</param>
/// <param name="t">時間</param>
/// <param name="start">始点</param>
/// <param name="end">終点</param>
/// <returns>移動結果</returns>
double Ease(type InOutType, ease EaseType, double t, double start, double end);
/// <summary>
/// イージング
/// </summary>
/// <param name="Type">タイプ(In,Out)</param>
/// <param name="Ease">挙動の種類</param>
/// <param name="t">時間</param>
/// <param name="start">始点</param>
/// <param name="end">終点</param>
/// <returns>移動結果</returns>
Vector3 Ease(type InOutType, ease EaseType, double t, Vector3 start, Vector3 end);

