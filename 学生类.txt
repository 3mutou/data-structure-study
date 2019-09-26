package 学生类;
class xuesheng{
	private	String name1;
	private int age1;
	public String degree1;
	public xuesheng(String name,int age,String degree) {
		name1=name;
		age1=age;
		degree1=degree;
	}
    public void out() {
    	System.out.println("姓名："+name1+"\n"+"年龄："+age1+"\n"+"学位："+degree1);
    }
}
class java3 extends xuesheng{
	private String yanjiu1;
	public java3(String name,int age,String degree,String yanjiu) {
		super(name,age,degree);
		yanjiu1=yanjiu;
	}
	public void out() {
		super.out();
		System.out.println("研究方向："+yanjiu1);
	}
}
class Student extends xuesheng{
	private String zhuanye1;
	public Student(String name,int age,String degree,String zhuanye) {
		super(name,age,degree);
		zhuanye1=zhuanye;
	}
	public void out() {
		super.out();
		System.out.println("专业："+zhuanye1+"\n");
	}
	public static void main(String[] args) { 
		Student a=new Student("李四",27,"本科生","软件工程");
		a.out();
		java3 b=new java3("王五",31,"博士","网络安全");
		b.out();
	}
}

