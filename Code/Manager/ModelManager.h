#pragma once
#include <map>
#include <string>
#include "../3d/Obj/ObjLoader.h"

class ModelManager final
{
private:
	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(const ModelManager& r) = default;
	ModelManager& operator= (const ModelManager& r) = default;

public:
	////モデルに付けるタグ名
	//enum ModelName {
	//	PLAYER,
	//	BULLET,
	//	ENEMY,
	//	EBULLET,
	//	WALL,
	//	SKYDOME,

	//	MAX //最大数管理
	//};

public:
	static ModelManager* GetIns();		//取得用

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// モデル読み込み
	/// </summary>
	/// <param name="modelName">モデルに付けたいタグ名</param>
	/// <param name="fileName">ファイル名</param>
	void LoadModel(std::string fileName);

	/// <summary>
	/// モデル情報の取得
	/// </summary>
	/// <param name="modelName">モデルのファイル名</param>
	/// <returns>モデル情報</returns>
	ObjLoader* GetModel(const std::string& modelName)
	{
		if (model.find(modelName) == model.end())
		{
			//モデルが未ロードなら読み込み
			LoadModel(modelName);
		}
		return model[modelName]; 
	}

private:
	static map<std::string, ObjLoader* > model;	//モデル格納マップ
};

