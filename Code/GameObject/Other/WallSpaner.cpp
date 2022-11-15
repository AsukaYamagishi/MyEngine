#include "WallSpaner.h"
#include "Wall.h"

WallSpaner::WallSpaner(DirectXCommon* dxCommon, std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player):
	GameObjectBase(dxCommon)
{
	this->collisionManager = collisionManager;
	playerData = player;
	// �t�@�C���ǂݍ���
	LoadData("Resources/Csv/WallSpownData.csv");
}

void WallSpaner::Update()
{
	if (spawnDatas.size() == 0)
	{
		return;
	}
	// �v���C���[���X�|�[���ʒu������̋������ɂ���ΐ擪�̃f�[�^���X�|�[��������
	if (playerData->GetPos().z >= spawnDatas.front().spawnPos.z - 50.0f)
	{
		
		GameObjectBase::Create<Wall>(
			spawnDatas.front().spawnPos,
			dxCommon,
			collisionManager,
			playerData,spawnDatas.front().size);

		spawnDatas.pop();
	}
}

void WallSpaner::LoadData(const char* filepath)
{

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

		int type = strtof(datas[3].c_str(), NULL);
		Vector3 startPos
		{
			strtof(datas[0].c_str(),NULL),
			strtof(datas[1].c_str(),NULL),
			strtof(datas[2].c_str(),NULL)
		};
		//�؂蕪�����f�[�^���\���̂Ɋi�[
		switch (type)
		{
		case SIDE:
			SideSpawn(startPos);
			break;
		case VERTICAL:
			VerticalSpawn(startPos);
			break;
		case AROUND:
			AroundSpawn(startPos);
			break;
		case CENTER:
			CenterSpawn(startPos);
			break;

		default:
			break;
		}
	}
	//�t�@�C���N���[�Y
	fileStream.close();

}

void WallSpaner::SideSpawn(Vector3 startPos)
{
	spawnDatas.push(SpawnData{ startPos + Vector3{20,0,0}, Vector3{4,10,1} });
	spawnDatas.push(SpawnData{ startPos + Vector3{-20,0,0}, Vector3{4,10,1} });
}

void WallSpaner::VerticalSpawn(Vector3 startPos)
{
	spawnDatas.push(SpawnData{ startPos + Vector3{0,20,0}, Vector3{20,4,1} });
	spawnDatas.push(SpawnData{ startPos + Vector3{0,-20,0}, Vector3{20,4,1} });
}

void WallSpaner::AroundSpawn(Vector3 startPos)
{
	spawnDatas.push(SpawnData{ startPos + Vector3{20,0,0}, Vector3{4,10,1} });
	spawnDatas.push(SpawnData{ startPos + Vector3{-20,0,0}, Vector3{4,10,1} });
	spawnDatas.push(SpawnData{ startPos + Vector3{0,13,0}, Vector3{20,2,1} });
	spawnDatas.push(SpawnData{ startPos + Vector3{0,-13,0}, Vector3{20,2,1} });

}

void WallSpaner::CenterSpawn(Vector3 startPos)
{
	spawnDatas.push(SpawnData{ startPos + Vector3{0,0,0}, Vector3{10,10,1} });
}
