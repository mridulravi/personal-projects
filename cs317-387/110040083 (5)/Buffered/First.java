import java.io.*;
import java.util.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;

public class First extends HttpServlet  
  {

	List<String> slist = new ArrayList<String>();
	List<String> alist = new ArrayList<String>();
	List<String> blist = new ArrayList<String>();


    public void listinsert()	
	{
			slist.clear();
			alist.clear();
			blist.clear();
			BufferedReader br1 = null;
			String line = "";
			String cvsSplitBy = ":";
		try {
			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieinfo.csv"));
			// create an empty array list with an initial capacity
    			//List<String> slist = new ArrayList<String>();

			while ((line = br1.readLine()) != null) {
				String[] country = line.split(cvsSplitBy);
				if (!slist.contains(country[0])) {
				slist.add(new String(country[0])); 
				}

				if (!alist.contains(country[2])) {
				alist.add(new String(country[2])); 
				}

				String[] actorsArray = country[4].split(",");
				for (int i = 0; i < actorsArray.length; i++) {
    				actorsArray[i] = actorsArray[i].trim();

				if (!blist.contains(actorsArray[i]))
					{ 
					blist.add(new String(actorsArray[i])); 
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
		
	}

    public void bufferedWrite()
	{
    	        File source1 =new File(System.getenv("HOME")+"/mridul_log/movieinfo.csv");
    	        File target1 =new File(System.getenv("HOME")+"/movieinfo.csv");
	        target1.delete();
    	        File source2 =new File(System.getenv("HOME")+"/mridul_log/movieratings.csv");
    	        File target2 =new File(System.getenv("HOME")+"/movieratings.csv");
	        target2.delete();
		BufferedReader br1 = null;
		String line = "";
		String line2 = "";
		BufferedReader br2 = null;
		try {
 			//Construct the new file that will later be renamed to the original filename.
  			//File tempFile = new File(System.getenv("HOME")+"/mridul_log/movieinfo" + ".csv");
			PrintWriter pw = new PrintWriter(new FileWriter(target1));

  			//File ratingsTempFile = new File(System.getenv("HOME")+"/mridul_log/movieratings" + ".csv");
			PrintWriter ratingspw = new PrintWriter(new FileWriter(target2));

			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieinfo.csv"));
			while ((line = br1.readLine()) != null) {
				pw.println(line);
				pw.flush();
			}
			pw.close();

			br2 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieratings.csv"));
			while ((line2 = br2.readLine()) != null) {
				ratingspw.println(line2);
				ratingspw.flush();
			}
			ratingspw.close();
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


    public void init()	
	{
	try {
		BufferedReader br1 = null;
		String line = "";
		String line2 = "";
		BufferedReader br2 = null;
		boolean success = (new File(System.getenv("HOME")+"/mridul_log")).mkdirs();
		//listinsert();
		try {
 			//Construct the new file that will later be renamed to the original filename.
  			File tempFile = new File(System.getenv("HOME")+"/mridul_log/movieinfo" + ".csv");
			PrintWriter pw = new PrintWriter(new FileWriter(tempFile));

  			File ratingsTempFile = new File(System.getenv("HOME")+"/mridul_log/movieratings" + ".csv");
			PrintWriter ratingspw = new PrintWriter(new FileWriter(ratingsTempFile));

			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/movieinfo.csv"));
			while ((line = br1.readLine()) != null) {
				pw.println(line);
				pw.flush();
			}
			pw.close();

			br2 = new BufferedReader(new FileReader(System.getenv("HOME")+"/movieratings.csv"));
			while ((line2 = br2.readLine()) != null) {
				ratingspw.println(line2);
				ratingspw.flush();
			}
			ratingspw.close();
			listinsert();
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
	catch (Exception e) {
		System.out.println(e);
	}

	new Thread()
	{ public void run()
		{ 
		while(true)
		{
		bufferedWrite();

		 try { 
			Thread.sleep(100000); 
		     } 
		  catch (InterruptedException ex) {
		 	System.out.println(ex);
		     }
	        } 
		} 
	}.start();

	}





    		
    public void doGet(HttpServletRequest request,HttpServletResponse response)
					        throws IOException, ServletException // This method is called whenver we invoke this servlet. 
	// Use "request" to read incoming HTTP headers
	// Use "response" to specify the HTTP response line and headers
  	{
	//init();
        response.setContentType("text/html");
        PrintWriter out = response.getWriter(); // Use "out" to send content to browser
        out.println("<html>");
        out.println("<body bgcolor=\"white\">");
        out.println("<head>");
        out.println("<title>  Survey  </title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h3 align=\"center\">Movie Database</h3><hr>");
	if(request.getParameter("SUBMIT")==null){     // value of SUBMIT parameter determines which link or url is used invoking servlet
			//init();
			form1(request, response, out);
	} 

	else if(request.getParameter("SUBMIT").toString().equals("BACK")){
				//init();
				form1(request,response,out);    // Input Form
	}
	else {
                        	form2(request, response, out);  // Result form
        }
	out.println("</body>");
        out.println("</html>");
        
    }
    	


    	public void doPost(HttpServletRequest request,HttpServletResponse response)
        	throws IOException, ServletException
    	{
        	doGet(request, response);
    	}

	public void form1(HttpServletRequest request,HttpServletResponse response,PrintWriter out) 
	// This method gets invoked at start of servlet or whenever BACK is clicked from form2. This just shows the input form 
	{
	out.println("<P>");
        out.print("<form action=\"");
        out.print(response.encodeURL("First"));  // Here name of servlet to be invoked needs to be given
        out.print("\" ");
        out.println("method=GET>");
        
	out.println("<table border=\"0\" cellpadding=\"2\" cellspacing=\"0\">");
	out.println("<tr><td align=\"right\" nowrap  class=\"bodywhite\">Query parameter</td>");
	//out.println("<td align=\"right\"><input name=\"number1\" size=\"17\" ></td>");
	out.println("<td align=\"right\"><select name = \"number1\" size=\"1\">");
	listinsert();
	for (int i=0;i<slist.size();i++) 
	{
      	out.println("<option>"+ slist.get(i) +"</option>");
	}
	out.println("</select></td>");
	out.println("<td align=\"right\"><select name = \"number2\" size=\"1\">");
	for (int i=0;i<blist.size();i++) 
	{
      	out.println("<option>"+ blist.get(i) +"</option>");
	}
	out.println("</select></td>");
	out.println("<td align=\"right\"><select name = \"number3\" size=\"1\">");
	for (int i=0;i<alist.size();i++) 
	{
      	out.println("<option>"+ alist.get(i) +"</option>");
	}
	out.println("</select></td>");
	//out.println("<td align=\"right\" nowrap  class=\"bodywhite\">Number 2 </td>");
	//out.println("<td align=\"right\"><input name=\"number2\" size=\"17\" ></td>");
	out.println("</tr><tr>");
	out.println("<td colspan=\"2\" align=\"right\"><input type=submit name=\"SUBMIT\" value=\"q1\" ></td>"); // All the buttons have same name "SUBMIT" but different value
	out.println("<td colspan=\"1\" align=\"right\"><input type=submit name=\"SUBMIT\" value=\"q2\" ></td>");
	out.println("<td colspan=\"2\" align=\"right\"><input type=submit name=\"SUBMIT\" value=\"q3\" ></td>");
	out.println("</tr><tr>");
	out.println("<td colspan=\"2\" align=\"right\"><input type=submit name=\"SUBMIT\" value=\"q5\" ></td>");
	out.println("</tr>");		
	out.println("</table>");
	out.println("<table border=\"0\" cellpadding=\"2\" cellspacing=\"0\">");
	out.println("<tr><td align=\"right\" nowrap  class=\"bodywhite\">Insert New Movie</td>");
	out.println("</tr>");
	out.println("<tr>");
	out.println("<td align=\"right\" nowrap  class=\"bodywhite\">Movie Name</td>");
	out.println("<td align=\"right\"><input name=\"movieName\" size=\"17\" ></td>");
	out.println("</tr>");
	out.println("<tr>");
	out.println("<td align=\"right\" nowrap  class=\"bodywhite\">Director Name</td>");
	out.println("<td align=\"right\"><input name=\"directorName\" size=\"17\" ></td>");
	out.println("</tr>");
	out.println("<tr>");
	out.println("<td align=\"right\" nowrap  class=\"bodywhite\">Year</td>");
	out.println("<td align=\"right\"><input name=\"year\" size=\"17\" ></td>");
	out.println("</tr>");
	out.println("<tr>");
	out.println("<td align=\"right\" nowrap  class=\"bodywhite\">Genre</td>");
	out.println("<td align=\"right\"><input name=\"genre\" size=\"17\" ></td>");
	out.println("</tr>");
	out.println("<tr>");
	out.println("<td align=\"right\" nowrap  class=\"bodywhite\">Actor Names (seprated by commas)</td>");
	out.println("<td align=\"right\"><input name=\"actors\" size=\"17\" ></td>");
	out.println("</tr>");
	out.println("<tr>");
	out.println("<td align=\"right\" nowrap  class=\"bodywhite\">Rating</td>");
	out.println("<td align=\"right\"><input name=\"rating\" size=\"17\" ></td>");
	out.println("</tr>");
	out.println("<tr>");
	out.println("<td colspan=\"2\" align=\"right\"><input type=submit name=\"SUBMIT\" value=\"q4\" ></td>");
	out.println("</tr>");	
	out.println("</table>");
	out.println("<table border=\"0\" cellpadding=\"2\" cellspacing=\"0\">");
	out.println("<tr><td align=\"right\" nowrap  class=\"bodywhite\">Change information about a movie</td>");
	out.println("</tr>");
	out.println("<tr>");
	out.println("<td align=\"right\" nowrap  class=\"bodywhite\">Movie Name</td>");
	//out.println("<td align=\"right\"><input name=\"MovieNameChange\" size=\"17\" ></td>");
	out.println("<td align=\"right\"><select name = \"MovieNameChange\" size=\"1\">");
	listinsert();
	for (int i=0;i<slist.size();i++) 
	{
      	out.println("<option>"+ slist.get(i) +"</option>");
	}
	out.println("</select></td>");
	out.println("</tr>");
	out.println("<tr>");
	out.println("<td align=\"right\" nowrap  class=\"bodywhite\">Field which you want to change</td>");
	out.println("<td align=\"right\"><select name = \"category\" size=\"1\">");
	out.println("<option name = \"directorchange\" >Director name</option>");
	out.println("<option name = \"relyearchange\" >Year of release</option>");
	out.println("<option name = \"genrechange\" >Genre</option>");
	out.println("<option name = \"actorchange\" >Actor Names(seprated by commes)</option>");
	out.println("<option name = \"ratingchange\" >Movie Rating</option>");
	out.println("</select></td>");
	out.println("<tr>");
	out.println("<td align=\"right\" nowrap  class=\"bodywhite\">Changed Information</td>");
	out.println("<td align=\"right\"><input name=\"changedInfo\" size=\"17\" ></td>");
	out.println("</tr>");
	out.println("<tr>");
	out.println("<td colspan=\"2\" align=\"right\"><input type=submit name=\"SUBMIT\" value=\"q6\" ></td>");
	out.println("</tr>");
	out.println("</td>");
	out.println("</table>");
       	out.println("</form>");
	}


	public synchronized void form2(HttpServletRequest request,HttpServletResponse response,PrintWriter out) // This page displays result in new page 
        // It contain link back to input form
	{
		/*try {
		Thread.sleep(60000);
		}
		catch (Exception e) {
		System.out.println(e);
		}*/
		String operation;
		String num1;
		String num2;
		String num3;
		String movieName;
		String directorName;
		String year;
		String genre;
		String actors;
		String rating;
		String MovieNameChange;
		String category;
		String changedInfo;
		String res = "";
		num1 = request.getParameter("number1"); // To get data entered in textbox named "number1" 
		num2 = request.getParameter("number2"); // To get data entered in textbox named "number2" 
		num3 = request.getParameter("number3"); // To get data entered in textbox named "number3" 
		movieName = request.getParameter("movieName"); // To get data entered in textbox named "number1" 
		directorName = request.getParameter("directorName"); // To get data entered in textbox named "number1" 
		year = request.getParameter("year"); // To get data entered in textbox named "number2" 
		genre = request.getParameter("genre"); // To get data entered in textbox named "number1" 
		actors = request.getParameter("actors"); // To get data entered in textbox named "number1" 
		rating = request.getParameter("rating"); // To get data entered in textbox named "number2" 
		MovieNameChange = request.getParameter("MovieNameChange"); // To get data entered in textbox named "number2" 
		category = request.getParameter("category"); // To get data entered in textbox named "number2" 
		changedInfo = request.getParameter("changedInfo"); // To get data entered in textbox named "number2" 		
		operation = request.getParameter("SUBMIT");
		if(operation.equals("q1"))
		{
		out.println("<P> You requested the " + operation + " on " + num1 + "<BR>");
		BufferedReader br1 = null;
		String line = "";
		String cvsSplitBy = ":";

		try {
 
			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieinfo.csv"));
			while ((line = br1.readLine()) != null) {
				String[] country = line.split(cvsSplitBy);
 				if ( country[0].equals(num1))
				{
				res = country[1];
				out.println(" The Result is = " + res + "</br>");
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
	
		else if (operation.equals("q2"))
		{
		out.println("<P> You requested the " + operation + " on " + num2 + "<BR>");
		out.println(" The Result is = " + "</br>");
		BufferedReader br1 = null;
		String line = "";
		String cvsSplitBy = ":";

		try {
 
			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieinfo.csv"));
			while ((line = br1.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
				String[] actorsArray = country[4].split(",");
				for (int i = 0; i < actorsArray.length; i++) {
    				actorsArray[i] = actorsArray[i].trim();

				if (actorsArray[i].equals(num2))
					{ 
					out.println( country[0] + "</br>"); 
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
		}

		else if (operation.equals("q3"))
		{
		out.println("<P> You requested the " + operation + " on " + num3 + "<BR>");
		out.println(" The Result is = " + "</br>");
		BufferedReader br1 = null;
		String line = "";
		BufferedReader br2 = null;
		String line2 = "";
		String cvsSplitBy = ":";
		String ans = "";
		float max = 0;

		try {
 
			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieinfo.csv"));
			while ((line = br1.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
 				if ( country[2].equals(num3))
				{
					try {
 
					      br2 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieratings.csv"));
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
		
		out.println( ans + "</br>");
		}


		else if (operation.equals("q4"))
		{
		out.println("<P> You requested the " + operation + " on " + movieName + "<BR>");
		//out.println(" The Result is = " + "</br>");
		BufferedReader br1 = null;
		String line = "";
		String cvsSplitBy = ":";
		String ans = "";
		int flag = 0;
		try {
 
			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieinfo.csv"));
			while ((line = br1.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
 				if ( country[0].equals(movieName))
				{
				flag = 1;
				ans = "Movie already exists in the database";
				}
			}
			if (flag == 0) {
				FileWriter writer = new FileWriter(System.getenv("HOME")+"/mridul_log/movieinfo.csv",true);
	    			writer.append(movieName);
	    			writer.append(':');
	    			writer.append(directorName);
	    			writer.append(':');
	    			writer.append(year);
	    			writer.append(':');
	    			writer.append(genre);
	    			writer.append(':');
	    			writer.append(actors);
				writer.append('\n');
	       	 		writer.flush();
	       	 		writer.close();
				FileWriter ratingsWriter = new FileWriter(System.getenv("HOME")+"/mridul_log/movieratings.csv",true);
	    			ratingsWriter.append(movieName);
	    			ratingsWriter.append(':');
	    			ratingsWriter.append(rating);
				ratingsWriter.append('\n');
	       	 		ratingsWriter.flush();
	       	 		ratingsWriter.close();
				ans = "Movie added to the database";
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
		out.println( ans + "</br>");
		
		}


		else if (operation.equals("q5"))
		{
		out.println("<P> You requested the " + operation + " on " + num1 + "<BR>");
		//out.println(" The Result is = " + "</br>");
		BufferedReader br1 = null;
		String line = "";
		BufferedReader br2 = null;
		String line2 = "";
		String cvsSplitBy = ":";
		int flag5 = 0;
		int flag6 = 0;
		String ans1 = "";
		String ans2 = "";
		//int endIndex = s.length();
		//int startIndex = s.indexOf(" ");
		//String modified_s = request.getParameter("number1");;
		File inFile = new File(System.getenv("HOME")+"/mridul_log/movieinfo.csv");
		File ratingsInFile = new File(System.getenv("HOME")+"/mridul_log/movieratings.csv");

		try {
 			//Construct the new file that will later be renamed to the original filename.
  			File tempFile = new File(System.getenv("HOME")+"/mridul_log/movieinfo" + ".tmp");
			PrintWriter pw = new PrintWriter(new FileWriter(tempFile));

  			File ratingsTempFile = new File(System.getenv("HOME")+"/mridul_log/movieratings" + ".tmp");
			PrintWriter ratingspw = new PrintWriter(new FileWriter(ratingsTempFile));

			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieinfo.csv"));
			while ((line = br1.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
 				if ( !country[0].equals(num1))
				{
				pw.println(line);
				pw.flush();
				}

				else 
				flag5 = 1;
 			
			}
			pw.close();

			br2 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieratings.csv"));
			while ((line2 = br2.readLine()) != null) {
 
				String[] movie = line2.split(cvsSplitBy);
 				if ( !movie[0].equals(num1))
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
				ans1 = "Movie deleted from the info database";
			if (flag5 == 0)
				ans1 = "Movie does not exist in the info database";

			if (flag6 == 1) 
				ans2 = "Movie deleted from the ratings database";
			if (flag6 == 0)
				ans2 = "Movie does not exist in the ratings database";

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
 		
		out.println( ans1 + "</br>" + ans2 + "</br>");
		}


		else if (operation.equals("q6"))
		{
		out.println("<P> You requested the " + operation + " on " + MovieNameChange + "<BR>");
		int flag5 = 0;
		BufferedReader br1 = null;
		String line = "";
		BufferedReader br2 = null;
		String line2 = "";
		String cvsSplitBy = ":";
		String ans1 = "";
		File inFile = new File(System.getenv("HOME")+"/mridul_log/movieinfo.csv");
		File ratingsInFile = new File(System.getenv("HOME")+"/mridul_log/movieratings.csv");

		try {
 			//Construct the new file that will later be renamed to the original filename.
  			File tempFile = new File(System.getenv("HOME")+"/mridul_log/movieinfo" + ".tmp");
			PrintWriter pw = new PrintWriter(new FileWriter(tempFile));

			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieinfo.csv"));
			while ((line = br1.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
 				if ( country[0].equals(MovieNameChange))
				{
					flag5 = 1;
				/*System.out.println("To change information about the movie - " + modified_s + ". Enter commands:");
				System.out.println("c1 <Director name>");
				System.out.println("c2 <Year of release>");
				System.out.println("c3 <Genre>");
				System.out.println("c4 <Actor names seprated by commas>");
				System.out.println("c5 <Movie rating>");*/
				//change = in.nextLine();
				//int changeEndIndex = change.length();
				//int changeStartIndex = change.indexOf(" ");
				//String modified_change = change.substring(changeStartIndex + 1, changeEndIndex);
				//String command = change.substring(0, changeStartIndex);
					if ( category.equals("Director name"))
					{
					pw.println(country[0] +":"+ changedInfo + ":" + country[2] + ":" + country[3] +":" + country[4] );
					pw.flush();
					}
					else if ( category.equals("Year of release"))
					{
					pw.println(country[0] +":"+ country[1] + ":" + changedInfo + ":" + country[3] +":" + country[4] );
					pw.flush();
					}
					else if ( category.equals("Genre"))
					{
					pw.println(country[0] +":"+ country[1] + ":" + country[2] + ":" + changedInfo +":" + country[4] );
					pw.flush();
					}
					else if ( category.equals("Actor Names(seprated by commes)"))
					{
					pw.println(country[0] +":"+ country[1] + ":" + country[2] + ":" + country[3] +":" + changedInfo );
					pw.flush();
					}
					else if ( category.equals("Movie Rating"))
					{
					pw.println(line);
					pw.flush();
  					File ratingsTempFile = new File(System.getenv("HOME")+"/mridul_log/movieratings" + ".tmp");
					PrintWriter ratingspw = new PrintWriter(new FileWriter(ratingsTempFile));
					br2 = new BufferedReader(new FileReader(System.getenv("HOME")+"/mridul_log/movieratings.csv"));
					while ((line2 = br2.readLine()) != null) {
 
						String[] movie = line2.split(cvsSplitBy);
 						if ( movie[0].equals(MovieNameChange))
						{
						ratingspw.println(movie[0] +":"+ changedInfo);
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
					System.out.println("Wrong Input"+ category);
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
				ans1 = "Movie information edited in the database";
			if (flag5 == 0)
				ans1 = "Movie name does not exist in the database";


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
 		out.println( ans1 + "</br>");
		}



		out.println("<p><p align=center > <a href=First?SUBMIT=BACK>BACK </a>"); // This is way of passing parameters to the servlet. SUMBMIT is name of parameter and its value is "BACK"  
	}
}
