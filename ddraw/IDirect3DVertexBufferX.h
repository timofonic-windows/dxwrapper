#pragma once

class m_IDirect3DVertexBufferX : public IDirect3DVertexBuffer7
{
private:
	IDirect3DVertexBuffer7 *ProxyInterface;
	m_IDirect3DVertexBuffer7 *WrapperInterface;
	DWORD DirectXVersion;
	DWORD ProxyDirectXVersion;
	IID WrapperID;

public:
	m_IDirect3DVertexBufferX(IDirect3DVertexBuffer7 *aOriginal, DWORD Version, m_IDirect3DVertexBuffer7 *Interface) : ProxyInterface(aOriginal), DirectXVersion(Version), WrapperInterface(Interface)
	{
		WrapperID = (DirectXVersion == 1) ? IID_IDirect3DVertexBuffer :
			(DirectXVersion == 7) ? IID_IDirect3DVertexBuffer7 : IID_IDirect3DVertexBuffer7;

		REFIID ProxyID = ConvertREFIID(WrapperID);
		ProxyDirectXVersion = (ProxyID == IID_IDirect3DVertexBuffer) ? 1 :
			(ProxyID == IID_IDirect3DVertexBuffer7) ? 7 : 7;

		if (ProxyDirectXVersion != DirectXVersion)
		{
			Logging::LogDebug() << "Convert Direct3DVertexBuffer v" << DirectXVersion << " to v" << ProxyDirectXVersion;
		}
	}
	~m_IDirect3DVertexBufferX() {}

	DWORD GetDirectXVersion() { return DirectXVersion; }

	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID * ppvObj);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	/*** IDirect3DVertexBuffer7 methods ***/
	STDMETHOD(Lock)(THIS_ DWORD, LPVOID*, LPDWORD);
	STDMETHOD(Unlock)(THIS);
	STDMETHOD(ProcessVertices)(THIS_ DWORD, DWORD, DWORD, LPDIRECT3DVERTEXBUFFER7, DWORD, LPDIRECT3DDEVICE7, DWORD);
	STDMETHOD(GetVertexBufferDesc)(THIS_ LPD3DVERTEXBUFFERDESC);
	STDMETHOD(Optimize)(THIS_ LPDIRECT3DDEVICE7, DWORD);
	STDMETHOD(ProcessVerticesStrided)(THIS_ DWORD, DWORD, DWORD, LPD3DDRAWPRIMITIVESTRIDEDDATA, DWORD, LPDIRECT3DDEVICE7, DWORD);
};
