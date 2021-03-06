#pragma once

#include "DomoticzHardware.h"

class CLimitLess : public CDomoticzHardwareBase
{
      public:
	enum _eLimitlessBridgeType
	{
		LBTYPE_V4 = 0,
		LBTYPE_V5,
		LBTYPE_V6
	};
	CLimitLess(int ID, int LedType, int BridgeType, const std::string &IPAddress, unsigned short usIPPort);
	~CLimitLess() override = default;
	bool WriteToHardware(const char *pdata, unsigned char length) override;

      private:
	bool AddSwitchIfNotExits(unsigned char Unit, const std::string &devname);
	bool GetV6BridgeID();
	bool SendV6Command(const uint8_t *pCmd);
	void Send_V6_RGBWW_On(uint8_t dunit, long delay);
	void Send_V6_RGBW_On(uint8_t dunit, long delay);
	void Send_V4V5_RGBW_On(uint8_t dunit, long delay);
	bool IsDataAvailable(SOCKET sock);
	void Init();
	bool StartHardware() override;
	bool StopHardware() override;
	void Do_Work();

      private:
	_eLimitlessBridgeType m_BridgeType;
	unsigned char m_LEDType;

	uint8_t m_BridgeID_1;
	uint8_t m_BridgeID_2;
	uint8_t m_CommandCntr;

	std::string m_szIPAddress;
	unsigned short m_usIPPort;

	SOCKET m_RemoteSocket;
	sockaddr_in m_stRemoteDestAddr;

	std::shared_ptr<std::thread> m_thread;
};
