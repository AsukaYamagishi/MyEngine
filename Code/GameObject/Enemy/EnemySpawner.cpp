#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(DirectXCommon* dxCommon,std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player):
	GameObjectBase(dxCommon)
{
	this->collisionManager = collisionManager;
	playerData = player;
	// ファイル読み込み
	LoadData("Resources/Csv/EnemySpownBlocData.csv");
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
		GameObjectBase::Create<Enemy>(
			dxCommon, gameObjectManager, collisionManager,
			spawnDatas.front().spawnPos, playerData);
		spawnDatas.pop();
	}
}

void EnemySpawner::LoadData(const char* filepath)
{

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

		int type = strtof(datas[3].c_str(), NULL);
		Vector3 startPos
		{
			strtof(datas[0].c_str(),NULL),
			strtof(datas[1].c_str(),NULL),
			strtof(datas[2].c_str(),NULL)
		};
		//切り分けたデータを構造体に格納
		switch (type)
		{
		case CROSS:
			CrossSpawn(startPos);
			break;
		case BOX:
			BoxSpawn(startPos);
			break;
		default:
			break;
		}
		
	}
	//ファイルクローズ
	fileStream.close();

}

void EnemySpawner::CrossSpawn(Vector3 startPos)
{
	// 真ん中
	spawnDatas.push(SpawnData{ startPos });
	// 右上
	spawnDatas.push(SpawnData{ startPos + Vector3{10,10,0} });
	// 左上
	spawnDatas.push(SpawnData{ startPos + Vector3{-10,10,0} });
	// 右下
	spawnDatas.push(SpawnData{ startPos + Vector3{10,-10,0} });
	// 左下
	spawnDatas.push(SpawnData{ startPos + Vector3{-10,-10,0} });
}

void EnemySpawner::BoxSpawn(Vector3 startPos)
{
	// 右上
	spawnDatas.push(SpawnData{ startPos + Vector3{5,5,0} });
	// 左上
	spawnDatas.push(SpawnData{ startPos + Vector3{-5,5,0} });
	// 右下
	spawnDatas.push(SpawnData{ startPos + Vector3{5,-5,0} });
	// 左下
	spawnDatas.push(SpawnData{ startPos + Vector3{-5,-5,0} });

}
