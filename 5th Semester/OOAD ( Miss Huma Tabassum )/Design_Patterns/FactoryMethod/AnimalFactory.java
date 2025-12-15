package FactoryMethod;

abstract class AnimalFactory {
	public abstract Animal createAnimal();
}

class DogFactory extends AnimalFactory {
	public Animal createAnimal() {
		//Creating a Dog
		return new Dog();
	}
}

class TigerFactory extends AnimalFactory {
	public Animal createAnimal() {
		//Creating a Tiger
		return new Tiger();
	}
}