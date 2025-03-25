#include "framework.h"
//GameSystemクラスを使えるようにする
#include "GameSystem.h"
//Direct3Dクラスを使えるようにする
#include "Direct3D.h"
#include "DirectX.h"

void GameSystem::Initialize()
{

}


void GameSystem::Execute()
{
	//画面を青色で塗りつぶす
	float color[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), color);


	//三角形の描画
	{
		//1頂点の形式（今回は座標だけ）
		struct VertexType
		{
			DirectX::XMFLOAT3 Pos;
		};
		//三角形の頂点データ
		VertexType v[4] =
		{
			{ { -0.5f,-0.5f,0 } },
			{ { -0.5f,0.5f,0 } },
			{ {0.5f, -0.5f, 0} },
			{{0.5f, 0.5f, 0}},
		};

		// 頂点バッファ作成
		// ・上記で作った３つの頂点はそのままでは描画に使用できないんす…
		// ・ビデオメモリ側に「頂点バッファ」という形で作る必要があります！
		// ・今回は効率無視して、その場で作って、使って、すぐ捨てます。
		//-----------------------------
		// 作成するバッファの仕様を決める
		// ・今回は頂点バッファにするぞ！って感じの設定
		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // これは頂点バッファだぞ！
		vbDesc.ByteWidth = sizeof(v); // 作るバッファのサイズ
		vbDesc.MiscFlags = 0;
		vbDesc.Usage = D3D11_USAGE_DEFAULT; // 作成するバッファの使用法
		vbDesc.CPUAccessFlags = 0; // CPUからアクセスする必要があるかどうか

		ComPtr<ID3D11Buffer> vb;
		D3D11_SUBRESOURCE_DATA initData = { &v[0], sizeof(v), 0 };
		//頂点バッファ作成
		D3D.m_device->CreateBuffer(&vbDesc, &initData, &vb);

		// 頂点バッファを描画で使えるようにセット
		UINT stride = sizeof(VertexType); // 1頂点のサイズ
		UINT offset = 0; // オフセット
		D3D.m_deviceContext->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);

		D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//シェーダーをセット
		D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), nullptr, 0);
		D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), nullptr, 0);
		D3D.m_deviceContext->IASetInputLayout(D3D.m_spriteInputLayout.Get());

		//こんな感じで、ひたすらデバイスコンテキストに情報を渡す

		D3D.m_deviceContext->Draw(4, 0);
	}

	D3D.m_swapChain->Present(1, 0);
}