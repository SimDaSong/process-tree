#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <vector>
#include <tchar.h> // to use TCHAR
#include <wtypes.h> // to use DWORD
#include "process.h"

class Process {
	TCHAR *name; // name of process
	DWORD pid, ppid; // process id, parent process id
	DWORD newPpid; // when a parent process dies, the root process will be parent process of this process
				   // �����ͷ� parent process�� �����ѵ� ������, �׷��� �ϸ� �޸� ���� ����� �����̴�.(�θ� ���μ����� ���� �� ���� ��� �;��ϴ� ������ ppid��)
	std::vector<Process> children; // child processes

public:
	/// ������ �Լ� ///
	Process(TCHAR name[], DWORD pid, DWORD ppid);

	/// process ���� ��� �Լ��� ///
	Process* getChild(int i);
	int getSizeOfChildren();
	DWORD getPID();
	DWORD getPPID();

	/// process ���� ���� �Լ��� ///
	void setNewPPID(DWORD newPpid);
	void addChild(Process p);

	// has the process any child process?
	bool hasChild();

	// print information of process
	void printProcInfo();
};


#endif