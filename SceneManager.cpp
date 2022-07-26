#include "SceneManager.h"
std::stack<AbstructScene*> SceneManager::scenes;

DirectXCommon* SceneManager::dxCommon;
Audio* SceneManager::audio;

void SceneManager::ChangeScene(SceneNo sceneNo, bool sceneStackClear)
{

	if (sceneStackClear) {
		//�V�[������ɂȂ�܂Ń|�b�v
		while (scenes.size() != 0) {
			scenes.pop();
		}
	}
	
	//�V�[���؂�ւ�
	switch (sceneNo)
	{
		case SceneManager::titleScene:
			scenes.push(new Title());
			break;
		case SceneManager::gameScene:
			scenes.push(new GameScene());
			break;
		case SceneManager::endScene:
			scenes.push(new EndGame());
			break;
		case SceneManager::MAX:
			break;
		default:
			break;
	}
	scenes.top()->Init(dxCommon, audio);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::Init(DirectXCommon* dxCommon, Audio* audio)
{
#pragma region nullptr�`�F�b�N/���
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
#pragma endregion

	ChangeScene(gameScene);

}

void SceneManager::Update()
{

#pragma region �V�[���A�b�v�f�[�g
	//�X�^�b�N�̈�ԏ���A�b�v�f�[�g
	scenes.top()->Update();
#pragma endregion

}

void SceneManager::Draw()
{
	scenes.top()->Draw();
}
