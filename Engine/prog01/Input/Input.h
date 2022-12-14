#pragma once

#include <Windows.h>
#include <wrl.h>
#include <DirectXMath.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <xinput.h>
#include "DebugText.h"

#pragma comment (lib, "xinput.lib")

enum  PadKey
{
	BUTTON_A, // Aボタン
	BUTTON_B, // Bボタン
	BUTTON_X, // Xボタン
	BUTTON_Y, // Yボタン
	BUTTON_LEFT_SHOULDER, // LBボタン
	BUTTON_RIGHT_SHOULDER, // RBボタン
	BUTTON_BACK, // BACKボタン
	BUTTON_START, // STARTボタン
	BUTTON_LEFT_THUMB, // 左スティック押し込み
	BUTTON_RIGHT_THUMB, // 右スティック押し込み
	BUTTON_DPAD_UP, // デジタル方向ボタン上
	BUTTON_DPAD_DOWN, // デジタル方向ボタン下
	BUTTON_DPAD_LEFT, // デジタル方向ボタン左
	BUTTON_DPAD_RIGHT // デジタル方向ボタン右
};

class Input final
{
private:
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	struct MouseMove
	{
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};

public: //メンバ関数
	//初期化
	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	//更新
	void Update();
	// キーの押下をチェック
	bool PushKey(BYTE keyNumber);
	// キーのトリガーをチェック
	bool TriggerKey(BYTE keyNumber);

	static BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef);

	//スティックの傾き
	XMFLOAT2& PadStickGradient();
	XMFLOAT2& PadRightStickGradient();
	//スティックの角度
	double PadStickAngle();
	double PadRightStickAngle();
	//振動のフラグ設定
	void SetVibration(bool _vibration) { vibrationFlag = _vibration; }
	void SetVibrationPower(int _vibrationPower) { vibrationPower = _vibrationPower; }
	// キーの左ボタントリガーをチェック
	bool TriggerPadLeft();
	// キーの右ボタントリガーをチェック
	bool TriggerPadRight();
	//ゲームパッドのキーの押下をチェック
	bool PushPadKey(PadKey keyNumber);
	// キーのトリガーをチェック
	bool TriggerPadKey(PadKey keyNumber);
	//
	bool TriggerPadStickRight();
	bool TriggerPadStickLeft();

	// キーの左ボタン押下をチェック
	bool PushMouseLeft();
	// キーの中ボタン押下をチェック
	bool PushMouseMiddle();
	// キーの右ボタン押下をチェック
	bool PushMouseRight();
	// キーの左ボタントリガーをチェック
	bool TriggerMouseLeft();
	// キーの中ボタントリガーをチェック
	bool TriggerMouseMiddle();
	// キーの右ボタントリガーをチェック
	bool TriggerMouseRight();
	// マウス移動量を取得
	MouseMove GetMouseMove();
	//　マウスの座標を取得
	XMFLOAT2& GetMousePoint()
	{
		POINT mousePos;
		GetCursorPos(&mousePos);

		WINDOWINFO windowInfo;
		windowInfo.cbSize = sizeof(WINDOWINFO);
		HWND hDesktop = GetDesktopWindow();
		GetWindowInfo(hDesktop, &windowInfo);

		// スクリーン座標をクライアント座標に変換する
		ScreenToClient(hDesktop, &mousePos);

		XMFLOAT2 p;
		p.x = mousePos.x - (windowInfo.rcWindow.right / 2);
		p.y = mousePos.y - (windowInfo.rcWindow.bottom / 2);

		/*DebugText::GetInstance()->VariablePrint(0, 0, "windowInfo.rcWindow.right", windowInfo.rcWindow.right, 1.0f);
		DebugText::GetInstance()->VariablePrint(0, 16, "windowInfo.rcWindow.bottom", windowInfo.rcWindow.bottom, 1.0f);*/

		return p;
	};

	XMFLOAT2& GetScreen()
	{
		WINDOWINFO windowInfo;
		windowInfo.cbSize = sizeof(WINDOWINFO);
		HWND hDesktop = GetDesktopWindow();
		GetWindowInfo(hDesktop, &windowInfo);

		/*DebugText::GetInstance()->VariablePrint(0, 0, "windowInfo.rcWindow.right", windowInfo.rcWindow.right, 1.0f);
		DebugText::GetInstance()->VariablePrint(0, 16, "windowInfo.rcWindow.bottom", windowInfo.rcWindow.bottom, 1.0f);*/

		return XMFLOAT2(windowInfo.rcWindow.right, windowInfo.rcWindow.bottom);
	};

private:
	Input();
	~Input();

	void Vibration();

public:
	Input(const Input& input) = delete;
	Input& operator=(const Input& input) = delete;

	static Input* GetInstance();

private: //メンバ変数
	//キーボード
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};

	//dゲームパッド
	ComPtr<IDirectInput8> dinputPad;
	ComPtr<IDirectInputDevice8> devGamePad;
	LPVOID parameter;
	// 軸モードを絶対値モードとして設定
	DIPROPDWORD diprop;
	// 値の範囲設定
	DIPROPRANGE diprg;
	// 無反応範囲
	float angle = 200;
	// 入力情報
	DIJOYSTATE padData;
	DIJOYSTATE padDataPre;
	//接続確認
	bool padFlag = true;
	//xゲームパッド
	XINPUT_STATE state;
	XINPUT_STATE statePre;
	bool vibrationFlag = false;
	XINPUT_VIBRATION vibration;
	int vibrationPower = 65535;

	//マウス
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 mouseStatePre = {};
};