package FactoryMethod;

interface Animal {
	void speak();
	void preferredAction();
}

class Dog implements Animal {
	public void speak() {
			System.out.println("Dog says: Bow-Wow.");
	}
	public void preferredAction() {
			System.out.println("Dogs prefer barking...\n");
	}
}


class Tiger implements Animal {
	public void speak() {
		System.out.println("Tiger says: Halum.");
	}
	public void preferredAction() {
		System.out.println("Tigers prefer hunting...\n");
	}
}