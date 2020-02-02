#include <vector>
#include <tchar.h> // to use TCHAR
#include <wtypes.h> // to use DWORD
#include "process.h"

/// ������ �Լ� ///
Process::Process(TCHAR name[], DWORD pid, DWORD ppid) {
	int nameLength = _tcslen(name);
	this->name = new TCHAR[nameLength + 1];
	_tcscpy(this->name, name);
	this->pid = pid;
	this->ppid = ppid;
	newPpid = ppid;
}

/// process ���� ��� �Լ��� ///
Process* Process::getChild(int i) { return &children[i]; }
int Process::getSizeOfChildren() { return children.size(); }
DWORD Process::getPID() { return pid; }
DWORD Process::getPPID() { return ppid; }

/// process ���� ���� �Լ��� ///
void Process::setNewPPID(DWORD newPpid) { this->newPpid = newPpid; }
void Process::addChild(Process p) { children.push_back(p); }

// has the process any child process?
bool Process::hasChild() {
	if (children.size()) return true;
	return false;
}

// print information of process
void Process::printProcInfo() {
	printf("+-%S<%d><%d:%d>\n", name, pid, newPpid, ppid);
}
