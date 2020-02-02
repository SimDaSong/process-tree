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
				   // 포인터로 parent process를 가리켜도 되지만, 그렇게 하면 메모리 낭비가 생기기 때문이다.(부모 프로세스의 정보 중 내가 담고 싶어하는 정보는 ppid뿐)
	std::vector<Process> children; // child processes

public:
	/// 생성자 함수 ///
	Process(TCHAR name[], DWORD pid, DWORD ppid);

	/// process 정보 얻는 함수들 ///
	Process* getChild(int i);
	int getSizeOfChildren();
	DWORD getPID();
	DWORD getPPID();

	/// process 정보 세팅 함수들 ///
	void setNewPPID(DWORD newPpid);
	void addChild(Process p);

	// has the process any child process?
	bool hasChild();

	// print information of process
	void printProcInfo();
};


#endif