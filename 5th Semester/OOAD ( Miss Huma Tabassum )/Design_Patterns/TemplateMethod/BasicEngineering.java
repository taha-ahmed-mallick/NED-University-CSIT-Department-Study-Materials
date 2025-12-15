package TemplateMethod;

public abstract class BasicEngineering {
	//Making the method final to prevent overriding.
	public final void completeCourse() {
		//The course needs to be completed in the following sequence
		//1.Math-2.SoftSkills-3.Special Paper
		//Common Papers:
		completeMath();
		completeSoftSkills();
		//Specialization Paper:
		completeSpecialPaper();
	}
	
	private void completeMath() {
		System.out.println("1.Mathematics");
	}
	
	private void completeSoftSkills() {
		System.out.println("2.SoftSkills");
	}
	
	public abstract void completeSpecialPaper();

}
