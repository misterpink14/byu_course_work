package Shared.Communication.Param;

/**
 * For GetSampleImage input
 * 
 * @author Benjamin Thompson
 *
 */
public class GetSampleImage_Param
{
	private String user;
	private String pass;
	private Integer projectID;

	/**
	 * GetSampleImage_Param Constructor
	 * 
	 * @param user
	 * @param pass
	 * @param projectID
	 */
	public GetSampleImage_Param(String user, String pass, Integer projectID)
	{
		this.user = user;
		this.pass = pass;
		this.projectID = projectID;
	}
	/**
	 * Returns user name
	 * 
	 * @return the user
	 */
	public String getUser()
	{
		return user;
	}
	/**
	 * Returns password
	 * 
	 * @return the pass
	 */
	public String getPass()
	{
		return pass;
	}
	/**
	 * Returns projectID
	 * 
	 * @return the projectID
	 */
	public Integer getProjectID()
	{
		return projectID;
	}
	
}
