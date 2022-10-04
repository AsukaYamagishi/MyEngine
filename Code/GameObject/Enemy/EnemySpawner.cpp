#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(DirectXCommon* dxCommon,std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player):
	GameObject(dxCommon)
{
	this->collisionManager = collisionManager;
	playerData = player;
	// �t�@�C���ǂݍ���
	spawnDatas = LoadData("Resources/EnemySpownData.csv");
}

void EnemySpawner::Update()
{
	if (spawnDatas.size() == 0)
	{
		return;
	}
	// �v���C���[���X�|�[���ʒu������̋������ɂ���ΐ擪�̃f�[�^���X�|�[��������
	if (playerData->GetPos().z >= spawnDatas.front().spawnPos.z - 50.0f)
	{
		GameObject::Create<Enemy>(
			dxCommon, gameObjectManager, collisionManager,
			spawnDatas.front().spawnPos, playerData);
		spawnDatas.pop();
	}
}

std::queue<EnemySpawner::SpawnData> EnemySpawner::LoadData(const char* filepath)
{
	std::queue<SpawnData> dataTable;

	ifstream fileStream(filepath);
	if (!fileStream) 
	{
		assert(0);
	}
	// �s
	int i = 0;

	//�t�@�C�����I���܂œǂݍ���
	while (!fileStream.eof())
	{
		i++;
		string bufferString;
		fileStream >> bufferString;
		//1�s�ڂ͗񖼂Ńf�[�^�ł͂Ȃ����߃X�L�b�v
		if (i <= 1) continue;

		//�f�[�^�����ڂ��Ƃɒ��o
		istringstream stringStream(bufferString);
		vector<string> datas;
		string stemp;
		//�J���}��؂�Ńf�[�^��؂蕪��
		while (getline(stringStream, stemp, ','))
		{
			datas.push_back(stemp);
		}
		//�؂蕪�����f�[�^���\���̂Ɋi�[
		SpawnData data;
		data.spawnPos =
		{
			strtof(datas[0].c_str(),NULL),
			strtof(datas[1].c_str(),NULL),
			strtof(datas[2].c_str(),NULL)
		};
		dataTable.push(data);
	}
	//�t�@�C���N���[�Y
	fileStream.close();

	return dataTable;
}
