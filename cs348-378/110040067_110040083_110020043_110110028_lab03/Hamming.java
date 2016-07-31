/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import java.io.*;
import java.util.*;
/**
 *
 * @author Tarun Kathuria
 */
public class Hamming {
    public static String ret(int n){
        if(n==1)
            return "1";
        else
            return "0";
    }
    public static int binToInt(String l){
        if(l.equals("0000"))
            return 0;
        else if(l.equals("0001"))
             return 1;
        else if(l.equals("0010"))
             return 2;
        else if(l.equals("0011"))
             return 3;
        else if(l.equals("0100"))
             return 4;
        else if(l.equals("0101"))
             return 5;
        else if(l.equals("0110"))
             return 6;
        else if(l.equals("0111"))
             return 7;
        else if(l.equals("1000"))
             return 8;
        else if(l.equals("1001"))
             return 9;
        else if(l.equals("1010"))
             return 10;
        else if(l.equals("1011"))
             return 11;
        else if(l.equals("1100"))
             return 12;
        return -1;
    }
    public static ArrayList<Integer> toInt(String l){
        ArrayList<Integer> a=new ArrayList<>();
        a.add(5);
        for(int i=0;i<l.length();i++){
            a.add(Integer.parseInt(l.substring(i,i+1)));
        }
        return a;
    }
    
