package Shared.Communication.Result;

/**
 * For ValidateUser output
 * 
 * @author Benjamin Thompson
 *
 */
public class ValidateUser_Result
{
	private String success;
	private String first;
	private String last;
	private Integer records;
	
	
	/** 
	 * ValidateUser_Result Constructor
	 * 
	 * @param success
	 * @param first
	 * @param last
	 * @param records
	 */
	public ValidateUser_Result(String success, String first, String last,
			Integer records)
	{
		this.success = success;
		this.first = first;
		this.last = last;
		this.records = records;
	}
	
	public ValidateUser_Result(String success)
	{
		this.success = success;
		this.first = null;
		this.last = null;
		this.records = null;
	}

	/**
	 * Returns success status
	 * 
	 * @return success
	 */
	public String getSuccess()
	{
		return success;
	}


	/**
	 * Returns first name
	 * 
	 * @return first
	 */
	public String getFirst()
	{
		return first;
	}


	/**
	 * Returns last name
	 * 
	 * @return last
	 */
	public String getLast()
	{
		return last;
	}


	/**
	 * Returns records indexed
	 * 
	 * @return records
	 */
	public Integer getRecords()
	{
		return records;
	}


	@Override
	public String toString()
	{
		if (this.first == null)
		{
			return String.format( "%s", this.success );
		}
		return String.format( "%s\n%s\n%s\n%d\n", success, this.first, this.last, this.records.intValue() );
	}
	
}
