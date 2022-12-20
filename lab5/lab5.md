Lab 5: Assembly cont. And System Calls
======================================

### Lab Goals

*   To get acquainted with the low-level interface to system calls.
*   To understand how programs can work without the standard library.
*   Calling assmebly code from C.
*   Basics of directory listings.

This lab can be done in pairs!
==============================

As usual, you should read and understand the reading material and complete task 0 before attending the lab.  
**For the entire lab, do not use the standard library! This means you shouldn't include stdio.h, stdlib.h, or any other file from the C standard library. You can, however, include your own files or any files we provide you. This also means that you cannot use any library functions like printf, fopen, fgetc, strcmp, etc.**

Task 0: Using nasm, ld and the Arguments Printing Program
---------------------------------------------------------

In this task we will build a program which prints its arguments to standard output without using the standard C library.

### Task 0.A: C Implementation

1.  Download the files main.c, start.s, util.c and util.h.
2.  Compile and link them without using the C standard library as follows:
    *   Assemble the glue code:  
        nasm -f elf32 start.s -o start.o
    *   Compile the main.c and util.c files into object code files:  
        gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector util.c -o util.o  
        gcc -m32 -Wall -ansi -c -nostdlib -fno-stack-protector main.c -o main.o
    *   Link everything together:  
        ld -m elf\_i386 start.o main.o util.o -o task0
3.  Write a makefile to perform the compilation steps automatically.
4.  Write a new main.c that prints the elements of argv to the standard output, without using stdlib.

**Explanation**  
The file "start.s" has two purposes:  

1.  Each executable must have an entry point - the position in the code where execution starts. By default, the linker sets this entry point to be a library supplied code or function that begins at \_start. This code is responsible for initializing the program. After initialization, this code passes control to the main() function. Since we are not using any standard libraries, we must supply the linker with \_start of our own - which is defined in start.s.
2.  The assembly-language source code in start.s also contains the system\_call function, which is used to get a direct system call without requiring you to write in assembly language. Note that you can link files written in different languages: an object file is an object file, no matter where it came from. All is machine code at some point!

### Task 0.B: Assembly Implementation

Recall task 1 from lab 4, where you implemeted the same program of arguments print. Use the code from lab 4 and instead of calling printf perform the printing functionality using system calls. Note that you can you the same makefile as in lab 4. For this sub-task you need to read about argument passing to a system call in assembly.

### Task 0.C: Recalling encoder from lab 1

Make sure you have a **good** implementation in C of the encoder from lab 1, in the sense that it has handled the tasks with a good understanding of low-level features. That is because later on in the lab you will need to implement a simplified form in assembly language with direct system calls. A good low-level C implementation will make the task immediate, whereas an implementation without a care for details and understanding of low-level features (e.g. what is the end of a "string"?) will be extremely unhelpful. Consider that any place you have used "strlen", "strcpy", strcmp", and especially if you did something like "strlen{encoding)%i" you are **not** well prepared.

If you **do not** have a good implementation of the encoder from lab 1, consider the following advice. You may also borrow lab 1 solutions in C from other people (**only**) as preparation for lab 5, but of course you should say your implementation is based on (appropriate citation) C code from another source. In this instance only this is permitted and will cause no grade reduction! If, on the other hand, you **do** have a good low level implementation of the encoder from lab 1, this task 0.C can be considered a "nop", and ignore the rest of task 0.C. That is, you are ready in this aspect due to a previously well done job! (As the saying goes **"Mi She Tarakh Be Erev Shabat, Yokhal Be Shabat"**).

#### Low-level encoder tips

A good low-level implementation of the encode is easy to transfer to assembly language. Good is according to the tips below:

1.  Note that you never need to "copy" a "string" in this task. Rather you can always maintain a pointer to its start, as do not need to modify such "strings". Therefore, you should not be copying any such, and certainly not use "strcpy". See next tip.
2.  Recall that a "string" is simply an array of bytes, and that a pointer can be seen as a reference to the array, or any part thereof if it is advanced. So no need to use "strcmp" to detect command-line flags. For example, to do the output file case, can simply do in the loop on arguments:
    
       char \* OutFileName;
       FILE \* OutFile;
       if(av\[i\]\[0\] == '-' && av\[i\]\[1\] == 'O') {  /\* Can actually be done in 1 instruction, e.g.:  CMP word \[eax\], '-'+(256\*'O')  ; equivalently "-O" \*/
           OutFileName = (av\[i\])+2;
    	   OutFile = fopen(OutFileName, "w");
    	   if(Outfile == NULL) { /\* error, print "cannot open file" and exit \*/}
       }
    
