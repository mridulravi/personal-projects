Mridul Ravi Jain
110040083


Instructions: 
1. The tar consists of this README, JDBCSample.java file and 4 csv files.
2. Extract the postgresql-9.2-1002.jdbc4.jar(uploaded on moodle) in some directory.
3. Change current directory to postgresql-9.2-1002.jdbc4 directory.
4. Now put all the files submitted in postgresql-9.2-1002.jdbc4 directory.
5. In terminal type command: javac JDBCSample.java && java JDBCSample
6. A single program does everything.



Input-Output: 

If connected to database the program will output : "Connected Sucessfully" and then all 3-parts will be executed one by one.




PART-1:

In this part user doesn't have to give any input. The program will output the result from Simple as well as Prepared 
Statements one by one. This might take a few seconds as output is given in real time.

Schema is as follows: 
a) Movies (MovieName, YearofRelease, Producer, Director)
b) MoviePersons (Name, Address, Phone Number, emailid)
c) MovieAwards (AwardMovieName (foreign key into Movie), YearofAward, AwardName)
d) Castings (CastingsMovieName (foreign key into Movie), Actor (foreign key into MoviePerson))

PLEASE NOTE the attribute and table names carefully.





PART-2:

After PART-1 output is completely displayed on the screen, PART-2 will begin. User will be prompted to onput a movie name, year of 
release, producer name and director name one by one. It will insert if no movie with same name exists, else update the details.

If there is an update a message "Movie already exists in the database. Updating the info about the movie." will be displayed.
If there is an insert no such message is diaplayed and PART 3 begins.




PART-3:

In this part user will be prompted to insert a parameterized query in one line. 
After in writing the query, user will have to enter parameter values line by line.

Once this is done the output of the query will be diplayed and the program terminates.









