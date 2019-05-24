#pragma once

class lTrigger {
public:
	void Run(CUserCmd* pCmd);
private:
	void DoTrigger(CUserCmd* pCmd, C_BaseEntity* LocalPlayer);
}; extern lTrigger* g_Trigger;