#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(DirectXCommon* dxCommon)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	this->dxCommon = dxCommon;
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Init()
{
	//�ǉ������I�u�W�F�N�g�̐��ɉ����Ď����I�ɑS�ď�����
	for (auto& gameObj : objects)
	{
		gameObj->Init();
	}
}

void GameObjectManager::Update()
{
	//�I�u�W�F�N�g�̃T�C�Y(��)���Q��
	for (int i = 0; i < objects.size(); ++i)
	{
		//deleteFlag��TRUE�ł����Update�O�ɍ폜
		if (objects[i]->GetDeleteFlag()) {
    			objects.erase(objects.begin() + i);
		}
	}
	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->Update();
	}
}

void GameObjectManager::Draw()
{
	//�I�u�W�F�N�g�̃T�C�Y(��)���Q�Ƃ������I�ɕ`��
	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->Draw();
	}
}
