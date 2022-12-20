Introduction to C Programming in a Unix (Linux 32 bits) Environment
===================================================================

**Lab goals**:

*   C primer
*   Parsing command-line arguments
*   Undestanding character encoding (ASCII)
*   Implementing a debug mode for your program
*   Introduction to standard streams (stdin, stdout, stderr)
*   Simple stream IO library functions

(This lab is to be done SOLO)
=============================

Task 0: Maintaining a project using make
----------------------------------------

You should perform this task **before** attending the lab session. For this task, 3 files are provided: [add.s](https://moodle.bgu.ac.il/moodle/pluginfile.php/3648975/mod_resource/content/1/add.s), [main.c](https://moodle.bgu.ac.il/moodle/pluginfile.php/3649133/mod_resource/content/1/main.c), [numbers.c](https://moodle.bgu.ac.il/moodle/pluginfile.php/3649134/mod_resource/content/1/numbers.c).

The first file is assembly language code, and the other 2 are C source code.

1.  Log in to Linux.
2.  Decide on an ASCII text editor of your choice (vi, emacs, kate, pico, nano, femto, or whatever). It is **your responsibility** to know how to operate the text editor well enough for all tasks in all labs.
3.  Using the text editor that you decided to use, write a makefile for the given files (as explained in the introduction to GNU Make Manual, see the \[\[lab1/reading|Reading Material\]\]). The Makefile should provide targets for compiling the program and cleaning up the working directory.
4.  Compile the project by executing make in the console.
5.  Read all of lab1 reading material before attending the lab, and make sure you **understand** it. This may entail writing simple code to exercise the use of library functions and running it, in addition to any other task 0 code you are **required** to write.
6.  Read the puts(3) and printf(3) manuals. What is the difference between the functions? To read the manuals type man followed by the function name (e.g. `man puts`) in a "console".

### Important

To protect your files from being viewed or copied by other people, thereby possibly earning you a disciplinary hearing, employ the Linux permission system by running: `chmod 700 -R ~` In order to make sure you have sufficient space in your workspace, run the following command once you're logged in `du -a | sort -n` Then you can see a list of your files/directories and the amount of space each file/directory takes. If you need space and KNOW which files to remove, you can do that by: `rm -f [filename]`

### Control+D, Control+C and Control+Z

*   What does Control+D (^D) do?
*   What does Control+C (^C) do?
*   What does Control+Z (^Z) do?

Do not use Control+Z for terminating processes!!!

### Writing a simple program

Write a simple echo program named my\_echo:  

NAME

my\_echo - echoes text.

SYNOPSIS

my\_echo

DESCRIPTION

my\_echo prints out the text given in the command line by the user.

EXAMPLES

`#> my_echo aa b c`

`#> aa b c`

#### Mandatory requirements

*   Create a proper makefile as described in the reading material.
*   Test your program to see that it actually works...

Students coming with ready code "from home" will be assigned low priority **and** will have to demonstrate re-writing all the code again **from scratch**. Additionally, you are expected (of course) to understand your code completely.

### On this lab you can assume that the resulting encrypted char will always be in the range from 32 to 126 (inclusive).

Task 1: The encoder program
---------------------------

In this task we will write a program that encodes characters from the input text.  
As stated in task 0 and the reading material, you should already have consulted the man pages for **strncmp(3), fgetc(3), fputc(3), fopen(3), fclose(3)** before the lab.  
Task 1 consists of three subtasks: 1a, 1b, 1c and 1d, each building on top of the previous subtask. Therefore, your program for each task should contain all the features from the previous tasks.  
  

### Task 1a: A restricted encoder version - conversion to uppercase

The encoder program should be implemented as follows:  

NAME

encoder - encodes the input text as uppercase letters.

SYNOPSIS

encoder

DESCRIPTION

encoder reads the characters from standard input and prints the corresponding uppercase characters to the standard output. Non lowercase characters remain unchanged.

EXAMPLES

`#> encoder   Hi, my name is Noah   `

`#> HI, MY NAME IS NOAH`

`#> ^D`

`#>`

#### Information

*   stdin and stdout are FILE\* constants than can be used with fgetc and fputc.
*   Make sure you know how to recognize end of file ( _EOF_ ).
*   Control-D causes the Unix terminal driver to signal the EOF condition to the process running in this terminal foreground, using this key combination (shown in the above example as ^D) will cause _fgetc_ to return an _EOF_ constant and in response your program should terminate itself "normally".
*   Refer to [ASCII](http://www.asciitable.com/) table for more information on how to convert characters to lower-case or upper-case.

#### Mandatory requirements

*   You must read and process the input **character by character**, there is no need to store the characters you read at all.
*   Important - you cannot make any assumption about the line length.
*   Check whether a character is an lowercase letter by using a single "if" statement with two conditions. How?
*   You are **not** allowed to use any library function for the purpose of recognizing whether a character is a letter, and its case.

### Task 1b: Extending the encoder to support debug mode

As you develop a program, it is important to allow for easy debugging. The debug mode which you introduce here explains this idea. Using this scheme, any program can be run in a debug mode that allows special debugging features for testing the program. As a minimum, implemented here, when in debug mode the program prints out important information to stderr. Printing out the command-line parameters allows for easy detection of errors in retrieving them. Henceforth, code you write in most labs will also require adding a debug mode, and it is a good idea to have this option in **all** programs you write, even if **not required** to do so!

NAME

encoder - encodes the input text as hexadecimal values.

SYNOPSIS

encoder \[OPTION\]...

DESCRIPTION

encoder receives text characters from standard input and prints the corresponding uppercase charachters to the standard output.  
The debug mode is activated via command-line argument (-D).  
If the debug-mode is activated, print the command-line arguments to **stderr** and each character you recieve from the input (hexadecimal value) before and after the conversion.  
**regardless** of the debug-mode, the encoder will convert characters into uppercase.  

EXAMPLES

`#> encoder -D   -D   Hi, my name is Noah   48 48   69 49   2C 2C   20 20   60 40   79 59   20 20   6E 4E   61 41   6D 4D   65 45   20 20   69 49   73 53   20 20   4E 4E   6F 4F   61 41   68 48      HI, MY NAME IS NOAH   ^D   #>`*   Note: the left colomn is the hexadecimal representation of the **input** characters whereas the right colomn is the hexadecimal representation of the **modified** characters (in this case switched from lower-case to upper-case)

#### Mandatory requirements

*   You are **not** allowed to use any library function for the purpose of recognizing whether a character is a letter and its case.
*   Read your program parameters in the manner of task0 (main.c), first set default values to the variables holding the program configuration and then scan through _argv_ to update those values. Points will be reduced for failing to do so.

### Task 1c: Extending the encoder to support encryption

In this task, make sure you follow the output format precisely. Programs which deviate from the instructions will not be accepted! Please make your output is exactly as the examples bellow.

NAME

encoder - encodes the input text using encryption key.

SYNOPSIS

encoder \[OPTION\]...

DESCRIPTION

encoder receives characters from standard input and prints the corresponding encrypted characters to the standard output. The encryption key is given as a command-line argument.  
If **no** argument is supplied, the encoder converts characters into uppercase as before.  
The encryption key is of the following structure: +e{key}. The argument {key} stands for a sequence of digits whose value will be **added** to each input characters in sequence, in a **cyclic** manner.  
This means that each digit in sequence recieved by the encoder is added to the coresponding character in sequence in the key. When and if the end of the key is reached, re-start reading encoding digits from the begining of the key. You should support both addition and substruction, +e{key} is for addition and -e{key} is for substruction. On this task, you need to ignore the char '\\n' which means new line after you press ENTER.

EXAMPLES

`#> encoder +e12345   ABCDEF   BDFHJG   12#<   24&@   ^D   #> encoder -e4321   IVRM   ESPL   ^D`

Task 2:
-------

### Task 2a: Supporting input from a file

NAME

encoder - encoders the input text as uppercase or encrypted letters.

SYNOPSIS

encoder \[OPTION\]...

DESCRIPTION

encoder reads characters from standard input and prints the corresponding uppercase characters or encrypted characters (depending on whether the encryption key was given) to the standard output.  
If **no** encryption key argument is supplied, the encoder only converts upper-case characters into uppercase .  

OPTIONS

\-iFILE

Input file. Read list of characters to be encoded from a file, instead of from standard input.

ERRORS

If FILE cannot be opened for reading, print an error message to standard error and exit.

EXAMPLES

`#> echo 'IVRM' > input   #> encoder -e4321 -iinput   ESPL`

*   Notice that there is no seperation between the -i indicator and the file name (same as in the encryption key).

#### Mandatory requirements

*   Program arguments may arrive in an **arbitrary** order. Your program must support this feature.

### Task 2b: Supporting output to a file

NAME

encoder - encodes the input text as uppercase or encrypted letters.

SYNOPSIS

encoder \[OPTION\]...

DESCRIPTION

encoder reads ASCII text characters from standard input or from a file and prints the corresponding uppercase characters or encrypted characters (depending on whether the encryption key was given) to the standard output or the given file. The encryption key is given as an argument.  
If **no** encryption key argument is supplied, the encoder only converts lower-case characters into upper-case.  

OPTIONS

\-oFILENAME

Output file. Prints output to a file named FILENAME instead of the standard output.

EXAMPLES

`#> encoder -e4321 -ooutput   IVRM   ^D   #> more output   ESPL`

*   Notice that there is no seperation between the -o indicator and the file name (same as in the encryption key and the input file name).

  

### Deliverables:

Task 1 and task 2a must be completed during the regular lab. Task 2b may be done in a completion lab, but only if you run out of time during the regular lab. The deliverables must be submitted until the end of the day.  
You must submit source files for task1C, task2A and task2B in respective folders, and also a makefile that compiles them. The source files must be organized in the following tree structure (where '+' represents a folder and '-' represents a file):  
\+ task1C  
   - makfile  
   - encoder.c  
\+ task2A  
   - makefile  
   - encoder.c  
\+ task2B  
   - makefile  
   - encoder.c  

#### Submission instructions

*   Create a zip file with the relevant files (only).
*   Upload zip file to the submission system.
*   Download the zip file from the submission system and extract its content to an empty folder.
*   Compile and test the code to make sure that it still works.
