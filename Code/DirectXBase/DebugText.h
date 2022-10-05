#pragma once
#include<Windows.h>
#include<string>
#include"../2d/Sprite.h"

class DebugText
{
#pragma region 定数
public:
	//定数の宣言
	//デバッグテキスト用のテクスチャ番号を指定
	static const int maxCharCount = 256; //1フレームでの最大表示文字数
	static const int fontWidth = 9; //1文字分の横幅
	static const int fontHeight = 18; //1文字分の縦幅
	static const int fontLineCount = 14; //画像内1行分の文字数
#pragma endregion

#pragma region 関数
public: //メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="texnumber">テキスト画像収納番号</param>
	void Init(UINT texnumber);

	/// <summary>
	/// 文字列の追加
	/// </summary>
	/// <param name="text">表示文字</param>
	/// <param name="x">x位置</param>
	/// <param name="y">y位置</param>
	/// <param name="scale">大きさ</param>
	void PrintDebugText(const std::string& text, float x, float y, float scale = 1.0f);
	
	/// <summary>
	/// 文字列の表示
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void DrawAll(ID3D12GraphicsCommandList* cmdList);
#pragma endregion

#pragma region 変数
private: //メンバ変数
	//スプライトの配列
	Sprite* textSprites[maxCharCount];
	//配列の添え字
	int textIndex = 0;
#pragma endregion
};

