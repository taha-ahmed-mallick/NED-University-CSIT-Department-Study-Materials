package ChainOfResponsibility;

interface Receiver {
	boolean handleMessage(Message message);
	void nextErrorHandler(Receiver nextReceiver);
}
