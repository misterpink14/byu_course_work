
package Shared.Communication.Param;

/**
 * For Search input
 * 
 * @author Benjamin Thompson
 *
 */
public class Search_Param
{
	private String user;
	private String pass;
	private String fields;
	private String searchValues;
	
	
	/**
	 * Search Constructor
	 * 
	 * @param user
	 * @param pass
	 * @param fields
	 * @param searchValues
	 */
	public Search_Param(String user, String pass, String fields,
			String searchValues)
	{
		this.user = user;
		this.pass = pass;
		this.fields = fields;
		this.searchValues = searchValues;
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
	 * @return pass
	 */
	public String getPass()
	{
		return pass;
	}


	/**
	 * Returns fields
	 * 
	 * @return fields
	 */
	public String getFields()
	{
		return fields;
	}


	/**
	 * Returns searchValues
	 * 
	 * @return searchValues
	 */
	public String getSearchValues()
	{
		return searchValues;
	}
	
}
