package Shared.Communication.Param;

/**
 * For Validate User input
 * 
 * @author Benjamin Thompson
 *
 */
public class ValidateUser_Param
{
	private String user;
	private String pass;
	
	/**
	 * ValidateUser_Param Constructor
	 * 
	 * @param user
	 * @param pass
	 */
	public ValidateUser_Param(String user, String pass)
	{
		super();
		this.user = user;
		this.pass = pass;
	}
	
	/**
	 * Returns user name
	 * 
	 * @return user
	 */
	public String getUser()
	{
		return user;
	}
	
	/**
	 * Returns password
	 * 
	 * @return password
	 */
	public String getPass()
	{
		return pass;
	}
	
	

}
