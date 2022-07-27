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
			scenes.push(new Title(dxCommon, audio));
			break;
		case SceneManager::gameScene:
			scenes.push(new GameScene(dxCommon, audio));
			break;
		case SceneManager::endScene:
			scenes.push(new EndGame(dxCommon, audio));
			break;
		case SceneManager::MAX:
			break;
		default:
			break;
	}
	scenes.top()->Init();
}

SceneManager::SceneManager(DirectXCommon* dxCommon, Audio* audio)
{
#pragma region nullptr�`�F�b�N/���
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;
#pragma endregion
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::Init()
{
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
