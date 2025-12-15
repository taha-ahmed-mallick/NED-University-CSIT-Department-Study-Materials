package TemplateMethod;

public class TemplateMethodExample {

	public static void main(String[] args) {
		System.out.println("***Template Method Pattern Demo***\n");
		BasicEngineering preferredCourse = new ComputerScience();
		System.out.println("Computer Science courses will be completed in the following order:");
		preferredCourse.completeCourse();
		System.out.println();
		preferredCourse = new Electronics();
		System.out.println("Electronics courses will be completed in the following order:");
		preferredCourse.completeCourse();
	}

}
