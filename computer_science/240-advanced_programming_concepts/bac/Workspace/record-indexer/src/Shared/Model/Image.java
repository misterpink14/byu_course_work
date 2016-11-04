package Shared.Model;


/**
 * Image Class. Stores Batch/Image location. May not use the records
 * 	variable. records will be a SortedMap
 * 
 * @author Benjamin Thompson
 *
 */
public class Image extends Parent
{
	private String file;
	private Integer projectID;
	private Integer userID;

	/**
	 * Image Constructor. records variable set to null.
	 * 
	 * @param id
	 * @param file
	 * @param projectID
	 * @param userID
	 */
	public Image(Integer id, String file, Integer projectID, Integer userID)
	{
		super(id);
		this.file = file;
		this.projectID = projectID;
		this.userID = userID;
	}
	
	/**
	 * Image Constructor. records variable set to null.
	 * 
	 * @param id
	 * @param file
	 * @param projectID
	 * @param userID
	 */
	public Image( String file, Integer projectID, Integer userID)
	{
		super(-1);
		this.file = file;
		this.projectID = projectID;
		this.userID = userID;
	}
	
	/**
	 * Default construct
	 */
	public Image()
	{
		super();
	}
	
	/**
	 * Returns filename
	 * 
	 * @return file
	 */
	public String getFile()
	{
		return file;
	}
	/**
	 * Sets filename
	 * 
	 * @param file
	 */
	public void setFile(String file)
	{
		this.file = file;
	}
	/**
	 * Returns project id
	 * 
	 * @return projectID
	 */
	public Integer getProjectID()
	{
		return projectID;
	}
	/**
	 * Return userID. 
	 * 
	 * @return userID
	 */
	public Integer getUserID()
	{
		return userID;
	}

	/**
	 * Sets userID
	 * 
	 * @param userID
	 */
	public void setUserID(Integer userID)
	{
		this.userID = userID;
	}

	/**
	 * Sets project id
	 * 
	 * @param projectID
	 */
	public void setProjectID(Integer projectID)
	{
		this.projectID = projectID;
	}

	/**
	 * Returns the Map of Records
	 * 
	 * @return records
	 */
	
}