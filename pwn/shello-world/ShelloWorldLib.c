#include "ShelloWorldLib.h"
#include <stdio.h>
#include <windows.h>
#include <synchapi.h>

void PrintCSAWBanner(){
    printf(" #####   #####     #    #     #     #####    ###    #####   ##### \n");
    printf("#     # #     #   # #   #  #  #    #     #  #   #  #     # #     #\n");
    printf("#       #        #   #  #  #  #          # #     #       #       #\n");
    printf("#        #####  #     # #  #  #     #####  #     #  #####   ##### \n");
    printf("#             # ####### #  #  #    #       #     # #       #      \n");
    printf("#     # #     # #     # #  #  #    #        #   #  #       #      \n");
    printf(" #####   #####  #     #  ## ##     #######   ###   ####### #######\n");
    return;
}

void PrintOS(){
    printf("__        ___           _                     ____   ___  _  ___    ____                               \n");
    printf("\\ \\      / (_)_ __   __| | _____      _____  |___ \\ / _ \\/ |/ _ \\  / ___|  ___ _ ____   _____ _ __     \n");
    printf(" \\ \\ /\\ / /| | '_ \\ / _` |/ _ \\ \\ /\\ / / __|   __) | | | | | (_) | \\___ \\ / _ \\ '__\\ \\ / / _ \\ '__|    \n");
    printf("  \\ V  V / | | | | | (_| | (_) \\ V  V /\\__ \\  / __/| |_| | |\\__, |  ___) |  __/ |   \\ V /  __/ |       \n");
    printf("   \\_/\\_/  |_|_| |_|\\__,_|\\___/ \\_/\\_/ |___/ |_____|\\___/|_|  /_/  |____/ \\___|_|    \\_/ \\___|_|       \n");   
}

void SuspiciousGadget(){
    __asm__(
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "nop;"
        "jmp *%esp;"
        "ret;"
    );
    return;
}

void BeKindToYourCSAWInfraTeam(){
    // Give shell
    // WinExec("cmd.exe", SW_SHOWDEFAULT);
    // The above call is asynchronous, unlike system("/bin/sh") in Linux.
    // For this challenge the player is finding a way to execute that call with shellcode.
    // Lots of Windows shellcode deals with the asynchronicity by creating a new socket and executing cmd.exe in a new process
    // listening on that socket. Then the shellcode gracefully exits the original program. 
    // This challenge is running in a Docker container with one exposed port, so that's not an option.

    // This code is here for the player to jump to after executing WinExec('cmd.exe'). 
    // If we didn't provide this, the average player would just create an infinite loop with 
    // their shellcode and our CPUs could get maxed out during the final hours of the competition. 
    Sleep(120000); // Two minutes
    ExitProcess(0);
}
//C:\msys64\mingw32\bin\gcc.exe -m32 -DCSAW_EXPORTS -shared -Wl,--image-base=0x62100000,--disable-dynamicbase,--disable-nxcompat,--disable-reloc-section -o CSAWLib.dll CSAWLib.c