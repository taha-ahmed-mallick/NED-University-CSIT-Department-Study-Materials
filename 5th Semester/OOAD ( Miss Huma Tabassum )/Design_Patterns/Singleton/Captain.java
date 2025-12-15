package Singleton;

final class Captain {
	private static Captain captain;
	
	//We make the constructor private to prevent the use of "new"
	private Captain() {}
	
	public static Captain getCaptain() {
		//Lazy initialization
		if (captain == null) {
			captain = new Captain();
			System.out.println("New captain is elected for your team.");
		}
		else {
			System.out.print("You already have a captain for your team.");
			System.out.println("Send him for the toss.");
		}
		return captain;
	}
}

//We cannot extend Captain class.The constructor is private in this case.
//class B extends Captain{}// error
