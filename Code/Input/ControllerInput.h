#pragma once
#include <vector>
#include <dinput.h>
#include "../DirectXBase/WindowsAPI.h"
#define DIRECTINPUT_VERSION 0x0800 //DirectInputバージョン指定

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")


//ゲームパッド・ボタン入力
#define XBOX_INPUT_A      (0)  //Aボタン
#define XBOX_INPUT_B      (1)  //Bボタン
#define XBOX_INPUT_X      (2)  //Xボタン
#define XBOX_INPUT_Y      (3)  //Yボタン
#define XBOX_INPUT_LB     (4)  //LBボタン
#define XBOX_INPUT_RB     (5)  //RBボタン
#define XBOX_INPUT_SELECT (6)  //SELECTボタン
#define XBOX_INPUT_START  (7)  //STARTボタン
#define XBOX_INPUT_LSTICK (8)  //左スティック押し込み
#define XBOX_INPUT_RSTICK (9)  //右スティック押し込み
#define XBOX_INPUT_LEFT   (34) //十字キー左
#define XBOX_INPUT_RIGHT  (32) //十字キー右
#define XBOX_INPUT_UP     (35) //十字キー上
#define XBOX_INPUT_DOWN   (33) //十字キー下

//ゲームパッドのスティック入力
#define INPUT_AXIS_LX  (0x01) //左スティックのX軸
#define INPUT_AXIS_LY  (0x02) //左スティックのY軸
#define INPUT_AXIS_LZ  (0x04) //左スティックのZ軸（LT・RT）
#define INPUT_AXIS_RX (0x08) //左スティックのX回転軸（右スティックのX軸）
#define INPUT_AXIS_RY (0x10) //左スティックのY回転軸（右スティックのY軸）
#define INPUT_AXIS_RZ (0x20) //左スティックのZ回転軸


class ControllerInput final
{
	//シングルトンパターン設定
private: //コンストラクタ・デストラクタprivate化
	ControllerInput(){}
	~ControllerInput(){}
public: //コンストラクタ関係の設定
	//コピーコンストラクタの削除
	ControllerInput(const ControllerInput&) = delete;
	//代入演算子の削除
	const ControllerInput& operator=(const ControllerInput&) = delete;
	//インスタンスの取得
	static ControllerInput* GetIns();

private: //エイリアス
	template<class T> using vector = std::vector<T>;

public: //静的メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	static void Init();

	/// <summary>
	/// 毎フレーム更新
	/// </summary>
	static void Update();

	/// <summary>
	/// ゲームパッドの状態取得
	/// </summary>
	/// <param name="padNo">どのボタンか</param>
	/// <returns>ゲームパッドの状態</returns>
	static DIJOYSTATE GetGamepadState(const size_t& padNo = 0);

	//ボタンが押されているか
	static bool IsPadButton(const size_t& button, const size_t& padNo = 0);
	//ボタンが押されている間の時間の取得
	static size_t GetPadButtonPress(const size_t& button, const size_t& padNo = 0);
	//ボタンを離している間の時間の取得
	static size_t GetPadButtonRelease(const size_t& button, const size_t& padNo = 0);
	//ボタンが押されたか（押された瞬間）
	static bool IsPadButtonTrigger(const size_t& button, const size_t& padNo = 0);
	//ボタンから離れたか
	static bool IsPadButtonRelease(const size_t& button, const size_t& padNo = 0);
	//スティックに入力があるか
	static int IsPadStick(const size_t& stickAxis, const float& deadzone, const size_t& padNo = 0);

private:
	/// <summary>
	/// ゲームパッドデバイスの生成
	/// </summary>
	/// <returns>成否</returns>
	static HRESULT CreateGamepadDevice();

	/// <summary>
	/// デバイス列挙コールバック関数
	/// </summary>
	/// <param name="lpddi"></param>
	/// <param name="pvRef"></param>
	/// <returns>成否</returns>
	static BOOL CALLBACK EnumGamepadCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);

	/// <summary>
	/// プロパティ初期設定
	/// </summary>
	/// <param name="padNo">どのボタンか</param>
	/// <returns>成否</returns>
	static HRESULT SetupGamepadProperty(const size_t& padNo = 0);


public: //定数
	static const LONG zoneMax; //スティック入力上限
	static const LONG zoneMin; //スティック入力下限

private: //静的メンバ変数
	static IDirectInput8* dinput;
	static vector<IDirectInputDevice8*> devGamepad; //ゲームパッドデバイス
	static vector<DIJOYSTATE> gamepad; //ゲームパッドの現在の状態
	static vector<DIJOYSTATE> oldgamepad; //1フレーム前のゲームパッドの状態
	static size_t pressCount[64]; //押している時間
	static size_t releaseCount[64]; //離している時間

};

