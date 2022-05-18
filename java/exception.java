
import java.io.*;
import java.util.*;
public class exception {
    public static void main(String agrv[]){
        Scanner in=new Scanner (System.in);
        String s=in.next();
        try{
            if(s.compareTo("Dio")==0) {
                throw (new throwableExceptionDioSpotted());
            }
        }
        catch(Throwable e){
            System.out.print(e);
        }
        while(true){
            System.out.printf("Enter 1 to create file 2 to delete file 3 to read to file 4 to write file 5 to append in a file 6 to quit\n");
            int choice=in.nextInt();
            System.out.printf("Enter FileName\n");
            String FileName=in.next();
        if(choice==1){
            try{
                File f = new File(FileName);
                if(f.createNewFile()){
                    System.out.printf("File has been made\n");
                }
                else{
                    System.out.printf("File already exists u dumb fuck\n");
                }
            }
            catch(IOException e){
                System.out.println("An error has occurred.");
                e.printStackTrace();
            }
        }
        else if(choice==2){
            File f= new File(FileName);
            if(f.delete()){
                System.out.printf("File Has Been Deleted\n");
            }
            else{
                System.out.printf("You have failed in this like you have failed in everything else\n");
            }
        }
        else if(choice==3){
            try{
                File f=new File(FileName);
                Scanner Reader=new Scanner(f);
                while(Reader.hasNextLine()){
                    System.out.print(Reader.nextLine());
                }
                System.out.println("File has been read");
                Reader.close();
            }
            catch(IOException e){
                System.out.println("An error has occurred.");
                e.printStackTrace();                
            }
        }
        else if(choice==4){
            try{
                String ass;
                File f=new File(FileName);
                FileWriter fw = new FileWriter(f);
                System.out.println("Keep entering Strings to enter into files.\nPress !qw to exit mode\n");
                while(true){
                    ass=in.nextLine();
                    if(ass.compareTo("!qw")==0) break;
                    fw.write(ass+'\n');
                }
                fw.close();
                System.out.println("Writting has closed\n");
            }
            catch(IOException e){
                System.out.println("An error has occurred.");
                e.printStackTrace();       
            }
        }
        else if(choice==5){
            try{
                String ass;
                System.out.println("Keep entering Strings to enter into files.\nPress !qw to exit mode");
                BufferedWriter out = new BufferedWriter(new FileWriter(FileName, true));
                while(true){
                    ass=in.nextLine();
                    if(ass.compareTo("!qw")==0) break;
                    out.write(ass+'\n');
                }
                out.close();
            }
            catch(IOException e){
                System.out.println("An error has occurred.");
                e.printStackTrace();
            }
        }
    else if(choice==6) break;
    }
    in.close();
    }
}
class rowableExceptionDioSpotted extends Throwable{
    public String toString() {
        return "fuckker\n";
    }
}

class throwableExceptionDioSpotted extends Throwable{
    throwableExceptionDioSpotted(){
        
    }
    public String toString() {
        return "Dio Spotted Please Stay At A Safe Distance\n";
    }
}
