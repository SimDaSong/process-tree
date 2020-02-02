#include <iostream>
#include <wtypes.h> // to use DWORD
#include <tchar.h> // to use TCHAR
#include "process.h"
#include "pstree.h"

// 생성자 함수
// initialize root process
PSTree::PSTree(TCHAR nameOfRoot[], DWORD pidOfRoot, DWORD ppidOfRoot) {
	root = new Process(nameOfRoot, pidOfRoot, ppidOfRoot);
}

// input : address of current process, pid of parent process
// output : return address of parent process
//		    when we can't find prarent process(when the parent process dies), return null
Process* PSTree::findParentProcess(Process *currentProcess, DWORD ppid) {
	// if the current process is the parent process we need to find, return address of current process
	if (currentProcess->getPID() == ppid) {
		return currentProcess;
	}

	// if current process has child
	if (currentProcess->hasChild()) {
		Process* child = NULL;
		Process* parent = NULL;

		// search child processes of current process to find the parent process we need to find
		for (std::vector<Process>::size_type iOfChild = 0; iOfChild < currentProcess->getSizeOfChildren(); iOfChild++) {
			child = currentProcess->getChild(iOfChild);
			if (parent = findParentProcess(child, ppid)) // if we find parent process we need to find, return that process
				return parent;
		}
		// if we can't find the parent processe even though search all child processes of current process, return null
		return NULL;
	}
	// if current process is not the parent process we need to find and has no child, return null
	else {
		return NULL;
	}
}

// add new process to process tree
// input : information of the new process
void PSTree::addProc(TCHAR name[], DWORD pid, DWORD ppid) {
	Process newProc(name, pid, ppid);

	// find parent process of the new process
	Process* parent = findParentProcess(root, newProc.getPPID());
	// if we can't find parent process, set root process as the parent process of the new process
	if (parent == NULL) {
		newProc.setNewPPID(0);
		root->addChild(newProc);
	}
	// if we find parent process, set the process as the parent process of the neww process
	else {
		newProc.setNewPPID(parent->getPID());
		parent->addChild(newProc);
	}
}

// input : current process, the number of indentations to print out process's information
// output : print out information of current process
void PSTree::printProcess(Process *currentProc, int indent, int *iOfProc) {
	// if current process any child process, print out informations of them
	Process* child;
	for (std::vector<Process>::size_type iOfChild = 0; iOfChild < currentProc->getSizeOfChildren(); iOfChild++) {
		printf("%03d ", (*iOfProc)++);
		for (int j = 0; j <= indent; j++) {
			printf("|\t");
		}
		child = currentProc->getChild(iOfChild);
		child->printProcInfo();

		// if child process has any child process print out them too
		if (child->hasChild()) {
			printProcess(child, indent + 1, iOfProc);
		}
	}
	indent++;
}

// print process tree
void PSTree::printPSTree() {
	int iOfProc = 1; // 출력되는 프로세스들의 index

	// first, print out information of root process
	printf("%03d ", iOfProc++);
	root->printProcInfo();
	// then, print out all processes
	printProcess(root, 0, &iOfProc);
}
