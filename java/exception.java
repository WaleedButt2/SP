import java.lang.*;
import java.io.*;
import java.util.*;
public class exception {
    public static void main(String agrv[]){
        Scanner in=new Scanner (System.in);
        String s=in.next();
        try{
            if(s.compareTo("Dio")==0) {
                in.close();
                throw (new throwableExceptionDioSpotted());
            }
        }
        catch(Throwable e){
            System.out.print(e);
        }
        String FileName=in.nextLine();
        
    }
}
class throwableExceptionDioSpotted extends RuntimeException{
    public String toString() {
        return "Dio Spotted Please Stay At A Safe Distance\n";
    }
}
