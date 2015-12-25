#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>


DWORD dwClient, dwEngine;

const DWORD dwLocalPlayer = 0xA7AFAC;
const DWORD dwEntityList = 0x4A1D384;
const DWORD m_fFlags = 0x100;
const DWORD m_lifeState = 0x25B;
const DWORD m_iTeam = 0xF0;
const DWORD m_iCrosshairID = 0x2410;
const DWORD dwEntityIndex = 0x64;
const DWORD entityJump = 0x10;


class Funcs{
private:
	HANDLE _process;
	DWORD _pID;
public:
	bool Hook(char* process){
		HANDLE PHANDLE = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
		PROCESSENTRY32 pENTRY;
		pENTRY.dwFlags = sizeof(pENTRY);
		do{if(!strcmp(pENTRY.szExeFile, process)){
			_pID = pENTRY.th32ProcessID;
			CloseHandle(PHANDLE);
			_process = OpenProcess(PROCESS_VM_READ, FALSE, _pID);
			return true;
		}}while(Process32Next(PHANDLE, &pENTRY));
		return false;}
	DWORD GetModule(char* module){

	HANDLE HModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _pID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);
	do{if(!strcmp(mEntry.szModule, module)){
		CloseHandle(HModule);
		return (DWORD)mEntry.modBaseAddr;
	}}while (Module32Next(HModule, &mEntry));
	return false;}
	DWORD Read(DWORD address){
		DWORD value;
		ReadProcessMemory(_process, (DWORD*)address, &value, sizeof(value), NULL);
		return value;
	}
	void Write(DWORD address, int value){
		WriteProcessMemory(_process,(DWORD*)address, &value, sizeof(value), NULL);
	}
	
};
Funcs funcs;

struct Vec3_t
{
    float x;
    float y;
    float z;
};

struct myPlayer_t{
	DWORD LocalPlayer;
	int flag;
	int team;
	int chid;

	void readinfo(){
		 LocalPlayer = funcs.Read(dwClient + dwLocalPlayer);
		 flag = funcs.Read(LocalPlayer + m_fFlags);
		 team = funcs.Read(LocalPlayer + m_iTeam);
		 chid = funcs.Read(LocalPlayer + m_iCrosshairID);
	}
}myPlayer;

struct entityList_t{
	DWORD BaseEntity;
	int flag;
	int team;


	void readinfo(int player){
		BaseEntity = funcs.Read(dwClient + dwEntityList +(player*10));
		 flag = funcs.Read(BaseEntity + m_fFlags);
		 team = funcs.Read(BaseEntity + m_iTeam);

	}
}entityList[32];