#pragma once
#include <iostream>
#include <limits> //数値の最大値や最小値などを定義

namespace Mathf // f = float
{
	//イプシロン定数（C++で表現できる最小値）
	//constexpr : 定数みたいなもの
	static constexpr float epsilon{ FLT_EPSILON };
	// 円周率
	static const float pi = 3.14159265358979f;
	// 正の無限
	static const float infinity = std::numeric_limits<float>::infinity();
	// 負の無限
	static const float negative_infinity = -std::numeric_limits<float>::infinity();
	// 度からラジアンへ変換する定数
	static const float deg_to_rad = pi / 180.0f;
	// ラジアンから度へ変換する定数
	static const float rad_to_deg = 180.0f / pi;

	/// <summary>
	/// 2つの値の差が許容範囲内にあるかチェック(誤差が小さければ〇)
	/// </summary>
	/// <param name="lhs">1つ目の値</param>
	/// <param name="rhs">2つ目の値</param>
	/// <param name="tolerance">許容範囲</param>
	/// <returns>近似してるか(誤差が少ないか)</returns>
	inline static bool Approximately(const float& lhs, const float& rhs, const float& tolerance = epsilon)
	{
		//2つの値の差(違い)を求める
		float difference = fabsf(lhs - rhs);

		//差と許容範囲を比べて結果を返す
		if (difference < tolerance)
		{
			return true;
		}
		return false;
	}

	/// <summary>
	/// 値を指定した範囲内に収める
	/// </summary>
	/// <param name="value">調整したい値</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>計算結果(float)</returns>
	inline static float Clamp(const float& value, const float& min, const float& max)
	{
		//より大きかったらmaxを返す
		if (value > max)
		{
			return max;
		}
		//より小さかったらminを返す
		else if (value < min)
		{
			return min;
		}
		//どちらにも当てはまらなかったらそのまま返す
		return value;
	}

	/// <summary>
	/// 目標値まで指定した移動量で移動する
	/// </summary>
	/// <param name="current">現在値</param>
	/// <param name="target">目標値</param>
	/// <param name="max_delta">移動量</param>
	/// <returns>移動結果(float)</returns>
	inline static float MoveTowards(const float& current, const float& target, const float& max_delta)
	{
		//移動予定値が目標値まで小さければ移動後の値を返す
		if (current + max_delta < target)
		{
			return current + max_delta;
		}
		//大きくなった場合は目標値を返す
		return target;
	}

	/// <summary>
	/// 2つの値の中から最大値を返す
	/// </summary>
	/// <param name="lhs">1つ目</param>
	/// <param name="rhs">2つ目</param>
	/// <returns>最大値(float)</returns>
	inline static float Max(const float& lhs, const float& rhs)
	{
		if (lhs > rhs)
		{
			return lhs;
		}
		return rhs;
	}

	/// <summary>
	/// 複数の値の中から最大値を返す
	/// </summary>
	/// <param name="a">1つ目</param>
	/// <param name="b">2つ目</param>
	/// <param name="...args">3つ目以降(何個でも)</param>
	/// <returns>最大値(float)</returns>
	template<class ...Args>
	inline static float Max(float a, float b, Args ...args)
	{
		//最初の2つを比べてもとにする値を決める
		float max = Max(a, b);
		//さっき決めた値と3つ目以降の値を1つずつ全て比べる
		for (float i : std::initializer_list<float>{ args... })
		{
			max = Max(max, i);
		}
		//最終的に一番大きかった値を返す
		return max;
	}

	/// <summary>
	/// 2つの値の中から最小値を返す
	/// </summary>
	/// <param name="lhs">1つ目</param>
	/// <param name="rhs">2つ目</param>
	/// <returns>最小値(float)</returns>
	inline static float Min(const float& lhs, const float& rhs)
	{
		if (lhs < rhs)
		{
			return lhs;
		}
		return rhs;
	}

	/// <summary>
	/// 複数の値の中から最小値を返す
	/// </summary>
	/// <param name="a">1つ目</param>
	/// <param name="b">2つ目</param>
	/// <param name="...args">3つ目以降(何個でも)</param>
	/// <returns>最小値(float)</returns>
	template<class ...Args>
	inline static float Min(float a, float b, Args ...args)
	{
		//最初の2つを比べてもとにする値を決める
		float min = Min(a, b);
		//さっき決めた値と3つ目以降の値を1つずつ全て比べる
		for (float i : std::initializer_list<float>{ args... })
		{
			min = Min(min, i);
		}
		//最終的に一番小さかった値を返す
		return min;
	}

};
