#include "SceneManager.h"
std::stack<AbstructScene*> SceneManager::scenes;

DirectXCommon* SceneManager::dxCommon;
KeyboardInput* SceneManager::input;
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
	scenes.top()->Init(dxCommon, input, audio);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	
}

void SceneManager::Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio)
{
#pragma region nullptr�`�F�b�N/���
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
#pragma endregion

	//�e�V�[������/�ŏ��̃V�[��������
	//title = new Title();
	//title->Init(dxCommon, input, audio);
	//end = new EndGame();
	////end->Init(dxCommon, input, audio);
	//game = new GameScene();
	//game->Init(dxCommon, input, audio);

	//�|�X�g�G�t�F�N�g�p�e�N�X�`���ǂݍ���
	//Sprite::LoadTexture(100, L"Resources/white1x1.png");

	//�Q�[���J�n�V�[���̐ݒ�
	//sceneNo = gameScene;

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
