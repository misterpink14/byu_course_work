package Shared.Communication.Param;

/**
 * For DownloadBatch input
 * 
 * @author Benjamin Thompson
 *
 */
public class DownloadBatch_Param
{
	private String user;
	private String pass;
	private Integer projectID;
	/**
	 * DownloadBatch_Param Constructor
	 * 
	 * @param user
	 * @param pass
	 * @param projectID
	 */
	public DownloadBatch_Param(String user, String pass, Integer projectID)
	{
		super();
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
