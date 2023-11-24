```
import std.io;

add(int firstNumber, int secondNumber) {
    return firstNumber + secondNumber;
}
remove(int firstNumber, int secondNumber) {
    return firstNumber - secondNumber;
}

main() {
    print("This is just a simple example of a Lumix library!");
    x = 1;
    y = 2;
    result = add(x, y);
    if (result == 3) {
        print("x + y equals " + result + ".");
    } else {
        print("x + y doesn't equal 3.");
        exit(1); // Exit with an error.
    }
}
```