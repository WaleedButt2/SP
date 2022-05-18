public class table {
    public static void main(String []argv){
        Obj ass=new Obj();
        NewThread t1=new NewThread(1,10,ass);
        NewThread t2=new NewThread(2,10,ass);
        NewThread t3=new NewThread(3,20,ass);
    }
}
class NewThread implements Runnable{
    Thread t;
    int a;
    int limit;
    Obj x;
    NewThread(int a,int limit,Obj x){
        this.a=a;
        this.limit=limit;
        this.x=x;
        t= new Thread(this);
        t.start();
    }
    public void run(){
        Obj.calcualte(a,limit);
    }
}
class Obj{
    public synchronized static void calcualte(int start,int limit){
        for(int i=0;i<limit;i++){
            System.out.printf("%d * %d = %d\n",i,start,i*start);
        }
    }
}

