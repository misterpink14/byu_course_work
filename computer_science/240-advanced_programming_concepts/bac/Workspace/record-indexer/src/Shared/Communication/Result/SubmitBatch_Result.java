package Shared.Communication.Result;

/**
 * For SubmitBatch output
 * 
 * @author Benjamin Thompson
 *
 */
public class SubmitBatch_Result
{
	private Boolean success;

	/**
	 * SubmitBatch_Result Constructor
	 * 
	 * @param success
	 */
	public SubmitBatch_Result(Boolean success)
	{
		this.success = success;
	}

	/**
	 * Returns success status
	 * 
	 * @return the success
	 */
	public Boolean getSuccess()
	{
		return success;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString()
	{
		return success? "TRUE\n":"FAILED\n";
	}

}
