
// Import the File class
import java.io.File; 
  
public class GFG {
    public static void main(String[] args)
    {
        File Obj = new File("myfile.txt");
        if (Obj.delete()) {
            System.out.println("The deleted file is : "
                               + myObj.getName());
        }
        else {
            System.out.println(
                "Failed in deleting the file.");
        }
    }
}