






class Cat
{
    private String current = "*";
    String ans = "";
    private int s = 0;
    public void leap()
    {  
        if (s < 4) 
        {
            s++;
            ans+=".";
        }
        current+=ans+"*";
    }

    public String path()
    {
        return current;
    }


    public static void main(String[] a)
    {   

            Cat cat = new Cat();
            // assertEquals("*", cat.path());
            System.out.println(cat.path());
            cat.leap();
            System.out.println(cat.path());

            // assertEquals("*.*", cat.path());
            cat.leap();
            System.out.println(cat.path());

            // assertEquals("*.*..*", cat.path());
            cat.leap();
            System.out.println(cat.path());

            // assertEquals("*.*..*...*", cat.path());
            cat.leap();
            System.out.println(cat.path());

            // assertEquals("*.*..*...*....*", cat.path());
            cat.leap();
            System.out.println(cat.path());

            // assertEquals("*.*..*...*....*....*", cat.path());

    }
}