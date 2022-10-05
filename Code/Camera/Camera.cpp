#include "Camera.h"
#include <yMath.h>
#include "../DirectXBase/WindowsAPI.h"

Camera* Camera::NowMatView = nullptr;

Camera::Camera(Vector3 eye, Vector3 target, Vector3 up)
{
	this->eye = eye;
	this->target = target;
	this->up = up;
	//�r���[�s��̌v�Z
	UpdateViewMatrix();
	//�ˉe�s��̌v�Z
	UpdateProjectionMatrix();
	//�r���[�v���W�F�N�V��������
	matViewProjection = matView * matProjection;
}

void Camera::Update()
{
	//�r���[�s��X�V
	UpdateViewMatrix();
	//�r���[�v���W�F�N�V�����X�V
	UpdateProjectionMatrix();

	//�r���[�v���W�F�N�V��������
	matViewProjection = matView * matProjection;

}

void Camera::UpdateViewMatrix()
{
	//���݂̃J�������ŏ㏑��
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


void Camera::Init(const Vector3 eye, const Vector3 target, const Vector3 up)
{
	//�����ݒ肵�Ȃ��ꍇ�����I��(0,100,100),(0,0,0),(0,1,0)��
	NowMatView = new Camera(eye, target, up);
	NowMatView->matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up)
	);
}

void Camera::SetCam(Camera* cam)
{
	NowMatView = cam;
}
