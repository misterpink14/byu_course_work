package Shared.Communication.Param;

/**
 * For GetProjects input
 * 
 * @author Benjamin Thompson
 *
 */
public class GetProjects_Param
{
	private String user;
	private String pass;
	
	/**
	 * GetProjects_Param Constructor
	 * 
	 * @param user
	 * @param pass
	 */
	public GetProjects_Param(String user, String pass)
	{
		this.user = user;
		this.pass = pass;
	}

	/**
	 * Returns user name
	 * 
	 * @return name
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
