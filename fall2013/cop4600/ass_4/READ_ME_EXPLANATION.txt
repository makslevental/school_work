Maksim Levental
COP4600 Fall 2013

Picture 2:

I compiled and ran the linux kernel, using the Debian file system, on own computer, using VirtualBox. At the bottom you can see that the user logged into the host linux machine is max@max-VirtualBox. Also you can see me running the linux kernel in user mode.

Picture 3:

At the login prompt for UML.

Picture 4: 

Logged in as root.

Picture 5:

Editing the unistd_64.h file inside the linux-3.2 dir.

Picture 6:

Editing syscalls.h inside the linux-3.2 dir.

Picture 7:

Editing sys.c inside the linux-3.2 dir.

Picture 8:

I then mounted the Debian file system inside my own linux file system. I mounted it to /mnt/deb and created a test directory folder inside the home folder. I then created test.c in that folder and entered the code from the instructions.

Picture 9: I used g++ on my own computer to compile test.c as test.

Picture 10: I then unmounted the Debian file system from my own linux file system so that I could mount it under UML.

Picture 11:

Showing that it did in fact mount and I see the test executable.

Picture 12:

Running the executable which makes the system call.

-----------

bob.sh is the bash script I used to automate building the kernel.



