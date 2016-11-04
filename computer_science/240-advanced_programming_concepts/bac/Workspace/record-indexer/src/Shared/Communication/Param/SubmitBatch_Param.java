package Shared.Communication.Param;

/**
 * For SubmitBatch input
 * 
 * @author Benjamin Thompson
 *
 */
public class SubmitBatch_Param
{
	private String user;
	private String pass;
	private Integer imageID;
	private String fieldValues;
	
	/**
	 * SubmitBatch_Param Constructor
	 * 
	 * @param user
	 * @param pass
	 * @param imageID
	 * @param fieldValues
	 */
	public SubmitBatch_Param(String user, String pass, Integer imageID,
			String fieldValues)
	{
		super();
		this.user = user;
		this.pass = pass;
		this.imageID = imageID;
		this.fieldValues = fieldValues;
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
	 * Returns imageID
	 * 
	 * @return the imageID
	 */
	public Integer getImageID()
	{
		return imageID;
	}
	/**
	 * Returns fieldVales
	 * 
	 * @return the fieldValues
	 */
	public String getFieldValues()
	{
		return fieldValues;
	}
	

}
