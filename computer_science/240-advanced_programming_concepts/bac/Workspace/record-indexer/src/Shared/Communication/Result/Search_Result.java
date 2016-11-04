
package Shared.Communication.Result;

import java.util.List;
import java.util.Map;

import Shared.Model.Image;
import Shared.Model.Record;

/**
 * For Search output
 * 
 * @author Benjamin Thompson
 *
 */
public class Search_Result
{
	public Boolean success;
	public Map<Image, List<Record>> resultsList;

	/**
	 * @param success
	 * @param resultsList
	 */
	public Search_Result(Boolean success, Map<Image, List<Record>> resultsList)
	{
		this.success = success;
		this.resultsList = resultsList;
	}
	
	/**
	 * @return the success
	 */
	public Boolean getSuccess()
	{
		return success;
	}
	
	public void updateURL (String url)
	{
		for (Map.Entry<Image, List<Record>> temp: resultsList.entrySet())
		{
			temp.getKey().setFile(url+temp.getKey().getFile());
		}
	}

	/**
	 * @return the resultsList
	 */
	public Map<Image, List<Record>> getResultsList()
	{
		return resultsList;
	}

	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString()
	{
		StringBuilder sb = new StringBuilder();
		if(this.resultsList == null)
		{
			return "FAILED\n";
		}
		for(Map.Entry<Image, List<Record>> temp : this.resultsList.entrySet())
		{
			Image i = temp.getKey();
			for (Record r: temp.getValue())
			{
				sb.append(i.getId().intValue()).append('\n').append(i.getFile()).append('\n').append(r.getRow().intValue()).append('\n').append(r.getFieldID().intValue()).append('\n');
			}
		}
		return sb.toString();
	}
	
}
