# Simple Shell

### Shell

The Shell is a program that allows a user to interact with the computers operating system to perform a specific task.

### Building your own shell

Building a shell requires a few basic concepts:

	* PID and PPID
	* Command line arguments
	* Executing a program
	* Creating Processes
	* Suspending Processes
	* File information
	* Environments

Understanding these concepts will allow us to better understand how a shell works and how to build one of our own.

### PID & PPID | getpid() && getppid()

For every instance that a program is executed, a unique ID is given to that process and that ID / value is stored on the processes table. This PID (process ID) is used many functions and system calls and can allow the user to manipulate other processes.

It's important to note that for every process there is a parent process that allows the execution of that initial process. In other words, in order to be able to execute a program, there needs to be a program to execute it and that would be the parent.

An example of this would be executing a program through the shell. The shell is a program that can allow you to execute another program, be it one that have created or not. The shell would technically be there parent, and the executed program (the process) would be the child.

In order to obtain a PID or a PPID (parent process ID) these steps can be followed:

syntax:

	#include <unistd.h>	<--- the header file where the functions are help

	int main(void)
	{
		pid_t pid, ppid;

		pid = getpid();
		ppid = getppid();

		printf("current ID: %d, parent ID: %d\n", pid, ppid);

		return (0);
	}

	pid_t:		this data type is defined in the library, an int that can hold the value of a pid /ppid
	getpid():	This function returns the current process ID
	getppid();	This function returns the parent process ID

If this program was executed two different integers / ID's 'would be printed to the screen. If the command "echo $$" was typed in the terminal, you'd notice that the id would match the parent ID the program returned.

### Command line arguments | argc && argv

Command line arguments are arguments that are passed to and accepted by a program to perform a certain task. The command line arguments are usually set as parameters for the main function of a program.
	
	* argc
	* argv

Argc is the argument counter and is represented by an integer that gives us the total number of arguments being passed to the program (this number includes the program in the count).

Argv is the argument vector and represent an array of character strings that is null-terminated. These represent the arguments that are being passed to the program. By doing pointer arithmetic, a user can access these strings.

Syntax:

	int main(int argc, char *argv[])
	{
		//code goes here
	}

Once the source code is compiled, the user can type the programs name / executable file and the arguments to be passed to it.

Example:

	./a.out arugemts passed		<--- two arguments passed to the program

Here are a few extra functions that read input that will be helpful in building the shell.

	* getline()
	* strtok();

Syntax for getline()

	ssize_t getline(char **str, size_t *n, FILE *stream);

	ssize_t:	returns an int as low as -1
	**str:		a pointer to a array of char / string
	FILE *stream:	The input as to where getline will be reading the line from

getline() reads an entire line from stream, and stores that data in the address of a char pointer. This pointer / buffer is null-terminated and it includes a NEWLINE if one was found. The newline is very important to take note of.

When getline() reads the string and allocates memory to it if "\*\*str" == NULL and 'n' == 0 before the call. It's also good to note that if the buffer is not large enough, getline reallocates memory to the buffer.

Always remember when dealing with allocating of memory it is important to free it.

On success getline() returns the number of char printed including the delimiter, excluding the null-terminating byte. On failure, -1 is returned.

Example of getline():

	#include <stdlib.h> 	<---- creating and freeing memory
	#include <stdio.h>

	int main(void)
	{
	 	ssize_t i = 0;
		char *str = NULL;

		i = getline(&str, &i, stdin);
		if (i == -1)
			perror("Error");
		printf("%s\n",str);
		free(str);

		return (0);
	}


	getline():	The function retriving the line from source
	&str:		we are initailizing the pointer we declared with the string we are reading
	&i:		this will be the length of the string
	stdin:		The stream we are reading from stdin(0) POSIX STDIN_FILENO

A reminder that getline() reads input from the stdin through it's parameters. This means that argv and Argc is not used.

strtok() is a function that breaks down a string into sections of 0 - more nonempty tokens. These sections are determined by the delimiter that is passed to the function.

