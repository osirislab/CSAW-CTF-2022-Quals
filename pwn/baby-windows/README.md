
### Baby Windows

    This challenge is a very basic introduction to Windows binary exploitation. It's literally a `gets` buffer overflow with a jump to a Win function 
    ("`pwn`") in a DLL. We give the players all the source code.

    It's the most basic challenge we can possibly do. The idea here is that if the players get their tooling working, they'll get the solve.
    And then they get rewarded for setting up their tools. They still need to mess around with Ghidra, Ollydbg, maybe Windbg or Immunity Debugger.
    And they may need to figure out how to debug a process running in a Docker container.

    Some of these steps they may avoid by just figuring out the code they need to jump to and then getting the exploit right without debugging.
    That's possible. Even so, it will be useful to them to have this challenge here so that they can debug things when they start working on the 
    next challenge -- the shellcoding challenge -- and get stuck.

    I'm thinking 200 points for this challenge. And 150 of those points are a reward for setting up their Windows tooling.


    Questions during testing:

    1. Do we need to give people a walkthough for setting up an AWS EC2 Windows Server 2019 with Containers Instance? Or is it enough to just tell people to do that?
    2. How did you decide to debug this? Was that part difficult for you?
    3. Is it fun to solve or is it tedious? 

    Note to infra team: 
    1. I put a 120-second timeout on this function in multiple places: socat.exe, an alarm event that fires after 120 seconds, 
    and a 120-second sleep command. So a bunch of teams are going to be connecting and then running for no more than two minutes. This should be 
    robust for us. The next Windows challenge will be trickier because players will be writing shellcode, and some players could write shellcode 
    that does busy waiting (infinite loop).
    2. The Docker container is locked down -- the flag is read-only and so are the Windows DLLs. Someone would have to try pretty hard to 
    mess things up for us.
    3. The auto-deploy script will not work out of the box because this challenge needs to run on Windows Server 2019 with Containers in AWS.
    4. To build and run the Dockerfile once it's in the AWS instance: 
       `docker build --tag=babywindows .`
       `docker run -dit --restart=always -p 7777:7777 babywindows`


    Note to tester: If you want to run the solver, run the following:
    1. >!`python3 exploit-babywindows.py DEBUG`
    >!Note the DEBUG parameter. This is part of the challenge. Windows sends carriage returns back and the Linux terminal 
    >!interprets this as a command to clear the line. So players logging into Windows will see a prompt but not all the 
    >!text they expect. DEBUG shows that the characters are getting properly received and then are not displaying in the terminal.
    >!Tricky!
