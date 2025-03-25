#include "framework.h"
//GameSystem�N���X���g����悤�ɂ���
#include "GameSystem.h"
//Direct3D�N���X���g����悤�ɂ���
#include "Direct3D.h"
#include "DirectX.h"

void GameSystem::Initialize()
{

}


void GameSystem::Execute()
{
	//��ʂ�F�œh��Ԃ�
	float color[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), color);


	//�O�p�`�̕`��
	{
		//1���_�̌`���i����͍��W�����j
		struct VertexType
		{
			DirectX::XMFLOAT3 Pos;
		};
		//�O�p�`�̒��_�f�[�^
		VertexType v[4] =
		{
			{ { -0.5f,-0.5f,0 } },
			{ { -0.5f,0.5f,0 } },
			{ {0.5f, -0.5f, 0} },
			{{0.5f, 0.5f, 0}},
		};

		// ���_�o�b�t�@�쐬
		// �E��L�ō�����R�̒��_�͂��̂܂܂ł͕`��Ɏg�p�ł��Ȃ��񂷁c
		// �E�r�f�I���������Ɂu���_�o�b�t�@�v�Ƃ����`�ō��K�v������܂��I
		// �E����͌����������āA���̏�ō���āA�g���āA�����̂Ă܂��B
		//-----------------------------
		// �쐬����o�b�t�@�̎d�l�����߂�
		// �E����͒��_�o�b�t�@�ɂ��邼�I���Ċ����̐ݒ�
		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // ����͒��_�o�b�t�@�����I
		vbDesc.ByteWidth = sizeof(v); // ���o�b�t�@�̃T�C�Y
		vbDesc.MiscFlags = 0;
		vbDesc.Usage = D3D11_USAGE_DEFAULT; // �쐬����o�b�t�@�̎g�p�@
		vbDesc.CPUAccessFlags = 0; // CPU����A�N�Z�X����K�v�����邩�ǂ���

		ComPtr<ID3D11Buffer> vb;
		D3D11_SUBRESOURCE_DATA initData = { &v[0], sizeof(v), 0 };
		//���_�o�b�t�@�쐬
		D3D.m_device->CreateBuffer(&vbDesc, &initData, &vb);

		// ���_�o�b�t�@��`��Ŏg����悤�ɃZ�b�g
		UINT stride = sizeof(VertexType); // 1���_�̃T�C�Y
		UINT offset = 0; // �I�t�Z�b�g
		D3D.m_deviceContext->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);

		D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//�V�F�[�_�[���Z�b�g
		D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), nullptr, 0);
		D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), nullptr, 0);
		D3D.m_deviceContext->IASetInputLayout(D3D.m_spriteInputLayout.Get());

		//����Ȋ����ŁA�Ђ�����f�o�C�X�R���e�L�X�g�ɏ���n��

		D3D.m_deviceContext->Draw(4, 0);
	}

	D3D.m_swapChain->Present(1, 0);
}