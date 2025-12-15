public class Demo {
    public static void main(String[] args) {
        DamageHandler shield = new MagicShield();
        DamageHandler armor = new IronArmor();
        DamageHandler body = new PlayerBody();

        // Chain them: Shield -> Armor -> Body
        shield.setNext(armor);
        armor.setNext(body);
        shield.handleDamage(80); 


        EnemyFactory factory = new EnemyFactory();
        Enemy e1 = factory.createEnemy("Forest");
        e1.attack();

        GameEntity hero = new Hero();
        hero.dailyRoutine();

        // Developer doesn't need to know about Lighting or Sound classes
        GameEngineFacade engine = new GameEngineFacade();
        engine.renderScene();
    }
}

// 1. Abstract Handler
abstract class DamageHandler {
    protected DamageHandler nextHandler;

    public void setNext(DamageHandler nextHandler) {
        this.nextHandler = nextHandler;
    }

    public abstract void handleDamage(int amount);
}

// 2. Concrete Handler: Shield
class MagicShield extends DamageHandler {
    public void handleDamage(int amount) {
        int absorbed = 50; 
        System.out.println("Magic Shield tries to absorb " + amount + " damage.");
        
        if (amount <= absorbed)
            System.out.println("Shield absorbed all damage!");
        else {
            int remaining = amount - absorbed;
            System.out.println("Shield broke! Passing " + remaining + " damage to Armor.");
            if (nextHandler != null) nextHandler.handleDamage(remaining);
        }
    }
}

class IronArmor extends DamageHandler {
    public void handleDamage(int amount) {
        int absorbed = 20;
        System.out.println("Iron Armor tries to block " + amount + " damage.");

        if (amount <= absorbed)
            System.out.println("Armor blocked all damage!");
        else {
            int remaining = amount - absorbed;
            System.out.println("Armor pierced! Passing " + remaining + " damage to Body.");
            if (nextHandler != null) nextHandler.handleDamage(remaining);
        }
    }
}

// Body (Final health)
class PlayerBody extends DamageHandler {
    public void handleDamage(int amount) {
        System.out.println("Ouch! Player took " + amount + " damage to Health.");
    }
}


// 1. Common Interface
interface Enemy {
    void attack();
}

// 2. Concrete Classes
class Goblin implements Enemy {
    public void attack() { System.out.println("Goblin attacks with a club!"); }
}

class Shark implements Enemy {
    public void attack() { System.out.println("Shark bites!"); }
}

// 3. Factory Class
class EnemyFactory {
    public Enemy createEnemy(String environment) {
        if (environment.equalsIgnoreCase("Forest"))
            return new Goblin();
        else if (environment.equalsIgnoreCase("Ocean"))
            return new Shark();
        else
            throw new IllegalArgumentException("Unknown environment");
    }
}


// 1. Abstract Base Template Class
abstract class GameEntity {
    
    public final void dailyRoutine() {
        wakeUp();   
        performAction();   // Unique (Abstract)
        sleep();  
    }

    private void wakeUp() {
        System.out.println("Waking up and stretching...");
    }

    private void sleep() {
        System.out.println("Going to sleep to recover health.");
    }

    protected abstract void performAction();
}

// 2. Concrete Class: Hero
class Hero extends GameEntity {
    @Override
    protected void performAction() {
        System.out.println(">> Hero is fighting monsters!");
    }
}

// 3. Concrete Class: NPC
class NPC extends GameEntity {
    @Override
    protected void performAction() {
        System.out.println(">> NPC is selling potions.");
    }
}


// 1. Complex Subsystems
class Lighting {
    public void calculateShadows() { System.out.println("Calculating shadows..."); }
}
class Sound {
    public void sync() { System.out.println("Syncing audio..."); }
}
class Renderer {
    public void drawFrame() { System.out.println("Drawing pixels..."); }
}

// 2. The Facade (Clean interface)
class GameEngineFacade {
    private Lighting lights;
    private Sound sound;
    private Renderer renderer;

    public GameEngineFacade() {
        this.lights = new Lighting();
        this.sound = new Sound();
        this.renderer = new Renderer();
    }

    // One simple method calls all the complex ones
    public void renderScene() {
        lights.calculateShadows();
        sound.sync();
        renderer.drawFrame();
        System.out.println("Scene Rendered Successfully!");
    }
}