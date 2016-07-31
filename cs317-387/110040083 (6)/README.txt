Mridul Ravi Jain
110040083


USERS Table:

 username | password  |  role  
----------+-----------+--------
 reader   | reader123 | reader
 reader2  | reader234 | reader
 reader3  | reader345 | reader
 writer   | writer123 | writer
 writer2  | writer234 | writer
 writer3  | writer345 | writer


Instructions:

1. Extract the submitted file 110040083.tar.gz. It will be extracted to a folder named 110040083.
2. Folder 110040083 consists of 3 files : README.txt	assignment7-dbscript	ROOT.war
3. Now open terminal and type commands:

	cd 110040083
	psql -h 10.105.1.51 -p 5432 -U cs110040083 -W -f assignment7-dbscript
	(Now enter password 380040011)
	psql -h 10.105.1.51 -p 5432 -U cs110040083 -W
	(Now enter password 380040011)
	
4. Copy the ROOT.war file in  Tomcat's webapps folder.
5. The ROOT.war will automatically be extracted to a ROOT folder.
5. Now change directory to webapps/ROOT/WEB-INF/classes.
6. Type command:   javac -cp "/usr/share/tomcat7/lib/servlet-api.jar" First.java
7. Now change directory to Tomcat's bin folder and run the script by writing ./startup.sh.
8. Open your browser and type link :  localhost:8080/login.jsp
9. Enter Username and passwords as given above.

READER will be able to see interface for Quesry 1,2,3 only whereas WRITER can see interface for all 6 queries.

Q1: Query the details of a movie given it's name. It returns the movie details as well as the actors that acted in the 
movie. You will be directed to another page containing the result of your query. If movie doesnot exist in the DB, 
result will be empty lines. Press BACK button in the browser to return to previous page.

Q2: Query the set of awards given a movie name. You will be directed to another page containing the result of your 
query. If movie doesnot exist in the DB, result will be empty lines. Press BACK button in the browser to return to 
previous page.

Q3: Return the set of movies the actor acted in. If actor name doesnt exist in the DB, Result will be empty 
lines.Press BACK button in the browser to return to previous page.


Q4: Interface to add a new movie with all actor information. If any of these actors, producer or director etc. are not 
in the DB in MoviePersons we return an error. If movie already exists in the DB we return an error.

Q5. Interface to delete a movie (corresponding actors in Castings should also be deleted), if it exists.

Q6: Interface to add an award for a movie. No resrictions, two tuples can have the same value for all attributes.











	

