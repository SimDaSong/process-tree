#include <iostream>
#include <wtypes.h> // to get num of running processes
#include <Psapi.h> // to get num of running processes
#include <TlHelp32.h> // to use createToolhelp32Snapshot()
#include "pstree.h"

int main() {

	/// identifier declaration ///
	HANDLE hProcessSnap; // ���μ����� snap
	PROCESSENTRY32 pe32; // ���μ����� ������ ��� ����ü
	int numOfProc = 0; // �� ���μ����� ��

	/// snap process ///
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		puts("CreateToolhelp32Snapchot error");
		exit(EXIT_FAILURE);
	}

	/// get first process(init process) ///
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32)) {
		puts("Process32First error!");
		CloseHandle(hProcessSnap);
		exit(EXIT_FAILURE);
	}
	numOfProc++;

	/// get all processes ///
	PSTree pstree(pe32.szExeFile, pe32.th32ProcessID, pe32.th32ParentProcessID); // set init process as root process of pstree
	// ���� ���μ������� ������ �޾� Ʈ�� �����
	while (Process32Next(hProcessSnap, &pe32)) {
		pstree.addProc(pe32.szExeFile, pe32.th32ProcessID, pe32.th32ParentProcessID);
		numOfProc++;
	}

	/// print ///
	puts("########### process tree ############");
	printf("Number of Running Processes = %d\n", numOfProc);
	pstree.printPSTree();

}

