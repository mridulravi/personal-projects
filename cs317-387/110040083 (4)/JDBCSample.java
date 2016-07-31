import java.io.*;
import java.sql.*;
import java.util.*;


public class JDBCSample {
        public static void main(String[] args) throws IOException{

		//Load the PostgreSQL JDBC driver class
                try{
                    Class.forName("org.postgresql.Driver");
                } catch (ClassNotFoundException cnfe){
                    System.out.println("Could not find the JDBC driver!");
                    System.exit(1);
                }
	        
		//Enter the connection details
		String hostname = "10.105.1.51";	// If PostgreSQL is running on some other machine enter the IP address of the machine here
		String username = "cs110040083"; // Enter your PostgreSQL username
		String password = "380040011"; // Enter your PostgreSQL password
		String dbName = "cs110040083"; // Enter the name of the database that has the university tables.
		String connectionUrl = "jdbc:postgresql://" + hostname +  "/" + dbName;
		Connection conn = null;

		//Connect to the database
                try {
                    conn = DriverManager.getConnection(connectionUrl,username, password);
                    System.out.println("Connected successfullly");
                } catch (SQLException sqle) {
                       System.out.println("Connection failed");
		       System.out.println(sqle);
		       // Uncomment the below line for a more detailed stack trace
		       // sqle.printStackTrace();
                       System.exit(1);
                }
                
                
////////////////////////////////////////////////////////////////////////////////////////////             
                
		/**********PART -1 BEGINS HERE**********/
		
//////////////////////////////////////////////////////////////////////////////////////////// 

 		System.out.println("PART - 1 ");

                double firstTimeNormal = System.currentTimeMillis();

		//Execute the query and print the results
		try {
                    Statement createTable = conn.createStatement();
                    createTable.execute("DROP TABLE IF EXISTS Castings;");
                    createTable.execute("DROP TABLE IF EXISTS MovieAwards;");
                    createTable.execute("DROP TABLE IF EXISTS Movies;");
                    createTable.execute("DROP TABLE IF EXISTS MoviePersons;");
                    createTable.execute("create table MoviePersons (Name varchar(100) PRIMARY KEY, Address varchar(100), PhoneNumber varchar(100), emailid varchar(100));");
                    createTable.execute("create table Movies (MovieName varchar(100) PRIMARY KEY, YearofRelease varchar(5), Producer varchar(100) REFERENCES MoviePersons(Name), Director varchar(100) REFERENCES MoviePersons(Name));");
                    createTable.execute("create table MovieAwards (AwardMovieName varchar(100) REFERENCES Movies(MovieName), YearofAward varchar(5), AwardName varchar(100));");
                    createTable.execute("create table Castings (CastingsMovieName varchar(100) REFERENCES Movies(MovieName), Actor varchar(100) REFERENCES MoviePersons(Name));");
                    
                    	Statement insertIntoTable = conn.createStatement();
                    	String csvFile = "Movies.csv";
			String csvFile1 = "MoviePersons.csv";
			String csvFile2 = "MovieAwards.csv";
			String csvFile3 = "Casting.csv";
			BufferedReader br = null;
			String line = "";
			String cvsSplitBy = ",";
			String insertionQuery = "";
			
			try{
			
				br = new BufferedReader(new FileReader(csvFile1));
				while ((line = br.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
				insertionQuery = "";
				insertionQuery = insertionQuery.concat("insert into MoviePersons values('");
	    			insertionQuery = insertionQuery.concat(country[0]);
	    			insertionQuery = insertionQuery.concat("', '");
	    			insertionQuery = insertionQuery.concat(country[1]);
	    			insertionQuery = insertionQuery.concat("', '");
	    			insertionQuery = insertionQuery.concat(country[2]);
	    			insertionQuery = insertionQuery.concat("', '");
	    			insertionQuery = insertionQuery.concat(country[3]);
	    			insertionQuery = insertionQuery.concat("' );");
				insertIntoTable.executeUpdate(insertionQuery);
 
				}
				
				insertionQuery = "";
				br = new BufferedReader(new FileReader(csvFile));
				while ((line = br.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
				insertionQuery = "";
				insertionQuery = insertionQuery.concat("insert into Movies values('");
	    			insertionQuery = insertionQuery.concat(country[0]);
	    			insertionQuery = insertionQuery.concat("', '");
	    			insertionQuery = insertionQuery.concat(country[1]);
	    			insertionQuery = insertionQuery.concat("', '");
	    			insertionQuery = insertionQuery.concat(country[2]);
	    			insertionQuery = insertionQuery.concat("', '");
	    			insertionQuery = insertionQuery.concat(country[3]);
	    			insertionQuery = insertionQuery.concat("' );");
 				insertIntoTable.executeUpdate(insertionQuery);
 
				}
				
				
				insertionQuery = "";
				br = new BufferedReader(new FileReader(csvFile2));
				while ((line = br.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
				insertionQuery = "";
				insertionQuery = insertionQuery.concat("insert into MovieAwards values('");
	    			insertionQuery = insertionQuery.concat(country[0]);
	    			insertionQuery = insertionQuery.concat("', '");
	    			insertionQuery = insertionQuery.concat(country[1]);
	    			insertionQuery = insertionQuery.concat("', '");
	    			insertionQuery = insertionQuery.concat(country[2]);
	    			insertionQuery = insertionQuery.concat("' );");
 				insertIntoTable.executeUpdate(insertionQuery);
 
				}
				

				insertionQuery = "";
				br = new BufferedReader(new FileReader(csvFile3));
				while ((line = br.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
				insertionQuery = "";
				insertionQuery = insertionQuery.concat("insert into Castings values('");
	    			insertionQuery = insertionQuery.concat(country[0]);
	    			insertionQuery = insertionQuery.concat("', '");
	    			insertionQuery = insertionQuery.concat(country[1]);
	    			insertionQuery = insertionQuery.concat("' );");
 				insertIntoTable.executeUpdate(insertionQuery);
 
				}
				
								
			
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			} finally {
				if (br != null) {
					try {
						br.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}	

                } catch (SQLException sqle) {
                       System.out.println(sqle);
                       System.exit(1);
                }
                
                double secondTimeNormal = System.currentTimeMillis();
                System.out.println("Time for Simple Statement : ");
                System.out.println((secondTimeNormal - firstTimeNormal)/1000.0);
                
                
                
                
                try {
                        Statement deleteTable = conn.createStatement();
                        deleteTable.execute("delete from Castings;");
                        deleteTable.execute("delete from MovieAwards;");
                        deleteTable.execute("delete from Movies;");
                        deleteTable.execute("delete from MoviePersons;");
                        
                        
                	PreparedStatement pstate;
                   	String csvFile = "Movies.csv";
			String csvFile1 = "MoviePersons.csv";
			String csvFile2 = "MovieAwards.csv";
			String csvFile3 = "Casting.csv";
			BufferedReader br = null;
			String line = "";
			String cvsSplitBy = ",";
			
			try{
				pstate = conn.prepareStatement("insert into MoviePersons values(?,?,?,?);");
				br = new BufferedReader(new FileReader(csvFile1));
				while ((line = br.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
				pstate.setString(1, country[0]);
				pstate.setString(2, country[1]);
				pstate.setString(3, country[2]);
				pstate.setString(4, country[3]);
				pstate.execute();
				
				}
				
				pstate = conn.prepareStatement("insert into Movies values(?,?,?,?);");
				br = new BufferedReader(new FileReader(csvFile));
				while ((line = br.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
				pstate.setString(1, country[0]);
				pstate.setString(2, country[1]);
				pstate.setString(3, country[2]);
				pstate.setString(4, country[3]);
				pstate.execute();
				
				}
				
				pstate = conn.prepareStatement("insert into MovieAwards values(?,?,?);");
				br = new BufferedReader(new FileReader(csvFile2));
				while ((line = br.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
				pstate.setString(1, country[0]);
				pstate.setString(2, country[1]);
				pstate.setString(3, country[2]);
				pstate.execute();
				
				}
				
				pstate = conn.prepareStatement("insert into Castings values(?,?);");
				br = new BufferedReader(new FileReader(csvFile3));
				while ((line = br.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
				pstate.setString(1, country[0]);
				pstate.setString(2, country[1]);
				pstate.execute();
				
				}
				
			} catch (IOException e) {
				e.printStackTrace();
			} finally {
				if (br != null) {
					try {
						br.close();
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}		
		
                
                } catch (SQLException sqle) {
                       System.out.println(sqle);
                       System.exit(1);
                }
                
                double thirdTimePrepared = System.currentTimeMillis();
                System.out.println("Time for Prepared Statement : ");
                System.out.println((thirdTimePrepared - secondTimeNormal)/1000);
                
                
////////////////////////////////////////////////////////////////////////////////////////////             
                
		/**********PART -2 BEGINS HERE**********/
		
//////////////////////////////////////////////////////////////////////////////////////////// 

 		System.out.println("PART - 2 ");

		try {
	            int flag = 0;
                    BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		    System.out.println("Enter a Movie name:");
                    String movieName = br.readLine();
                    BufferedReader br1=new BufferedReader(new InputStreamReader(System.in));
		    System.out.println("Enter year of release:");
                    String yor = br.readLine();
                    BufferedReader br2=new BufferedReader(new InputStreamReader(System.in));
		    System.out.println("Enter a Producer name:");
                    String prodName = br.readLine();
                    BufferedReader br3=new BufferedReader(new InputStreamReader(System.in));
		    System.out.println("Enter a Director name:");
                    String dirName = br.readLine();

                    Statement query=conn.createStatement();
                    //pstmt.setString(1, deptName);
                    ResultSet rs = query.executeQuery("SELECT * FROM Movies WHERE MovieName = '" + movieName + "';");
                    
                    
                    /*String s;
      		    Scanner in = new Scanner(System.in);
                    System.out.println("Enter a string");
                    s = in.nextLine();
                    Statement createTable = conn.createStatement();*/


                    while(rs.next()){
                            //String name = rs.getString("moviename");
                            //System.out.println(name);
                            System.out.println("Movie already exists in the database. Updating the info about the movie.");
                            flag=1;
                    }
                    
                    if(flag == 0) {
                    
                    Statement check1=conn.createStatement();
                    ResultSet checkrs1 = check1.executeQuery("SELECT * FROM MoviePersons WHERE Name = '" + prodName + "';");
                    if(!checkrs1.next()) {
                    Statement insertProd=conn.createStatement();
                    insertProd.execute("INSERT INTO MoviePersons VALUES('" + prodName + "',NULL,NULL,NULL);");
                    }
                    
                    Statement check2=conn.createStatement();
                    ResultSet checkrs2 = check2.executeQuery("SELECT * FROM MoviePersons WHERE Name = '" + dirName + "';");
                    if(!checkrs2.next()) {
                    Statement insertDir=conn.createStatement();
                    insertDir.execute("INSERT INTO MoviePersons VALUES('" + dirName + "',NULL,NULL,NULL);");
                    }                    
                    
                    Statement insert=conn.createStatement();
                    insert.execute("INSERT INTO Movies VALUES('" + movieName + "'," + yor  + ", '"+ prodName +"', '"+ dirName +"');");
                    }
                    
                    else if (flag == 1) {
                    
                    
                    Statement check1=conn.createStatement();
                    ResultSet checkrs1 = check1.executeQuery("SELECT * FROM MoviePersons WHERE Name = '" + prodName + "';");
                    if(!checkrs1.next()) {
                    Statement insertProd=conn.createStatement();
                    insertProd.execute("INSERT INTO MoviePersons VALUES('" + prodName + "',NULL,NULL,NULL);");
                    }
                    
                    Statement check2=conn.createStatement();
                    ResultSet checkrs2 = check2.executeQuery("SELECT * FROM MoviePersons WHERE Name = '" + dirName + "';");
                    if(!checkrs2.next()) {
                    Statement insertDir=conn.createStatement();
                    insertDir.execute("INSERT INTO MoviePersons VALUES('" + dirName + "',NULL,NULL,NULL);");
                    }                    
                    
                    
                    Statement update=conn.createStatement();
                    update.execute("UPDATE Movies SET YearofRelease = "+ yor +", Producer = '"+ prodName +"', Director='"+ dirName +"' WHERE MovieName='" + movieName + "'; ");
                    }

                } catch (SQLException sqle) {
                       System.out.println(sqle);
                       System.exit(1);
                }  
                
////////////////////////////////////////////////////////////////////////////////////////////             
                
		/**********PART -3 BEGINS HERE**********/
		
//////////////////////////////////////////////////////////////////////////////////////////// 

 		System.out.println("PART - 3 ");

		try {
                    BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		    System.out.println("Enter the query:");
                    String query = br.readLine();
                    PreparedStatement pstate = conn.prepareStatement(query);
                    String findStr = "?";
		    int lastIndex = 0;
		    int count =0;
                    
                    String[] parameters;
                    
		    while(lastIndex != -1){

       			lastIndex = query.indexOf(findStr,lastIndex);

       			if( lastIndex != -1){
             		count ++;
            		lastIndex+=findStr.length();
      			}
		    }
		    
		    
		    Scanner in = new Scanner(System.in);
		    
		    for (int i = 1 ; i <= count ; i++) {
		    	pstate.setString(i, in.nextLine());
		    }

	    	    ResultSet FinalResult = pstate.executeQuery();
	    	    ResultSetMetaData resultsMetaData = FinalResult.getMetaData();
			int columnCount = resultsMetaData.getColumnCount();
			System.out.println("	");
			
			for(int i=1; i<columnCount+1; i++) {
				System.out.print("	" + resultsMetaData.getColumnName(i));
			}
			System.out.println();
			
			while(FinalResult.next()) {
				System.out.println("	");
				for(int i=1; i<columnCount+1; i++) {
				System.out.print("	" + FinalResult.getString(i));
				}
					
			System.out.println();
			}



                } catch (SQLException sqle) {
                       System.out.println(sqle);
                       System.exit(1);
                }

                
        }
}
