package Server.DatabaseAccess.Database;

/**
 * Exceptions from the Database class
 * 
 * @author Benjamin Thompson
 *
 */
@SuppressWarnings("serial")
public class DatabaseException extends Exception 
{

	public DatabaseException() {
		return;
	}

	// Probably won't bother with using these, unless I have time to add
	//	it in the end
	public DatabaseException(String message) {
		super(message);
	}

	public DatabaseException(Throwable cause) {
		super(cause);

	}

	public DatabaseException(String message, Throwable cause) {
		super(message, cause);
	}

}