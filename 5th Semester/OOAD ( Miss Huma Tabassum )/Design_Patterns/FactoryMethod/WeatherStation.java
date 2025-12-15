import java.util.List;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {

        WeatherStationController ws = WeatherStationController.getInstance();

        ws.addSensor("temperature");
        ws.addSensor("humidity");
        ws.addSensor("pressure");
        ws.addSensor("wind");

        WeatherStationFacade facade = new WeatherStationFacade();
        WeatherData data = facade.getWeatherReport();

        System.out.println("Temperature: " + data.temperature);
        System.out.println("Humidity: " + data.humidity);
        System.out.println("Pressure: " + data.pressure);
        System.out.println("Wind: " + data.windSpeed);
    }
}


abstract class Sensor {

    // Template Method
    public final double collect() {
        System.out.println("Initializing sensor...");
        double value = readValue();  // customizable step
        System.out.println("Finalizing sensor...\n");
        return value;
    }

    protected abstract double readValue(); // Subclasses must define this
}

class TemperatureSensor extends Sensor {
    @Override
    protected double readValue() {
        return 25.5;
    }
}

class HumiditySensor extends Sensor {
    @Override
    protected double readValue() {
        return 60.1;
    }
}

class PressureSensor extends Sensor {
    @Override
    protected double readValue() {
        return 1013.2;
    }
}

class WindSensor extends Sensor {
    @Override
    protected double readValue() {
        return 12.8;
    }
}

class SensorFactory {

    public Sensor createSensor(String type) {
        return switch (type) {
            case "temperature" -> new TemperatureSensor();
            case "humidity" -> new HumiditySensor();
            case "pressure" -> new PressureSensor();
            case "wind" -> new WindSensor();
            default -> throw new IllegalArgumentException("Unknown sensor type");
        };
    }
}

class WeatherStationController {

    private static WeatherStationController instance;

    private SensorFactory factory = new SensorFactory();
    private List<Sensor> sensors = new ArrayList<>();

    private WeatherStationController() {}

    public static WeatherStationController getInstance() {
        if (instance == null) {
            instance = new WeatherStationController();
        }
        return instance;
    }

    public void addSensor(String type) {
        sensors.add(factory.createSensor(type));
    }

    public WeatherData collectAllData() {

        double temp = 0, hum = 0, pres = 0, wind = 0;

        for (Sensor s : sensors) {
            double value = s.collect();

            if (s instanceof TemperatureSensor) temp = value;
            else if (s instanceof HumiditySensor) hum = value;
            else if (s instanceof PressureSensor) pres = value;
            else if (s instanceof WindSensor) wind = value;
        }

        return new WeatherData(temp, hum, pres, wind);
    }
}

class WeatherStationFacade {

    private WeatherStationController controller = WeatherStationController.getInstance();

    public WeatherData getWeatherReport() {
        return controller.collectAllData();
    }
}

class WeatherData {
    public double temperature;
    public double humidity;
    public double pressure;
    public double windSpeed;

    public WeatherData(double t, double h, double p, double w) {
        this.temperature = t;
        this.humidity = h;
        this.pressure = p;
        this.windSpeed = w;
    }
}