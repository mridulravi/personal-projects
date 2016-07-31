 
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.File;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.FileWriter;
 
public class lab01 {
 
  public static void main(String[] args) {
 
	lab01 obj = new lab01();
	obj.run();
 
  }
 
  public void run() {
 
	String csvFile1 = "movieinfo.csv";
	BufferedReader br1 = null;
	String line = "";
	String cvsSplitBy = ":";
	String s;


	String csvFile2 = "movieratings.csv";
	BufferedReader br2 = null;
	String line2 = "";
 

        Scanner in = new Scanner(System.in);
 
        System.out.println("Enter a query:");
        s = in.nextLine();
	while (!s.equals("q0")) {
	char a_char = s.charAt(0);
	char b_char = s.charAt(1);
 	if( a_char == 'q') { 


  	if ( b_char == '1') {
		int endIndex = s.length();
		int startIndex = s.indexOf(" ");
		String modified_s = s.substring(startIndex + 1, endIndex);

	try {
 
		br1 = new BufferedReader(new FileReader(csvFile1));
		while ((line = br1.readLine()) != null) {
 
			String[] country = line.split(cvsSplitBy);
 			if ( country[0].equals(modified_s))
			{
			System.out.println(country[1]);
			}
 
		}
 
	} catch (FileNotFoundException e) {
		e.printStackTrace();
	} catch (IOException e) {
		e.printStackTrace();
	} finally {
		if (br1 != null) {
			try {
				br1.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
 
  }



  	else if ( b_char == '2') {
		int endIndex = s.length();
		int startIndex = s.indexOf(" ");
		String modified_s = s.substring(startIndex + 1, endIndex);
	try {
 
		br1 = new BufferedReader(new FileReader(csvFile1));
		while ((line = br1.readLine()) != null) {
 
			String[] country = line.split(cvsSplitBy);
			String[] actorsArray = country[4].split(",");
			for (int i = 0; i < actorsArray.length; i++) {
    			actorsArray[i] = actorsArray[i].trim();

			if (actorsArray[i].equals(modified_s))
				{ System.out.println(country[0]); }
			}
 
		}
 
	} catch (FileNotFoundException e) {
		e.printStackTrace();
	} catch (IOException e) {
		e.printStackTrace();
	} finally {
		if (br1 != null) {
			try {
				br1.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
 
  }



  	else if ( b_char == '3') {
		float max = 0;
		String ans = "";
		int endIndex = s.length();
		int startIndex = s.indexOf(" ");
		String modified_s = s.substring(startIndex + 1, endIndex);
		
	try {
 
		br1 = new BufferedReader(new FileReader(csvFile1));
		while ((line = br1.readLine()) != null) {
 
			String[] country = line.split(cvsSplitBy);
 			if ( country[2].equals(modified_s))
			{
				try {
 
					br2 = new BufferedReader(new FileReader(csvFile2));
					while ((line2 = br2.readLine()) != null) {
 
						String[] country2 = line2.split(cvsSplitBy);
 						if ( country2[0].equals(country[0]))
						{
						if ( Float.parseFloat(country2[1]) > max)
							{ max = Float.parseFloat(country2[1]);
							ans = country2[0];}
						}
					}
 					
				} catch (FileNotFoundException e) {
				e.printStackTrace();
				} catch (IOException e) {
				e.printStackTrace();
				} finally {
					if (br2 != null) {
						try {
							br2.close();
						} catch (IOException e) {
							e.printStackTrace();
						}
					}
				}
				
			}
 			
		}
 
	} catch (FileNotFoundException e) {
		e.printStackTrace();
	} catch (IOException e) {
		e.printStackTrace();
	} finally {
		if (br1 != null) {
			try {
				br1.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	System.out.println(ans);
  }





  	else if ( b_char == '4') {
		int flag = 0;
		String movieName;
	        System.out.println("Enter movie name:");
        	movieName = in.nextLine();
		String directorName;
	        System.out.println("Enter director name:");
        	directorName = in.nextLine();
		String releaseYear;
	        System.out.println("Enter year of release:");
        	releaseYear = in.nextLine();
		String genre;
	        System.out.println("Enter movie genre:");
        	genre = in.nextLine();
		String actorNames;
	        System.out.println("Enter actor names(separated by commas):");
        	actorNames = in.nextLine();
		String movieRating;
	        System.out.println("Enter movie rating:");
        	movieRating = in.nextLine();
		//int endIndex = s.length();
		//int startIndex = s.indexOf(" ");
		//String modified_s = s.substring(startIndex + 1, endIndex);
	try {
 
		br1 = new BufferedReader(new FileReader(csvFile1));
		while ((line = br1.readLine()) != null) {
 
			String[] country = line.split(cvsSplitBy);
 			if ( country[0].equals(movieName))
			{
			flag = 1;
			System.out.println("Movie already exists in the database");
			}
		}
		if (flag == 0) {
			FileWriter writer = new FileWriter("movieinfo.csv",true);
	    		writer.append(movieName);
	    		writer.append(':');
	    		writer.append(directorName);
	    		writer.append(':');
	    		writer.append(releaseYear);
	    		writer.append(':');
	    		writer.append(genre);
	    		writer.append(':');
	    		writer.append(actorNames);
			writer.append('\n');
	       	 	writer.flush();
	       	 	writer.close();
			FileWriter ratingsWriter = new FileWriter("movieratings.csv",true);
	    		ratingsWriter.append(movieName);
	    		ratingsWriter.append(':');
	    		ratingsWriter.append(movieRating);
			ratingsWriter.append('\n');
	       	 	ratingsWriter.flush();
	       	 	ratingsWriter.close();
			System.out.println("Movie added to the database");
		}
 
	} catch (FileNotFoundException e) {
		e.printStackTrace();
	} catch (IOException e) {
		e.printStackTrace();
	} finally {
		if (br1 != null) {
			try {
				br1.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
 
  }




  	else if ( b_char == '5') {
		int flag5 = 0;
		int flag6 = 0;
		int endIndex = s.length();
		int startIndex = s.indexOf(" ");
		String modified_s = s.substring(startIndex + 1, endIndex);
		File inFile = new File("movieinfo.csv");
		File ratingsInFile = new File("movieratings.csv");

	try {
 		//Construct the new file that will later be renamed to the original filename.
  		File tempFile = new File("movieinfo" + ".tmp");
		PrintWriter pw = new PrintWriter(new FileWriter(tempFile));

  		File ratingsTempFile = new File("movieratings" + ".tmp");
		PrintWriter ratingspw = new PrintWriter(new FileWriter(ratingsTempFile));

		br1 = new BufferedReader(new FileReader(csvFile1));
		while ((line = br1.readLine()) != null) {
 
			String[] country = line.split(cvsSplitBy);
 			if ( !country[0].equals(modified_s))
			{
			pw.println(line);
			pw.flush();
			}

			else 
			flag5 = 1;
 			
		}
		pw.close();

		br2 = new BufferedReader(new FileReader(csvFile2));
		while ((line2 = br2.readLine()) != null) {
 
			String[] movie = line2.split(cvsSplitBy);
 			if ( !movie[0].equals(modified_s))
			{
			ratingspw.println(line2);
			ratingspw.flush();
			}

			else 
			flag6 = 1;
 			
		}
		ratingspw.close();


		//Delete the original file
  		if (!inFile.delete()) {
    			System.out.println("Could not delete file");
    			return;
  		}

  		//Rename the new file to the filename the original file had.
  		if (!tempFile.renameTo(inFile)) {
    			System.out.println("Could not rename file");
			return;
		}


		//Delete the original file
  		if (!ratingsInFile.delete()) {
    			System.out.println("Could not delete file");
    			return;
  		}

  		//Rename the new file to the filename the original file had.
  		if (!ratingsTempFile.renameTo(ratingsInFile)) {
    			System.out.println("Could not rename file");
			return;
		}


		if (flag5 == 1) 
			System.out.println("Movie deleted from the info database");
		if (flag5 == 0)
			System.out.println("Movie does not exist in the info database");

		if (flag6 == 1) 
			System.out.println("Movie deleted from the ratings database");
		if (flag6 == 0)
			System.out.println("Movie does not exist in the ratings database");

	} catch (FileNotFoundException e) {
		e.printStackTrace();
	} catch (IOException e) {
		e.printStackTrace();
	} finally {
		if (br1 != null) {
			try {
				br1.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
 
  }


  	else if ( b_char == '6') {
		int flag5 = 0;
		int endIndex = s.length();
		int startIndex = s.indexOf(" ");
		String modified_s = s.substring(startIndex + 1, endIndex);
		String change;
		File inFile = new File("movieinfo.csv");
		File ratingsInFile = new File("movieratings.csv");

	try {
 		//Construct the new file that will later be renamed to the original filename.
  		File tempFile = new File("movieinfo" + ".tmp");
		PrintWriter pw = new PrintWriter(new FileWriter(tempFile));

		br1 = new BufferedReader(new FileReader(csvFile1));
		while ((line = br1.readLine()) != null) {
 
			String[] country = line.split(cvsSplitBy);
 			if ( country[0].equals(modified_s))
			{
			flag5 = 1;
			System.out.println("To change information about the movie - " + modified_s + ". Enter commands:");
			System.out.println("c1 <Director name>");
			System.out.println("c2 <Year of release>");
			System.out.println("c3 <Genre>");
			System.out.println("c4 <Actor names seprated by commas>");
			System.out.println("c5 <Movie rating>");
			change = in.nextLine();
			int changeEndIndex = change.length();
			int changeStartIndex = change.indexOf(" ");
			String modified_change = change.substring(changeStartIndex + 1, changeEndIndex);
			String command = change.substring(0, changeStartIndex);
				if ( command.equals("c1"))
				{
				pw.println(country[0] +":"+ modified_change + ":" + country[2] + ":" + country[3] +":" + country[4] );
				pw.flush();
				}
				else if ( command.equals("c2"))
				{
				pw.println(country[0] +":"+ country[1] + ":" + modified_change + ":" + country[3] +":" + country[4] );
				pw.flush();
				}
				else if ( command.equals("c3"))
				{
				pw.println(country[0] +":"+ country[1] + ":" + country[2] + ":" + modified_change +":" + country[4] );
				pw.flush();
				}
				else if ( command.equals("c4"))
				{
				pw.println(country[0] +":"+ country[1] + ":" + country[2] + ":" + country[3] +":" + modified_change );
				pw.flush();
				}
				else if ( command.equals("c5"))
				{
					pw.println(line);
					pw.flush();
  					File ratingsTempFile = new File("movieratings" + ".tmp");
					PrintWriter ratingspw = new PrintWriter(new FileWriter(ratingsTempFile));
					br2 = new BufferedReader(new FileReader(csvFile2));
					while ((line2 = br2.readLine()) != null) {
 
						String[] movie = line2.split(cvsSplitBy);
 						if ( movie[0].equals(modified_s))
						{
						ratingspw.println(movie[0] +":"+ modified_change);
						ratingspw.flush();
						}

						else 
						{
						ratingspw.println(line2);
						ratingspw.flush();
						}
 			
					}
					ratingspw.close();

					//Delete the original file
  					if (!ratingsInFile.delete()) {
    						System.out.println("Could not delete file");
    						return;
  					}

  					//Rename the new file to the filename the original file had.
  					if (!ratingsTempFile.renameTo(ratingsInFile)) {
    						System.out.println("Could not rename file");
						return;
					}

				}
				else
				{
				System.out.println("Wrong Input");
				pw.println(line);
				pw.flush();
				}
			
			}

			else 
			{
			pw.println(line);
			pw.flush();
			}
 			
		}
		pw.close();


		//Delete the original file
  		if (!inFile.delete()) {
    			System.out.println("Could not delete file");
    			return;
  		}

  		//Rename the new file to the filename the original file had.
  		if (!tempFile.renameTo(inFile)) {
    			System.out.println("Could not rename file");
			return;
		}


		if (flag5 == 1) 
			System.out.println("Movie information edited in the database");
		if (flag5 == 0)
			System.out.println("Movie name does not exist in the database");


	} catch (FileNotFoundException e) {
		e.printStackTrace();
	} catch (IOException e) {
		e.printStackTrace();
	} finally {
		if (br1 != null) {
			try {
				br1.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
 
  }



	else { System.out.println("Wrong query : You can only enter q1 q2 q3 q4 q5 or q0"); } }
	else { System.out.println("Wrong input"); } 
	System.out.println("Enter another query(q0 to exit):");
	s = in.nextLine();

}
}		
}
