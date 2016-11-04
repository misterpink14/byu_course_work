package Shared.Communication.Result;

import java.util.List;

import Shared.Model.Field;

/**
 * For GetFields output
 * 
 * @author Benjamin Thompson
 *
 */
public class GetFields_Result
{
	Boolean success;
	private List<Field> fieldList;

	/**
	 * GetFields_Result Constructor
	 * 
	 * @param projectIDList
	 * @param fieldIDList
	 * @param fieldTitleList
	 */
	public GetFields_Result(Boolean success, List<Field> fieldList)
	{
		this.success = success;
		this.fieldList = fieldList;
	}
	
	/**
	 * Returns fieldList
	 * 
	 * @return the fieldList
	 */
	public List<Field> getFieldList()
	{
		return this.fieldList;
	}
	
	public Boolean getSuccess()
	{
		return this.success;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString()
	{
		if(this.fieldList == null || this.getFieldList().size() == 0)
		{
			return "FAILED\n";
		}
		StringBuilder sb = new StringBuilder();
		for (Field f: fieldList)
		{
			sb.append(f.getProject_id()).append('\n').append(f.getId()).append('\n').append(f.getTitle()).append('\n');
		}
		return sb.toString();
	}
	
	
	
	
}
