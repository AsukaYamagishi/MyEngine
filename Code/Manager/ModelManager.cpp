#include "ModelManager.h"

map<ModelManager::ModelName, ObjLoader* > ModelManager::model;

ModelManager* ModelManager::GetIns()
{
	static ModelManager instans;
	return &instans;
}

void ModelManager::Init()
{
	LoadModel(PLAYER, "Player");
	LoadModel(BULLET, "bullet");
	LoadModel(ENEMY, "enemy");
	LoadModel(WALL, "Wall");
	LoadModel(SKYDOME, "skydome");
	LoadModel(EBULLET, "EnemyBullet");
	
	//LoadModel(TestDunut, "donut");
}

void ModelManager::LoadModel(const ModelName modelName, std::string fileName)
{
	model[modelName] = new ObjLoader();
	model[modelName]->InitializeDiscriptorHeap();
	model[modelName]->CreateFromObj(fileName);

}
