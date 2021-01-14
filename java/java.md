# Java

## Java的坑

### 数组是协变的与类型擦除实现泛型

```java
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
//        Float[] b = (Float[]) new Object[10];
//        b[0] = (Float)new Object();
        Object[] a = (Object[]) new Float[10];
        a[0] = 3.1f;
        Object obj = new Float(43.3);
        Float c = 3.1f;
        assert c == a[0];
        Object[] d = new Object[10];
        d[0] = new ArrayList<Integer>();
        ((ArrayList)d[0]).add(new Float(32.7f));
//        ((ArrayList<Integer>)d[0]).add(new Float(32.7f));
        ((ArrayList)d[0]).add(new ArrayList<>(32));
//        ArrayList<Object> li = new ArrayList<Float>();
    }
//    ArrayList<Object> foo() {
//        return new ArrayList<Float>();
//    }
//    ArrayList<Float> bar() {
//        return new ArrayList<Object>();
//    }
}
```