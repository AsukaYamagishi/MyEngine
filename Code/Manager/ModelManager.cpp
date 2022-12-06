#include "ModelManager.h"

map<std::string, ObjLoader* > ModelManager::model;

ModelManager* ModelManager::GetIns()
{
	static ModelManager instans;
	return &instans;
}

void ModelManager::Init()
{
	LoadModel("Player");
	LoadModel("bullet");
	LoadModel("enemy");
	LoadModel("Wall");
	LoadModel("skydome");
	LoadModel("EnemyBullet");
	
	//LoadModel(TestDunut, "donut");
}

void ModelManager::LoadModel(std::string fileName)
{
	model[fileName] = new ObjLoader();
	model[fileName]->InitializeDiscriptorHeap();
	model[fileName]->CreateFromObj(fileName);

}
