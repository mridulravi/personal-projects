import java.io.*;
import java.util.*;
import java.net.*;

public class measure_buffered_write
  {

	 public static void main(String[] args) {
	int i = 1000;
	long t1 = System.currentTimeMillis();
	while(i > 0) {

	try {
    	URL myURL = new URL("http://localhost:8080/First?number1=Capote&number2=Allie+Mickelson&number3=1982&SUBMIT=q5&movieName=&directorName=&year=&genre=&actors=&rating=&MovieNameChange=Gandhi&category=Director+name&changedInfo=");
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
	System.out.println("Time in case Buffered Write for 1000 iterations = " + t3/1000.0 + " seconds.");
}
}

	