3.  To find the start of the encoding string, same (av\[i\])+2 as above works:
    
       unsigned char \* EncoderString, \* CurrentEncodeP, EncodeByte;
        if(av\[i\]\[0\] == '+' && av\[i\]\[1\] == 'e') {
           CurrentEncodeP = EncoderString = (av\[i\])+2;
    	   if(\*EncoderString == 0) /\* Error, null encoder string, exit \*/
       }
       /\* And then, later on, after getting each character c: \*/
       EncodeByte = (\*CurrentEncodeP)-'0';
       c += EncodeByte;
       CurrentEncodeP++;
       /\* And then below wrap around to start at null termination \*/
       if(\*CurrentEncodeP == 0) { CurrentEncodeP = EncoderString; }  
    

Task 1: Encryption In Assembly
------------------------------

**All of the code in this task supposed to be written in assembly. Including argument parsing.**  
Recall the encryption in the encoder program from lab 1 (a long time ago!). We want to implement the **encryption** program in **assembly using system calls**.  
The encryption program should support the following command-line arguments:

*   +e{key} (just + this time, no need to implement the -e{key} option).
*   \-i{file} - get input from the given file.
*   \-o{file} - direct output to the given file.

### Task 1.A: Basic Encryption Version

In this section you are required to implement the encoder program while supporting the command line argument of +e{key}, the input\\output are from\\to stdin\\stdout (use the appropriate system calls for reading or writing). **If +e{key} argument is not provided the input is not changed!.**

### Task 1.B: Encryption With Input and Output Support

Add to your program the option of the following command line arguments:

*   \-i{file} - get input from the given file.
*   \-o{file} - direct output to the given file.

### Task 2: Attach Virus Program

Many computer viruses attach themselves to executable files that may be part of legitimate programs. If a user attempts to launch an infected program, the virus code is executed before the infected program code. The goal is to write a program that attaches its code to files in the current directory.

**In this task you are required to write both in C and assembly. Your C program should call sys\_getdents in order to get all the entries in the current directory and print them, and when the -a{prefix} argument is provided should call assembly functions that will attach the executable code to the desired files.**

  
In this task you are required to implement the following program:  

**DESCRIPTION**  
Print all the file names in the current directory.

**COMMAND-LINE ARGUMENT**  
**\-a{prefix}**  
Attach the executable code (be discussed more below) at the end of each file in the current directory that begins with the given prefix. For every file changed you should print a message to the user, i.e., when printing the file name as a part of the file list add a print comment **"VIRUS ATTACHED"** next to the file name.

#### Some guidelines

1.  Your program should use the **sys\_getdents \[141\]** system call.
2.  The declarations of the dirent type constants can be found in the file dirent.h
3.  Please note that the first argument for getdents is a file descriptor open for reading - it should be for the file "." that represents the current directory.
4.  In case of an error, the program should terminate with exit code 0x55.
5.  To make things easier, you may assume that the entire directory data (returned by the getdents call) is smaller than 8192 bytes.
6.  Dont forget not to use any standard library functions!. Instead, in "util.h" and "util.c", you can find few implementation for some helpful functions. You may use them.

**Warning:** You probably want to be very sure that the mechanism for selecting files works correctly at this point, e.g. you may not want the program to operate on your C source code files, etc. Be careful not to destroy your own source code files!  
  
**The following contains code you need to write in assembly language.**

1.  Starting assembly language implementation: begin with a label "code\_start".
2.  Write a function **void infection(int)** that prints to the screen the message "Hello, Infected File". Note: this should be done using just one system call! If you have too many lines of code here then you are doing something wrong!
3.  Write a function **void infector(char \*)** that opens the file named in its argument, and adds the executable code from "code\_start" to "code\_end" after the end of that file, and closes the file. Note: this should be done using just a few system calls: open (for append), write, close, each using less than 10 lines of assembly code. Again, if your code is longer then you are doing something wrong!
4.  End infected program part with a label "code\_end".
5.  When the flag -a{prefix} is supplied, it will call the infector functions in order to add the executable code of infection to the end of each file with the given prefix. Also, this option will print out a comment such as "VIRUS ATTACHED" next to each file with the given prefix (this print will be performed in the C program).

  
**Note: it is recommended to open the file with the append option. You **may** open for reading/writing rather than append, but then you will have to perform the lseek system call to the end of the file.**  
  
**Note for assembly language implementation:** The part of the code that is responsible for actual file handling (i.e. opening the file, adding the executable code of the infection , etc.) should be written in assembly language and done inside the file "start.s". You can add the code after the end of the code for system\_call. You can either call the system\_call code (note that it uses C calling conventions, as until now you used it through function-calls from C), or re-use part of it to do the system call yourself (shorter and simpler!). Also, it is a good idea to test your infection() function first, before proceeding to infector().  
  
Test your implementation on at least two files. You can use your previous lab solutions as input. Use the command **chmod u+wx {filename}** to give user write/execute permissions.

Submission
----------

Task 1 and Task 2 (without -a option) are mandatory for this lab. You can complete the -a option in task 2 later on in the completion lab.  
You are required to submit a zip file named \[your id\].zip that contains the following:

\+ task1

\- start.s

\- makefile

\+ task2

\- main.c

\- start.s

\- makefile
