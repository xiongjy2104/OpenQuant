#pragma once
#include "Include/FTPluginCore.h"
#include "Include/FTPluginQuoteInterface.h"
#include "Include/FTPluginTradeInterface.h"
#include "PluginQuoteServer.h"
#include "PluginHKTradeServer.h"
#include "PluginUSTradeServer.h"
#include "PluginNetwork.h"
#include "MsgHandler.h"

//示例工程说明见ReadMe.txt

IFTPluginMoudle*  __stdcall GetFTPluginMoudle(int& nVerSupport);
void ReleasePluginMoudle();

class CPluginModule: 
	public IFTPluginMoudle,
	public IPluginNetEvent,
	public CMsgHandlerEventInterface
{
public:
	CPluginModule();
	virtual ~CPluginModule();

protected:
	//IFTPluginMoudle
	virtual void Init(IFTPluginCore* pPluginCore);
	virtual void Uninit();
	virtual LPCWSTR	GetName();
	virtual GUID    GetGuid(); 
	virtual void 	ShowPlugin(bool bShow);
	virtual void  GetPluginCallback_Quote(IQuoteInfoCallback** pCallback); 
	virtual void  GetPluginCallback_TradeHK(ITradeCallBack_HK** pCallback); 
	virtual void  GetPluginCallback_TradeUS(ITradeCallBack_US** pCallback);
	virtual void  GetPluginCallback_QuoteKL(IQuoteKLCallback** pCallback);

	//IPluginNetEvent
	virtual void OnReceive(SOCKET sock);
	virtual void OnSend(SOCKET sock);
	virtual void OnClose(SOCKET sock);

	//CMsgHandlerEventInterface
	virtual void OnMsgEvent(int nEvent,WPARAM wParam,LPARAM lParam);

protected:
	void	OnRecvNetData(SOCKET sock);
	void	ParseRecvData(SOCKET sock, char *pBuf, int nBufLen);

protected:
	IFTPluginCore*		m_pPluginCore;
	CPluginQuoteServer	m_QuoteServer;
	CPluginHKTradeServer m_HKTradeServer;
	CPluginUSTradeServer m_USTradeServer;
	CMsgHandler			m_MsgHandler;
	CPluginNetwork		m_Network;
	std::string			m_strRecvBuf;
};