package Shared.Communication.Result;

import java.util.List;

import Shared.Model.Field;

/**
 * For DownloadBatch output
 * 
 * @author Benjamin Thompson
 *
 */
public class DownloadBatch_Result
{
	private Boolean success;
	private Integer batchID;
	private Integer projectID;
	private String file;
	private Integer ycoord;
	private Integer height;
	private Integer records;
	private Integer fields;
	private List<Field> fieldList;
	
	
	/**
	 * DownloadBatch_Result Constructor
	 * 
	 * @param batchID
	 * @param projectID
	 * @param imageURL
	 * @param ycoord
	 * @param height
	 * @param records
	 * @param fields
	 * @param fieldList
	 */
	public DownloadBatch_Result(Boolean success, Integer batchID, Integer projectID,
			String imageURL, Integer ycoord, Integer height, Integer records,
			Integer fields, List<Field> fieldList)
	{
		super();
		this.success = success;
		this.batchID = batchID;
		this.projectID = projectID;
		this.file = imageURL;
		this.ycoord = ycoord;
		this.height = height;
		this.records = records;
		this.fields = fields;
		this.fieldList = fieldList;
	}
	/**
	 * Returns success status
	 * 
	 * @return success
	 */
	public Boolean getSuccess()
	{
		return success;
	}
	/**
	 * Returns imageID
	 * 
	 * @return the batchID
	 */
	public Integer getBatchID()
	{
		return batchID;
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
	/**
	 * Returns file location
	 * 
	 * @return the imageURL
	 */
	public String getFile()
	{
		return file;
	}
	public void setBaseUrl(String url)
	{
		this.file = url + this.file;
		for (Field f: this.fieldList)
		{
			String help = f.getHelphtml();
			f.setHelphtml(url + help);
			if(f.getKnowndata() != null)
			{
				String known = f.getKnowndata();
				f.setKnowndata(url + known);
			}
		}
	}
	/**
	 * Returns first y coord
	 * 
	 * @return the ycoord
	 */
	public Integer getYcoord()
	{
		return ycoord;
	}
	/**
	 * Returns image height
	 * 
	 * @return the height
	 */
	public Integer getHeight()
	{
		return height;
	}
	/**
	 * Returns numbet of records
	 * 
	 * @return the records
	 */
	public Integer getRecords()
	{
		return records;
	}
	/**
	 * Returns number of fields
	 * 
	 * @return the fields
	 */
	public Integer getFields()
	{
		return fields;
	}
	/**
	 * Returns fieldList
	 * 
	 * @return the fieldList
	 */
	public List<Field> getFieldList()
	{
		return fieldList;
	}
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString()
	{
		if(!this.success)
		{
			return "FAILED\n";
		}
		StringBuilder sb = new StringBuilder();
		sb.append(this.batchID.intValue()).append('\n').append(this.projectID.intValue()).append('\n')
			.append(this.file).append('\n').append(this.ycoord.intValue()).append('\n')
			.append(this.height.intValue()).append('\n').append(this.records.intValue()).append('\n')
			.append(this.fields.intValue()).append('\n');
		int fieldNum = 1;
		for (Field f: this.fieldList)
		{
			sb.append(f.getId().intValue()).append('\n').append(fieldNum).append('\n')
				.append(f.getTitle()).append('\n').append(f.getHelphtml())
				.append('\n').append(f.getXcoord().intValue()).append('\n').append(f.getWidth().intValue())
				.append('\n');
			if (f.getKnowndata() != null)
			{
				sb.append(f.getKnowndata()).append('\n');
			}
			fieldNum++;
		}
		
		return sb.toString();
	}
	
}
