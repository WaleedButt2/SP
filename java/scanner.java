public class scanner {
    public static void main(String args[]){
        jojo[] array;
        array= new jojo[10];
        for(int i=0;i<array.length;i++){
            if(i%2==0)array[i]=new dio();
            else array[i]=new jojo();
        }
        System.out.printf("%d\n",array[0].get_count());
    }
}
class jojo{
    public int get_count(){
        return -1;
    }
    jojo(){
        System.out.println("This is Parent");
    }
}
class dio extends jojo{
    static int count=0;
    {
        count++;
    }
    public int get_count(){
        return count;
    }
    dio(){
        System.out.println("This is Child");
    }
}
