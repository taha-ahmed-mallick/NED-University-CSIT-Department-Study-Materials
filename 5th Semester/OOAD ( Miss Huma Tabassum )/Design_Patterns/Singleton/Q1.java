public class SingletonDemo {
    public static void main(String[] args) {
        System.out.println("=== Testing Eager Initialization ===");
        EagerDBConnection eager1 = EagerDBConnection.getInstance();
        eager1.connect();
        EagerDBConnection eager2 = EagerDBConnection.getInstance();
        System.out.println("Same instance? " + (eager1 == eager2));
        
        System.out.println("\n=== Testing Static Block Initialization ===");
        StaticBlockDBConnection static1 = StaticBlockDBConnection.getInstance();
        static1.connect();
        StaticBlockDBConnection static2 = StaticBlockDBConnection.getInstance();
        System.out.println("Same instance? " + (static1 == static2));
        
        System.out.println("\n=== Testing Lazy Initialization ===");
        LazyDBConnection lazy1 = LazyDBConnection.getInstance();
        lazy1.connect();
        LazyDBConnection lazy2 = LazyDBConnection.getInstance();
        System.out.println("Same instance? " + (lazy1 == lazy2));
        
        System.out.println("\n=== Testing Thread-Safe Initialization ===");
        ThreadSafeDBConnection threadSafe1 = ThreadSafeDBConnection.getInstance();
        threadSafe1.connect();
        ThreadSafeDBConnection threadSafe2 = ThreadSafeDBConnection.getInstance();
        System.out.println("Same instance? " + (threadSafe1 == threadSafe2));
        
        System.out.println("\n=== Testing Double-Checked Locking ===");
        DoubleCheckedDBConnection doubleChecked1 = DoubleCheckedDBConnection.getInstance();
        doubleChecked1.connect();
        DoubleCheckedDBConnection doubleChecked2 = DoubleCheckedDBConnection.getInstance();
        System.out.println("Same instance? " + (doubleChecked1 == doubleChecked2));
        
        // Testing that we cannot create new instances
        // EagerDBConnection eager3 = new EagerDBConnection(); // Error: constructor is private
    }
}

// 1. Eager Initialization Singleton
final class EagerDBConnection {
    private static final EagerDBConnection instance = new EagerDBConnection();
    
    private EagerDBConnection() {
        System.out.println("EagerDBConnection object created");
    }
    
    public static EagerDBConnection getInstance() {
        return instance;
    }
    
    public void connect() {
        System.out.println("Connected to database using Eager initialization");
    }
}

// 2. Static Block Initialization Singleton
final class StaticBlockDBConnection {
    private static StaticBlockDBConnection instance;
    
    private StaticBlockDBConnection() {
        System.out.println("StaticBlockDBConnection object created");
    }
    
    // Static block for exception handling
    static {
        try {
            instance = new StaticBlockDBConnection();
        } catch (Exception e) {
            throw new RuntimeException("Exception occurred in creating singleton instance");
        }
    }
    
    public static StaticBlockDBConnection getInstance() {
        return instance;
    }
    
    public void connect() {
        System.out.println("Connected to database using Static Block initialization");
    }
}

// 3. Lazy Initialization Singleton
final class LazyDBConnection {
    private static LazyDBConnection instance;
    
    private LazyDBConnection() {
        System.out.println("LazyDBConnection object created");
    }
    
    public static LazyDBConnection getInstance() {
        if (instance == null) {
            instance = new LazyDBConnection();
        }
        return instance;
    }
    
    public void connect() {
        System.out.println("Connected to database using Lazy initialization");
    }
}

// 4. Thread-Safe Singleton
final class ThreadSafeDBConnection {
    private static ThreadSafeDBConnection instance;
    
    private ThreadSafeDBConnection() {
        System.out.println("ThreadSafeDBConnection object created");
    }
    
    public static synchronized ThreadSafeDBConnection getInstance() {
        if (instance == null) {
            instance = new ThreadSafeDBConnection();
        }
        return instance;
    }
    
    public void connect() {
        System.out.println("Connected to database using Thread-Safe initialization");
    }
}

// 5. Double-Checked Locking Singleton
final class DoubleCheckedDBConnection {
    private static volatile DoubleCheckedDBConnection instance;
    
    private DoubleCheckedDBConnection() {
        System.out.println("DoubleCheckedDBConnection object created");
    }
    
    public static DoubleCheckedDBConnection getInstance() {
        if (instance == null) {
            synchronized (DoubleCheckedDBConnection.class) {
                if (instance == null) {
                    instance = new DoubleCheckedDBConnection();
                }
            }
        }
        return instance;
    }
    
    public void connect() {
        System.out.println("Connected to database using Double-Checked Locking");
    }
}