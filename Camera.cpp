#include "Camera.h"
#include "WindowsAPI.h"
#include "yMath.h"

Camera* Camera::NowMatView = nullptr;

Camera::Camera(Vector3 eye, Vector3 target, Vector3 up)
{
	this->eye = eye;
	this->target = target;
	this->up = up;
	//ビュー行列の計算
	UpdateViewMatrix();
	//射影行列の計算
	UpdateProjectionMatrix();
	//ビュープロジェクション合成
	matViewProjection = matView * matProjection;
}

void Camera::Update()
{
	//ビュー行列更新
	UpdateViewMatrix();
	//ビュープロジェクション更新
	UpdateProjectionMatrix();

	//ビュープロジェクション合成
	matViewProjection = matView * matProjection;

}

void Camera::UpdateViewMatrix()
{
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));
}

void Camera::UpdateProjectionMatrix()
{
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WindowsAPI::win_width / WindowsAPI::win_height,
		0.1f, 50000.0f
	);
}


void Camera::Init(const XMFLOAT3 eye)
{
	NowMatView = new Camera(Vector3{ eye });
	NowMatView->matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&Vector3{ 0,0,0 }),
		XMLoadFloat3(&Vector3{ 0,1,0 })
	);
}

void Camera::SetCam(Camera* cam)
{
	NowMatView = cam;
}
