#include "WallSpaner.h"
#include "Wall.h"

WallSpaner::WallSpaner(DirectXCommon* dxCommon, std::shared_ptr<CollisionManager> collisionManager, PlayerBase* player):
	GameObjectBase(dxCommon)
{
	this->collisionManager = collisionManager;
	playerData = player;
	// ファイル読み込み
	LoadData("Resources/Csv/WallSpownData.csv");
}

void WallSpaner::Update()
{
	if (spawnDatas.size() == 0)
	{
		return;
	}
	// プレイヤーがスポーン位置から一定の距離内にいれば先頭のデータをスポーンさせる
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
	//ファイルクローズ
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
