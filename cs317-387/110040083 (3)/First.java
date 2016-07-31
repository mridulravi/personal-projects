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
    public void init()	
	{
		try {
			BufferedReader br1 = null;
			String line = "";
			String cvsSplitBy = ":";
			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/movieinfo.csv"));
			// create an empty array list with an initial capacity
    			//List<String> slist = new ArrayList<String>();

			while ((line = br1.readLine()) != null) {
				String[] country = line.split(cvsSplitBy);
				slist.add(new String(country[0])); 

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
		}
		catch (Exception e) {
			System.out.println(e);
		}

	}





    		
    public void doGet(HttpServletRequest request,HttpServletResponse response)
					        throws IOException, ServletException // This method is called whenver we invoke this servlet. 
	// Use "request" to read incoming HTTP headers
	// Use "response" to specify the HTTP response line and headers
  	{
	init();
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
			form1(request, response, out);
	} 

	else if(request.getParameter("SUBMIT").toString().equals("BACK")){
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
        out.println("method=POST>");
        
	out.println("<table border=\"0\" cellpadding=\"2\" cellspacing=\"0\">");
	out.println("<tr><td align=\"right\" nowrap  class=\"bodywhite\">Query parameter</td>");
	//out.println("<td align=\"right\"><input name=\"number1\" size=\"17\" ></td>");
	out.println("<td align=\"right\"><select name = \"number1\" size=\"1\">");
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
	out.println("</tr>");
	out.println("</table>");
       	out.println("</form>");
	}


	public void form2(HttpServletRequest request,HttpServletResponse response,PrintWriter out) // This page displays result in new page 
        // It contain link back to input form
	{
		String operation;
		String num1;
		String num2;
		String num3;
		String res = "";
		num1 = request.getParameter("number1"); // To get data entered in textbox named "number1" 
		num2 = request.getParameter("number2"); // To get data entered in textbox named "number1" 
		num3 = request.getParameter("number3"); // To get data entered in textbox named "number2" 
		operation = request.getParameter("SUBMIT");
		if(operation.equals("q1"))
		{
		out.println("<P> You requested the " + operation + " on " + num1 + "<BR>");
		BufferedReader br1 = null;
		String line = "";
		String cvsSplitBy = ":";

		try {
 
			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/movieinfo.csv"));
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
 
			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/movieinfo.csv"));
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
 
			br1 = new BufferedReader(new FileReader(System.getenv("HOME")+"/movieinfo.csv"));
			while ((line = br1.readLine()) != null) {
 
				String[] country = line.split(cvsSplitBy);
 				if ( country[2].equals(num3))
				{
					try {
 
					      br2 = new BufferedReader(new FileReader(System.getenv("HOME")+"/movieratings.csv"));
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
		out.println("<p><p align=center > <a href=First?SUBMIT=BACK>BACK </a>"); // This is way of passing parameters to the servlet. SUMBMIT is name of parameter and its value is "BACK"  
	}
}
