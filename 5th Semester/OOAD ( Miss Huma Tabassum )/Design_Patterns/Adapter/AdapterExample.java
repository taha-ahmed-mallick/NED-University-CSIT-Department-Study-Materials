package Adapter;

public class AdapterExample {

	public static void main(String[] args) {
			System.out.println("***Adapter Pattern Demo***\n");
			CalculatorAdapter calculatorAdapter = new CalculatorAdapter();
			Triangle t = new Triangle(20,10);
			System.out.println("Area of Triangle is " + calculatorAdapter.getArea(t) + " Square unit");
	}
}
