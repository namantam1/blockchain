class Animal {

    // overridden method
    public void display(){
        System.out.println("I am an animal");
    }
}

class Dog extends Animal {

    // overriding method
    @Override
    public void display(){
        System.out.println("I am a dog");
    }

    public void printMessage(){

        // this calls overriding method
        display();

        // this calls overridden method
        super.display();
    }
}

interface Obj {
    void printHello();
}

class Oops {
    public static void main(String[] args) {
//        Dog dog1 = new Dog();
//        dog1.printMessage();

        // Anonymous
        Obj obj = new Obj() {

            @Override
            public void printHello() {
                System.out.println("Hello");
            }

            public void another() {
                printHello();
            }
        };

        obj.printHello();
    }
}
