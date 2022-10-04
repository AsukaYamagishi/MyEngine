#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(DirectXCommon* dxCommon,std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player):
	GameObject(dxCommon)
{
	this->collisionManager = collisionManager;
	playerData = player;
	// ファイル読み込み
	spawnDatas = LoadData("Resources/EnemySpownData.csv");
}

void EnemySpawner::Update()
{
	if (spawnDatas.size() == 0)
	{
		return;
	}
	// プレイヤーがスポーン位置から一定の距離内にいれば先頭のデータをスポーンさせる
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
	// 行
	int i = 0;

	//ファイルが終わるまで読み込み
	while (!fileStream.eof())
	{
		i++;
		string bufferString;
		fileStream >> bufferString;
		//1行目は列名でデータではないためスキップ
		if (i <= 1) continue;

		//データを項目ごとに抽出
		istringstream stringStream(bufferString);
		vector<string> datas;
		string stemp;
		//カンマ区切りでデータを切り分け
		while (getline(stringStream, stemp, ','))
		{
			datas.push_back(stemp);
		}
		//切り分けたデータを構造体に格納
		SpawnData data;
		data.spawnPos =
		{
			strtof(datas[0].c_str(),NULL),
			strtof(datas[1].c_str(),NULL),
			strtof(datas[2].c_str(),NULL)
		};
		dataTable.push(data);
	}
	//ファイルクローズ
	fileStream.close();

	return dataTable;
}
