#include "main.h"


void bhop(){

	DWORD LocalPlayer = funcs.Read(dwClient + dwLocalPlayer);
				int iFlags = funcs.Read(LocalPlayer + m_fFlags);

				if(iFlags & (0x1 == 1)){
					keybd_event(MapVirtualKey(VK_SPACE, 0), 0x39, 0, 0);
					Sleep(20);
					keybd_event(MapVirtualKey(VK_SPACE, 0), 0x39, KEYEVENTF_KEYUP, 0);

}}

void trigger(){

	myPlayer.readinfo();
			for(int i=0;i<32;i++){
					entityList[i].readinfo(i);}


			DWORD EnemyInCH = funcs.Read(dwClient + dwEntityList + ((m_iCrosshairID - 1) * entityJump));
			int EnemyTeam = funcs.Read(EnemyInCH + m_iTeam);


			if(myPlayer.chid != 0 && myPlayer.chid > 0 && myPlayer.chid < 32 && myPlayer.team != EnemyTeam){
					mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP,0,0,0,0);
					Sleep(10);
			}
}


BOOL WINAPI DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved ) 
{
	if( dwReason == DLL_PROCESS_ATTACH ){ 
		if(!funcs.Hook("csgo.exe")){MessageBox(0,"failed to hook csgo.exe","error",0);exit(0);}

		dwClient = funcs.GetModule("client.dll");
		MessageBox(0,"injected!","success",0);
			
		
		while(!GetAsyncKeyState(VK_END))
		{ /*panic key END*/
	
			trigger();

		if(GetAsyncKeyState(VK_SPACE)&0x8000){bhop();}
			
		}
		
	}MessageBox(0,"good bye","panic key",0);FreeLibraryAndExitThread(hModule,0);
	}

