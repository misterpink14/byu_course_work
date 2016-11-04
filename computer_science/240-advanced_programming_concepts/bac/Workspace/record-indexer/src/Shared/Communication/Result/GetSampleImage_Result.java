package Shared.Communication.Result;

/**
 * For GetSampleImage output
 * 
 * @author Benjamin Thompson
 *
 */
public class GetSampleImage_Result
{
	private String file;
	private Boolean success;

	/**
	 * GetSampleImage_Result Constructor
	 * 
	 * @param success
	 * @param file
	 */
	public GetSampleImage_Result(Boolean success, String file)
	{
		this.file = file;
		this.success = success;
	}

	/**
	 * Returns file location
	 * 
	 * @return file
	 */
	public String getFile()
	{
		return file;
	}
	
	public void setUrl(String url)
	{
		file = url + file;
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
		if (!success || this.file == null)
		{
			return "FAILED\n";
		}
		return String.format("%s\n", this.file);
	}

}
