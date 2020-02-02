#ifndef _PSTREE_H_
#define _PSTREE_H_

#include <wtypes.h> // to get num of running processes
#include <tchar.h> // to use tchar
#include "process.h"

class PSTree {
	Process *root; // root process(init process)
				   // 동적 할당(Process의 매개변수 있는 생성자 사용 위함)을 위해 포인터로 선언

public:
	// 생성자 함수
	// initialize root process
	PSTree(TCHAR nameOfRoot[], DWORD pidOfRoot, DWORD ppidOfRoot);

	// input : address of current process, pid of parent process
	// output : return address of parent process
	//		    when we can't find prarent process(when the parent process dies), return null
	Process* findParentProcess(Process *currentProcess, DWORD ppid);

	// add new process to process tree
	// input : information of the new process
	void addProc(TCHAR name[], DWORD pid, DWORD ppid);

	// input : current process, the number of indentations to print out process's information
	// output : print out information of current process
	void printProcess(Process *currentProc, int indent, int *iOfProc);

	// print process tree
	void printPSTree();
};

#endif