Syntax of strtok():

	char *strtok(char *str, const chat *delimiter);
	
	*str:		a pointer to a string that we will break down
	*delimiter:	a pointer to a delimter that will determine where he will seperate the tokens.

When the first instance of calling the strtok() function "str" should be passed and so would the pointer holding the delimiter, this will give us the first token from the string. However, in order to continue creating tokens from the same string, for every instance after the first call NULL will be the first parameter instead of "str". The function will understand that this is the same string that is being passed to it and will continue the tokenisation of the string until the condition that was set is met.

Example:

	#include <string.h>

	int main(void)
	{
		char string[] = "this is a string";
		char *token;
		char *delim = " ";

		token = strtok(strnig, delim);
		while (token != NULL)
		{
			printf("%s ", token);
			token = strtok(NULL, delim);
		}
		printf("\n");
		return (0);
	}

This example shows a string being broken down into tokens, and each token was printed to the screen. The first call to strtok() was outside of the loop as the pointer "token" was not yet initialized so its value is NULL.

Once the loop started, the token variable kept being reinitialized until the value that was returned was null, thus ending the loop.


### Executing programs | execve()

The system call execve() allows a user to execute a program within another program, once this function is called the code and memory associated with program that called execve() would be truncated and replaced by the new program. The process ID remains unchanged.

execve() does not return anything on success, but if it fails -1 is returned so setting up an if statement to manage this error is important (remember that our code should always manage errors).

The execve() takes in 3 parameters:

	int execve(const char *filename, char *const argv[], char *const envp[]);

		*filename:	This is the path to where the file / command is located (argv[0])
		argv[]:		contains the filename / arugments and a NULL at the end (full command line arugment)


Syntax:

	#include <unistd.h>

	int main()
	{
		int i = 0;
		char *argv[] = {"/usr/bin/ls", "-l", NULL};	<---- note that it's a NULL terminated array of pointers.

		i = execve(argv[0], argv, NULL);
		
		if (i == -1)
			perror("Error");

		printf("This wont be printed as the code would be replaced by the new program");
		return (0);
	}

	/usr/bin/ls:		this is the path of the file that would be exected
	argv: 			the full command line arugment

The output of this command would be the ls -l command.

I find that the common mistake is forgetting about the NULL terminated array of pointers. This will effect the execution of the program if your are accepting user input through getline(). When using the strtok() function to store tokens in an array, when you reach the end of the pointer array increment the array one last time and add the extra NULL pointer.

### Creating process | fork()

The fork() function allows the user to branch off and create a new process within the current process. The means it clones the process from where it was called, thus creating a child process.

On success, the child process ID is returned to the parent process and the value of '0' is given to the child. On failure, no process ID is created and -1 is returned. Always remember to handle these errors. 

Syntax:

	#include <unistd.h>

	int main()
	{
		int i = 0;

		printf("Hello\n");
		i = fork();
		if (i = -1)
			return (-1);
		printf("World\n");

		return (0);
	}

This will result on the word "hello" being printed and the word "world" printed twice.

There are a few situations that can happen when calling the fork function: either the child terminated before the parent (this this is known as a zombie process); or the parents terminated before the child process (this is called an orphan process).

Zombie process:

The zombie process is when a child process terminates before the parent does, this means that the memory associated with the child process is not cleared and a memory leak is possible. The process table only has a finite amount of space on the RAM where it can record processes and if zombie processes are not freed it runs the risk of filling up the table which  means no new processes can occur. It is always important to make sure that the child terminates before the parent. To insure this a wait() function is used.

You'll notice that during the execution of a program that holds a zombie process, the terminal executes the program and then returns the shell to indicate that it is ready for more commands, but is then followed by the execution of the child process.

example:

using the fork example above after execution.

	hello
	world
	linux:~$ world

The proper output would be:

	hello
	world
	world
	linix:~$ 

Orphan process:

The orphan process happens when the parent process terminates before the child does, this causes the value of the child PID becomes 1 and is adopted by the init process (parent of all processes, its PID is actually 1), and the child process is removed from the process table after execution.

