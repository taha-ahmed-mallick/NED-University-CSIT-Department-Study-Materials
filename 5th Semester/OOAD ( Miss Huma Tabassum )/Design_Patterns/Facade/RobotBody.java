package Facade;

public class RobotBody {
	public static void createRobot() {
		System.out.println(" Refer the manual before creation of a robot.");
	}
	
	public void createHands() {
		System.out.println(" Hands manufactured.");
	}
	
	public void createBody() {
		System.out.println(" Body is created.");
	}
	
	public static void destroyRobot() {
		System.out.println(" Refer the manual before destroying of a robot.");
	}
	
	public void destroyHands() {
		System.out.println(" The robot's hands are destroyed.");
	}
	
	public void destroyBody() {
		System.out.println(" The robot's body is destroyed.");
	}
}
