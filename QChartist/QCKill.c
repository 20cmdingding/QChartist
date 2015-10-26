#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

int main(void) {

  // création du snapshot
  HANDLE sys = NULL;
  if (!(sys = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0))) {
    fprintf(stderr, "Snapshot failure.\n");
    return EXIT_FAILURE;
  }

  // ouverture du premier process
  PROCESSENTRY32 proc;
  ZeroMemory(&proc, sizeof(proc));
  proc.dwSize = sizeof(proc);
  if (!Process32First(sys, &proc)) {
    fprintf(stderr, "Process32First failure.\n");
    return EXIT_FAILURE;
  }

  // on cherche le process qchartist
  DWORD myproc = 0;
  do {
    if (lstrcmp(proc.szExeFile, "QChartist.Exe") == 0) {
      myproc = proc.th32ProcessID;
      break;
    }
  } while (Process32Next(sys, &proc));
  CloseHandle(sys);

  // qchartist n'est probablement pas lancé (vérifier GetLastError pour en être sûr)
  if (!myproc) {
    fprintf(stderr, "Process32Next failure.\n");
    return EXIT_FAILURE;
  }

  // ouverture du process qchartist
  HANDLE myprochandle = NULL;
  if (!(myprochandle = OpenProcess(PROCESS_TERMINATE, FALSE, myproc))) {
    fprintf(stderr, "OpenProcess failure.\n");
    return EXIT_FAILURE;
  }

  // terminaison du process qchartist
  TerminateProcess(myprochandle, 0);
  CloseHandle(myprochandle);

  // fin du programme
  return EXIT_SUCCESS;

}