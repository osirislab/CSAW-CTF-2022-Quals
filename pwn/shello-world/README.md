
### Shello World

    This challenge introduces players to Windows shellcoding. It's a `gets` buffer overflow with an executable stack and
    a gadget that allows for a pivot of the instruction pointer to the stack. It's a 32-bit binary.

    Most of the time, when people run Windows shellcode, they are on an actual computer. And so they can create a socket,
    bind cmd.exe to it, and listen for an incoming connection. And since those calls are all asynchronous the original 
    thread running the shellcode can gracefully exit and the listener will still be running. In a Docker container we 
    only unblock one port for incoming connections, so the player has to either tweak shellcode available in Metasploit
    to just execute cmd.exe instead of binding to a new port, or else they have to write their own shellcode (I did the 
    latter as a learning experience but the former would be faster if it's feasible). 


    There are lots of gotchas:
    1. There are more bad characters for Windows shellcode than Linux shellcode.
    2. The shellcode has to be encoded to avoid those characters and that will require msvenom.
    3. The gadget they can jump to in the DLL is not part of an exposed function, so they may miss it in Ghidra but they'd 
       find it using ROPGadget or if they're looking at the symbols and not the function names.
    4. They may have difficulty spinning up the Docker container, although we caution them that they may need AWS for this 
       and there's a free-tier solution.
    5. It's not clear to me that everyone will know to create an EC2 instance with enough disk space. Although we do tell
       players to refer to the first Windows challenge for tooling-related guidance.
    6. Unlike with Linux, the call to WinExec('cmd.exe') is asynchronous and so the thread has to not immediately crash 
       after that call in order for the command prompt to remain open for players once they spawn a shell. They'll have 
       to figure out how to do that. One way, unfortunately, is to create an infinite loop, which can drain our resources.
       I dealt with that in three ways: I put a two-minute alarm on the program (so a team would keep one of our CPUs engaged
       at 100% for a max of two minutes); I put a "BeKindToTheCSAWInfraTeam" function in the DLL so that it's easy and just 
       as fast for someone to jump there; and Jasmine is looking to set up a Powershell script to patrol the Resource Monitor 
       and kill instances of ShelloWorld.exe that are hogging CPU time.
    7. The gadget they need is at the end of a NOP sled. The fun part is most of the addresses in the NOP sled are in 
       an address range that has a bad byte in it. Putting the address with a bad byte in the shellcode keeps it from 
       getting sent at all (I think it's because Windows thinks a NAK is being sent instead of the shellcode). That's a 
       nice teachable moment for people, so I left it in.


    Infra Note: 
    1. I put a 120-second timeout on this function in multiple places: socat.exe, an alarm event that fires after 120 seconds, 
    and a 120-second sleep command. So a bunch of teams are going to be connecting and then running for no more than two minutes. This should be 
    robust for us. The next Windows challenge will be trickier because players will be writing shellcode, and some players could write shellcode 
    that does busy waiting (infinite loop).
    2. The Docker container is locked down -- the flag is read-only and so are the Windows DLLs. Someone would have to try pretty hard to 
    mess things up for us.
    3. The auto-deploy script will not work out of the box because this challenge needs to run on Windows Server 2019 with Containers in AWS.
    4. To build and run the Dockerfile once it's in the AWS instance: 
       `docker build --tag=shello-world .`
       `docker run -dit --restart=always -p 7778:7778 shello-world`


    Solver Note: If you want to run the solver, run the following:
    1. >!`python3 exploit-shelloworld.py DEBUG`
    >!Note the DEBUG parameter. This is part of the challenge. Windows sends carriage returns back and the Linux terminal 
    >!interprets this as a command to clear the line. So players logging into Windows will see a prompt but not all the 
    >!text they expect. DEBUG shows that the characters are getting properly received and then are not displaying in the terminal.
    >!Tricky!
    >!Also note that this exploit currently runs an infinite loop after spawning the shell. It's basically a minimum viable product for now.