    public static void main(String[] args){
        String opt="D";
        String bitstring;
        Scanner sc = new Scanner(System.in);
        opt=sc.next();
        bitstring=sc.next();
        //0110011000
        ///////Decoding
        
        if(opt.equals("D")){
            int n=bitstring.length();
            ArrayList<Integer> a=toInt(bitstring);
            String ans="";
            if(n==3){
                
                String c8="0";
                String c4="0";
                String c2=ret(a.get(2)^a.get(3));
                String c1=ret(a.get(1)^a.get(3));
                ans=c8+c4+c2+c1;
            }
            
            else if(n==5){
                String c1=ret(a.get(1)^a.get(3)^a.get(5));
                String c2=ret(a.get(2)^a.get(3));
                String c4=ret(a.get(4)^a.get(5));
                String c8="0";
                ans=c8+c4+c2+c1;  
            }
            
            else if(n==6){
                String c1=ret(a.get(1)^a.get(3)^a.get(5));
                String c2=ret(a.get(2)^a.get(3)^a.get(6));
                String c4=ret(a.get(4)^a.get(5)^a.get(6));
                String c8="0";
                ans=(c8+c4+c2+c1);  
            }
            else if(n==7){
                 String c1=ret(a.get(1)^a.get(3)^a.get(5)^a.get(7));
                String c2=ret(a.get(2)^a.get(3)^a.get(6)^a.get(7));
                String c4=ret(a.get(4)^a.get(5)^a.get(6)^a.get(7));
                String c8="0";
                ans=(c8+c4+c2+c1);  
            }
            
            else if(n==9){
                String c1=ret(a.get(1)^a.get(3)^a.get(5)^a.get(7)^a.get(9));
                String c2=ret(a.get(2)^a.get(3)^a.get(6)^a.get(7));
                String c4=ret(a.get(4)^a.get(5)^a.get(6)^a.get(7));
                String c8=ret(a.get(8)^a.get(9));
                ans=(c8+c4+c2+c1);  
            }
            else if(n==10){
                String c1=ret(a.get(1)^a.get(3)^a.get(5)^a.get(7)^a.get(9));
                String c2=ret(a.get(2)^a.get(3)^a.get(6)^a.get(7)^a.get(10));
                String c4=ret(a.get(4)^a.get(5)^a.get(6)^a.get(7));
                String c8=ret(a.get(8)^a.get(9)^a.get(10));
                ans=(c8+c4+c2+c1);  
            }
            else if(n==11){
                String c1=ret(a.get(1)^a.get(3)^a.get(5)^a.get(7)^a.get(9)^a.get(11));
                String c2=ret(a.get(2)^a.get(3)^a.get(6)^a.get(7)^a.get(10)^a.get(11));
                String c4=ret(a.get(4)^a.get(5)^a.get(6)^a.get(7));
                String c8=ret(a.get(8)^a.get(9)^a.get(10)^a.get(11));
                ans=(c8+c4+c2+c1);  
            }
            else if(n==12){
                String c1=ret(a.get(1)^a.get(3)^a.get(5)^a.get(7)^a.get(9)^a.get(11));
                String c2=ret(a.get(2)^a.get(3)^a.get(6)^a.get(7)^a.get(10)^a.get(11));
                String c4=ret(a.get(4)^a.get(5)^a.get(6)^a.get(7)^a.get(12));
                String c8=ret(a.get(8)^a.get(9)^a.get(10)^a.get(11)^a.get(12));
                ans=(c8+c4+c2+c1);
            }
            System.out.println("error bit is "+ans);
            int errBit=binToInt(ans);
            if(errBit<0)
                System.out.println("ERROR!!!!!!!!!!!!");
            else if(errBit==0){
                for(int i=1;i<a.size();i++){
                    if(i==1||i==2||i==4||i==8)
                        continue;
                    System.out.print(a.get(i));
                }
            }
            else{
                int val=5;
                if(a.get(errBit)==0)
                    val=1;
                else if(a.get(errBit)==1)
                    val=0;
                a.set(errBit,val);
                System.out.println("size of a is:"+ a.size());
                for(int i=1;i<a.size();i++){
                    if(i==1||i==2||i==4||i==8)
                        continue;
                    System.out.print(a.get(i));
                }
            }
        
        
        
        
        
        
        }
        
        
        
        
        
        else if(opt.equals("E")){
        
       // Encoding
         
         
         ArrayList<String> pkts=new ArrayList<>();
        String one="1",zero="0";
        for(int i=0;i<bitstring.length();i+=8){
            String pkt;
            if(i+8>=bitstring.length()-1){
                pkt=bitstring.substring(i,bitstring.length());
            }
            else
                pkt=bitstring.substring(i, i+8);
            pkts.add(pkt);
        }
        System.out.println("Packets b4 encoding are:");
        for(String s:pkts){
            System.out.println(s);
        }
        ArrayList<String> pktsnew=new ArrayList<>();
        
        
        
        
        
        for(String s:pkts){
            int n=s.length();
            if(n==1){
                if(s.charAt(0)=='1'){
                    pktsnew.add("111");
                }
                else
                    pktsnew.add("000");
            }
            
            else if(n==2){
                String X3=s.substring(0,1);
                String X5=s.substring(1,2);
                int x3=s.charAt(0)-'0';
                int x5=s.charAt(1)-'0';
                int p1=(x3^x5);
                
                int p2=x3;
                
                String P1=ret(p1);
                String P2=ret(p2);
                String P4=ret(x5);
                pktsnew.add(P1+P2+X3+P4+X5);
               // System.out.println(P1+" "+P2+" "+X3+" "+P4+" "+X5);
            }
            
            else if(n==3){
                String X3=s.substring(0,1),X5=s.substring(1,2),X6=s.substring(2,3);
                int x3=Integer.parseInt(X3),x5=Integer.parseInt(X5),x6=Integer.parseInt(X6);
                int p1=x3^x5,p2=x3^x6,p4=x5^x6;
                String P1=ret(p1);
                String P2=ret(p2);
                String P4=ret(p4);
                pktsnew.add(P1+P2+X3+P4+X5+X6);
            }
            
            else if(n==4){
                String X3=s.substring(0,1),X5=s.substring(1,2),X6=s.substring(2,3),X7=s.substring(3,4);
                int x3=Integer.parseInt(X3),x5=Integer.parseInt(X5),x6=Integer.parseInt(X6),x7=Integer.parseInt(X7);
                int p1=x3^x5^x7,p2=x3^x6^x7,p4=x5^x6^x7;
                String P1=ret(p1);
                String P2=ret(p2);
                String P4=ret(p4);
                pktsnew.add(P1+P2+X3+P4+X5+X6+X7);
            }
            
            else if(n==5){
                String X3=s.substring(0,1),X5=s.substring(1,2),X6=s.substring(2,3),X7=s.substring(3,4),X9=s.substring(4,5);
                int x3=Integer.parseInt(X3),x5=Integer.parseInt(X5),x6=Integer.parseInt(X6),x7=Integer.parseInt(X7),x9=Integer.parseInt(X9);
                int p1=x3^x5^x7^x9,p2=x3^x6^x7,p4=x5^x6^x7,p8=x9;
                String P1=ret(p1);
                String P2=ret(p2);
                String P4=ret(p4);
                String P8=ret(p8);
                pktsnew.add(P1+P2+X3+P4+X5+X6+X7+P8+X9);
            }
            
            else if(n==6){
                String X3=s.substring(0,1),X5=s.substring(1,2),X6=s.substring(2,3),X7=s.substring(3,4),X9=s.substring(4,5),X10=s.substring(5,6);
                int x3=Integer.parseInt(X3),x5=Integer.parseInt(X5),x6=Integer.parseInt(X6),x7=Integer.parseInt(X7),x9=Integer.parseInt(X9),x10=Integer.parseInt(X10);
                int p1=x3^x5^x7^x9,p2=x3^x6^x7^x10,p4=x5^x6^x7,p8=x9^x10;
                String P1=ret(p1);
                String P2=ret(p2);
                String P4=ret(p4);
                String P8=ret(p8);
                pktsnew.add(P1+P2+X3+P4+X5+X6+X7+P8+X9+X10);
            }
            
            else if(n==7){
                String X3=s.substring(0,1),X5=s.substring(1,2),X6=s.substring(2,3),X7=s.substring(3,4),X9=s.substring(4,5),X10=s.substring(5,6),X11=s.substring(6,7);
                int x3=Integer.parseInt(X3),x5=Integer.parseInt(X5),x6=Integer.parseInt(X6),x7=Integer.parseInt(X7),x9=Integer.parseInt(X9),x10=Integer.parseInt(X10),x11=Integer.parseInt(X11);
                int p1=x3^x5^x7^x9^x11,p2=x3^x6^x7^x10^x11,p4=x5^x6^x7,p8=x9^x10^x11;
                String P1=ret(p1);
                String P2=ret(p2);
                String P4=ret(p4);
                String P8=ret(p8);
                pktsnew.add(P1+P2+X3+P4+X5+X6+X7+P8+X9+X10+X11);
            }
            
            else if(n==8){
                String X3=s.substring(0,1),X5=s.substring(1,2),X6=s.substring(2,3),X7=s.substring(3,4),X9=s.substring(4,5),X10=s.substring(5,6),X11=s.substring(6,7),X12=s.substring(7,8);
                int x3=Integer.parseInt(X3),x5=Integer.parseInt(X5),x6=Integer.parseInt(X6),x7=Integer.parseInt(X7),x9=Integer.parseInt(X9),x10=Integer.parseInt(X10),x11=Integer.parseInt(X11),x12=Integer.parseInt(X12);
                int p1=x3^x5^x7^x9^x11,p2=x3^x6^x7^x10^x11,p4=x5^x6^x7^x12,p8=x9^x10^x11^x12;
                String P1=ret(p1);
                String P2=ret(p2);
                String P4=ret(p4);
                String P8=ret(p8);
                pktsnew.add(P1+P2+X3+P4+X5+X6+X7+P8+X9+X10+X11+X12);
            }
        
        }
        System.out.println("after encoding:");
        for(String s : pktsnew){
            System.out.println(s);
        }
        }
       // System.out.println(1^0);       
    }
    
    
    
    
}
