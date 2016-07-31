import java.io.*;
import java.util.*;
import java.net.*;

public class measure_direct_write
  {

	 public static void main(String[] args) {
	int i = 1000;
	long t1 = System.currentTimeMillis();
	while(i > 0) {

	try {
    	URL myURL = new URL("http://localhost:8080/First?number1=An+Unfinished+Life&number2=%C2%A0Robert+Redford&number3=1990&movieName=&directorName=&year=&genre=&actors=&rating=&MovieNameChange=The+Postman&category=Genre&changedInfo=Thriller&SUBMIT=q6");
    	URLConnection myURLConnection = myURL.openConnection();
    	myURLConnection.connect();
	} 
	catch (MalformedURLException e) { 
    		System.out.println(e);
	} 
	catch (IOException e) {   
    		System.out.println(e);
	}

	i=i-1;
        }
	long t2 = System.currentTimeMillis();
	double t3 = t2-t1;
	System.out.println("Time in case Direct Write for 1000 iterations = " + t3/1000.0 + "seconds.");
}
}

