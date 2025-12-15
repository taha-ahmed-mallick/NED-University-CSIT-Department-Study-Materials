public class FactoryExample {
    public static void main (String args[]) {        
        Dialog windowsDialog = new WindowsDialog();
        windowsDialog.render();
        Dialog webDialog = new WebDialog();
        webDialog.render();
    }
}

interface Button {
    void render();
    void onClick();
}

class WindowsButton implements Button {
    public void render () {
        System.out.println("Window button rendered");
    }

    public void onClick () {
        System.out.println("Windows button clicked");
    }
}

class HTMLButton implements Button {
    public void render () {
        System.out.println("HTML Butoon rendered");
    }

    public void onClick () {
        System.out.println("HTML Button clicked");
    }
}

abstract class Dialog {
    // Factory Method
    public abstract Button createButton ();

    public void render () {
        System.out.println("Rendering dialog...");
        Button button = createButton();
        button.render();
        button.onClick();
        System.out.println("Dialog rendering completed");
    }
}

class WindowsDialog extends Dialog {
    @Override
    public Button createButton () {
        return new WindowsButton();
    }
}

class WebDialog extends Dialog {
    @Override
    public Button createButton () {
        return new HTMLButton();
    }
}