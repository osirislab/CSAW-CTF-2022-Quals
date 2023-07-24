#include <windows.h>
#include <stdio.h>
#include "ShelloWorldLib.h"
#include <winbase.h>
#include <threadpoollegacyapiset.h>

HANDLE gDoneEvent;
HANDLE hTimerQueue;

VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired){
    printf("Alarm clock triggered. Exiting to conserve resources on the server.\n");
    ExitProcess(0);
    SetEvent(gDoneEvent);
}

int Alarm(int timeOut){
    //Complicated routine that does the same thing as the one-line alarm(120) in Linux
    // https://docs.microsoft.com/en-us/windows/win32/sync/using-timer-queues
    HANDLE hTimer = NULL;
    hTimerQueue = NULL;
    int timerArg = 0; // Argument to the timer routime, we don't really use it but it's part of the API
    gDoneEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (NULL == gDoneEvent)
    {
        printf("CreateEvent failed (%d)\n", GetLastError());
        return 1;
    }

    hTimerQueue = CreateTimerQueue();
    if (NULL == hTimerQueue)
    {
        printf("CreateTimerQueue failed (%d)\n", GetLastError());
        return 2;
    }

    // Set a timer to call the timer routine in 120 seconds.
    if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)TimerRoutine, &timerArg, timeOut, 0, 0)){
        printf("CreateTimerQueueTimer failed (%d)\n", GetLastError());
        return 3;
    }
    return 0;
}

int CleanUp(){
    CloseHandle(gDoneEvent);

    // Delete all timers in the timer queue.
    if (!DeleteTimerQueue(hTimerQueue))
        printf("DeleteTimerQueue failed (%d)\n", GetLastError());
}

void Vuln(){
    char buf[500];
    printf("Okay, give me some input!\n\n> ");
    fflush(stdout);
    gets(buf);
    printf("Thanks for playing...\n");
    fflush(stdout);
    return;
} 

int RunChallenge(){
    fflush(stdout);
    printf("WELCOME TO \n\n\n");
    PrintCSAWBanner();
    printf("\n\nSTARRING");
    printf("\n\n");
    PrintOS();
    printf("\n\n");

    puts("   Welcome to the second in a set of two introductory Windows pwnables. Your mission is to write your first Windows shellcode!");
    puts("Look to BabyWindows.c in the BabyWindows challenge for info about getting started with the tooling. Any practice you got with");
    puts("using debuggers or Windows docker containers from that challenge will help you here, as you will almost certainly need to debug");
    puts("your shellcode as it runs in the Docker container in order to get it right. We've also disabled some security protections for");
    puts("your convenience.\n");

    puts("   We are providing a hint here to save our poor infra team. If you worked on the first Windows challenge you may notice that a ");
    puts("call to spawn a Windows shell is asynchronous, unlike Linux. That means after your shell is spawned, you'll need the process to do");
    puts("something instead of immediately exiting. An easy thing to write shellcode to do is to run in an infinite loop, but it would be");
    puts("painful for our infra team if every team maxed out a CPU thread in the last hour. So we've placed an appropriately-labeled"); 
    puts("function in ShelloWorldLib.dll, which you can write your shellcode to jump to after spawning a shell.\n");

    Vuln();
    return 0;
}

int main(){
    SetProcessDEPPolicy(0); // opt out of DEP
    Alarm(120000); // Alarm clock, timeout is in milliseconds
    RunChallenge();
    CleanUp();
    return 0;
}