import java.lang.*;
import java.io.*;
import java.util.*;
public class inheritance {
    static void  poop(){
        new son(3);new daughter();
        son dio=new son(2);
        System.out.printf("%d\n",dio.sum(3,3,1));
        System.out.print(dio);
        new daughter().fuck();
        new daughter().stone();
    }
    public static void main(String argv[]){
        poop();
    }
}
abstract class daddy{
    daddy(int x){
        System.out.printf("Daddy Constructor is called\n");
    }
    public int sum(int x,int y){
        return x+y;
    }
    @Override
    public String toString() {
        return "This is the daddy of the daddies\n"; 
        //return super.toString();
    }
}
interface mommy{
    public void stone();
    public void fuck();
}
class son extends daddy {
    int a;
    son(int x){
        super(x);
        a=x;
        System.out.printf("Son Constructor is called\n");
    }
    public int sum(int x,int y,int i){
        if(i==1)return super.sum(x,y);
        return x*y;
    }
    @Override
    public String toString() {
        return super.toString();
        //return super.toString();
    }
}
class daughter implements whore {
    daughter(){
        System.out.printf("Daughter Constructor is called\n");
    }
    public void stone(){
        System.out.printf("Daughter stoned by mommy\n");
    }
    public void fuck(){
        System.out.printf("Daughter called fuck by mommy\n");
    }
}
interface milkman extends mommy{

}
interface newspaperboy extends mommy{

}
interface whore extends milkman,newspaperboy{

}
