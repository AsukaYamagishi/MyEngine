#pragma once
#include <map>
#include <string>
#include "Code/3d/Obj/ObjLoader.h"
class ModelManager final
{
private:
	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(const ModelManager &r) = default;
	ModelManager &operator= (const ModelManager &r) = default;

public:
	enum ModelName {
		PLAYER,
		BULLET,
		ENEMY,
		WALL,
	};

public:
	static ModelManager *GetIns();		//�擾�p

	void Initialize();
	void LoadModel(const ModelName modelName, std::string fileName);
	ObjLoader *GetModel(ModelName modelName) { return model[modelName]; }

private:
	static map<ModelName, ObjLoader*> model;	//���f���i�[�}�b�v
};

