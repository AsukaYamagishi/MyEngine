#include "EnemySponer.h"

EnemySponer::EnemySponer(DirectXCommon* dxCommon,std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player):
	GameObject(dxCommon)
{
	this->collisionManager = collisionManager;
	playerData = player;
	// �t�@�C���ǂݍ���
	spownDatas = LoadData("Resources/EnemySpownData.csv");
}

void EnemySponer::Update()
{
	if (spownDatas.size() == 0)
	{
		return;
	}
	// �v���C���[���X�|�[���ʒu������̋������ɂ���ΐ擪�̃f�[�^���X�|�[��������
	if (playerData->GetPos().z >= spownDatas.front().spownPos.z - 50.0f)
	{
		GameObject::Create<Enemy>(
			dxCommon, gameObjectManager, collisionManager,
			spownDatas.front().spownPos, playerData);
		spownDatas.pop();
	}
}

std::queue<EnemySponer::SpownData> EnemySponer::LoadData(const char* filepath)
{
	std::queue<SpownData> dataTable;

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
		SpownData data;
		data.spownPos =
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
