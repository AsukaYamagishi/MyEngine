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
	//モデルに付けるタグ名
	enum ModelName {
		PLAYER,
		BULLET,
		ENEMY,
		WALL,

		MAX //最大数管理
	};

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
	void LoadModel(const ModelName modelName, std::string fileName);

	/// <summary>
	/// モデル情報の取得
	/// </summary>
	/// <param name="modelName">モデルのタグ名</param>
	/// <returns>タグに対応したモデル情報</returns>
	ObjLoader *GetModel(ModelName modelName) { return model[modelName]; }

private:
	static map<ModelName, ObjLoader* > model;	//モデル格納マップ
};

