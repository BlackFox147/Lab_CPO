#include "headers.h"



void CreateSignal()
{
	HANDLE Event = CreateEvent(NULL, FALSE, FALSE,"MyEvent");

	if (Event)
		SetEvent(Event);
	else
		exit(0);
}



void CreateNewProcess(struct Data *data, struct Stack **stack)
{
	STARTUPINFO stInfo;
	PROCESS_INFORMATION prInfo;

	ZeroMemory(&stInfo, sizeof(STARTUPINFO));
	stInfo.cb = sizeof(STARTUPINFO);

	CreateProcess("mainW.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &stInfo, &prInfo);
	struct Data data_pr;
	data_pr.prInfo = prInfo;

	push(stack, data_pr);

}

void CloseProcess(struct Stack **stack, struct Data *data, int code)
{
	HANDLE Event = OpenEvent(EVENT_ALL_ACCESS, FALSE, "MyEvent");

	if (Event == NULL)
		exit(0);

	WaitForSingleObject(Event, INFINITE);
	if (code == 0){
		TerminateProcess((*stack)->hand, 0);
		pop(stack);

		SetEvent(Event);
	}
	else if (code == 1){
		while (size(*stack) != 0)
		{
			TerminateProcess((*stack)->hand, 0);
			pop(stack);
		}
//		system("cls");
	}

}
