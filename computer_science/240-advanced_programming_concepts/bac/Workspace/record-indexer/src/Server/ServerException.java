package Server;

@SuppressWarnings("serial")
public class ServerException extends Exception
{
	public ServerException() {
		return;
	}

	public ServerException(String message) {
		super(message);
	}

	public ServerException(Throwable cause) {
		super(cause);

	}

	public ServerException(String message, Throwable cause) {
		super(message, cause);
	}
}