### Suspending processes | wait()

To prevent a Zombie process from occurring we can use the wait() function to insure that the parent function only executes after the child process has changed it's state.

The wait() function waits for either: the child process to terminate; or the child was stopped by a signal; or the child was resumed by a signal.

It would be logical to use the wait() function within the parent process to ensure that the child terminates first.

Example:

	#include <sys/wait.h>

	int main()
	{
		int i = 0;

		i = fork();
		if (i == -1)
			return (-1);
		if (i == 0)
		{
			sleep(2);
			printf("hello ");
		}
		else
		{
			wait(NULL);
			printf("World!\n");
		}

		return (0);
	}

### File information | stat()

The stat() function allows a user to see the metadata / inode of a file. This means that data such as: the owner of the file / file permissions; the last time the file was opened; the last time it was modified, etc. The actually content of the file and the filename is not accessible through stat().

On success stat() returns 0, else it -1 on failure.

synatx:

	int stat(const char *pathname, struct stat *info);

	*pathanem: 	This the the pathname of the file you want to access
	*info:		this is a pointer to a structure where the functon will be able to store and access information
	
Example:

	#include <sys/stat.h>

	struct stat *info
	int main()
	{
		int i = stat("/usr/bin/ls", &info);
		
		if (i != -1)
			printf("file size: %ld bytes\n", info.st_size);
	}
This example will print the size of the file we have passed to the stat() function. There is a list of struct data that can be accessed through the pointer we have declared by dereferencing it.

Here is the struct:

	struct stat {
    		dev_t st_dev;       // ID of device containing file
    		ino_t st_ino;       // inode number
    		mode_t st_mode;     // protection
		nlink_t st_nlink;    // number of hard links
    		uid_t st_uid;       // user ID of owner
    		gid_t st_gid;       // group ID of owner
    		dev_t st_rdev;      // device ID (if special file)
    		off_t st_size;      // total size, in bytes
    		blksize_t st_blksize; // blocksize for file system I/O
    		blkcnt_t st_blocks;  // number of 512B blocks allocated
    		time_t st_atime;     // time of last access
    		time_t st_mtime;     // time of last modification
    		time_t st_ctime;     // time of last status change
		};

So if a user would like to access the time the file was last accessed, "info.st_atime" would be used in the code with the relevant format specifier used.

### Environment

An environment is a list of variables that influence the behaviour of programs and how it interact with the software. This sets the kind of behaviour and interaction it has with other programs.

Each process comes with an environment, and every process created from it receives a copy of it's parents environment. There are a few ways a user can retrieve their environment: through the command-line or through coding.

command-line:

	$ printenv
	
	The printenv command allows a user so see the environment variables set

There are 3 ways a user can access the environment through their source code:

Source code:

	* main function's 3rd prototype
	* global variable environ
	* getenv() functon

* Main function

The main function can receive a 3rd parameter called "\*\*env". It's an argument that is a NULL terminated array of strings can be accessed through pointer arithmetic or assigning it to a pointer to a pointer of arrays.

syntax

	int main(int argc, char *argv[], char *env[])

OR

	int main(int argv, char **argv, char **env)

We can access the individual variables or all of them though a loop or though dereferencing.

Example:

	int main( int argc, char **argv, char **env)
	{
		for (i = 0; env[i] != NULL; i++)
			printf("%s\n", env[i]);
	}

The user can also use the global variable "environ" to access the environment variables. This acts very similar to the \*env[] parameter of the main functon, which in fact uses environ to access the environment variables.

	extern char **environ;

	int main()
	{
		int i = 0;

		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
	}

The last way to access the environment variables is through the getenv()f function. This function takes in the name of the variables the user wants to print and displays value.

On success it returns the string of data associated with the variable name, on failure it returns (null).

Example

	int main(void)
	{

		printf("%s\n", getenv("HOME"));
		printf("%s\n", getenv("PATH"));
		printf("%s\n", getenv("SHELL"));
	}

//end
