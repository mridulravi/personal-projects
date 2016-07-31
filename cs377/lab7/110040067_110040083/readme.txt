Abhishek Gupta		110040067
Mridul Ravi Jain	110040083

#########
The format for command files are as follows:
	The file names should be "file0", "file1", "file2", "file3"
	
	For receive instruction, just "receive" should be written in the test file
	For send instrucion, format will be
		send <rec_id> <msg>
		
	We have made 2 folders test_case1 and test_case2, which contains the files
	The executable must be in the same folder as the test files. So copy the test files from the folders to the directory where executable is present.
	
Compilation instructions:-
	compile using -pthread flag
	Eg:-
		g++ -pthread -o ipc ipc.cpp
		
##########

We have also implemented check for deadlock, if they arise. Deadlock may or may not arise with the same file, i.e., there are some cases where deadlock may depend on the scheduling order of the threads. We have attached a test case (test_case3 folder)which demonstrates the same. If you run it multiple times, then some times it will report that deadlock has arisen whereas sometimes deadlock will not arise.
