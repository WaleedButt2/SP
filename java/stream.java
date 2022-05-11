import java.io.FileOutputStream;
import java.util.*;
 
public class stream {
    public static void main(String[] args)
    {
 
        String data = "Welcome to GfG";
 
        try {
            FileOutputStream output
                = new FileOutputStream("output.txt");
 
            // The getBytes() method used
            // converts a string into bytes array.
            byte[] array = data.getBytes();
 
            // writing the string to the file by writing
            // each character one by one
            // Writes byte to the file
            output.write(array);
 
            output.close();
        }
 
        catch (Exception e) {
            e.getStackTrace();
        }
    }
}