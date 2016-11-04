package Client.Communicator;
/**
 * Exceptions from ClientCommunicator class
 * 
 * @author Benjamin Thompson
 *
 */
@SuppressWarnings("serial")
public class ClientCommunicatorException extends Exception 
{
	public ClientCommunicatorException() {
		return;
	}

	// Probably won't bother with using these, unless I have time to add
	//	it in the end
	public ClientCommunicatorException(String message) {
		super(message);
	}

	public ClientCommunicatorException(Throwable cause) {
		super(cause);

	}

	public ClientCommunicatorException(String message, Throwable cause) {
		super(message, cause);
	}
}
