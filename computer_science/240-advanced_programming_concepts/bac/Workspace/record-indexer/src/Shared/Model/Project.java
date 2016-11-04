/**
 * 
 */
package Shared.Model;

/**
 * Project class. Stores Project main project information. Image and Field
 * 	information stored in the Image and Field Classes.
 * 
 * @author Benjamin Thompson
 *
 */
public class Project extends Parent
{
	private String title;
	private Integer records;
	private Integer firsty;
	private Integer height;
	
	/**
	 * Project Constructor
	 * 
	 * @param id
	 * @param title
	 * @param records
	 * @param firsty
	 * @param height
	 */
	public Project(Integer id, String title, Integer records, Integer firsty,
			Integer height)
	{
		super(id);
		this.title = title;
		this.records = records;
		this.firsty = firsty;
		this.height = height;
	}
	
	/**
	 * Project Constructor without id
	 * 
	 * @param title
	 * @param records
	 * @param firsty
	 * @param height
	 */
	public Project(String title, Integer records, Integer firsty,
			Integer height)
	{
		super();
		this.title = title;
		this.records = records;
		this.firsty = firsty;
		this.height = height;
	}
	
	/**
	 * Default Constructor
	 */
	public Project()
	{
		super();
	}
	
	/**
	 * Returns project title
	 * 
	 * @return title
	 */
	public String getTitle()
	{
		return title;
	}
	/**
	 * Sets project title
	 * 
	 * @param title
	 */
	public void setTitle(String title)
	{
		this.title = title;
	}
	/**
	 * Returns number of records
	 * 
	 * @return records
	 */
	public Integer getRecords()
	{
		return records;
	}
	/**
	 * Sets number of records
	 * 
	 * @param records
	 */
	public void setRecords(Integer records)
	{
		this.records = records;
	}
	/**
	 * Returns first y value
	 * 
	 * @return firsty
	 */
	public Integer getFirsty()
	{
		return firsty;
	}
	/**
	 * Sets first y value
	 * 
	 * @param firsty
	 */
	public void setFirsty(Integer firsty)
	{
		this.firsty = firsty;
	}
	/**
	 * Returns height of fields
	 * 
	 * @return height
	 */
	public Integer getHeight()
	{
		return height;
	}
	/**
	 * Sets height of fields
	 * 
	 * @param height
	 */
	public void setHeight(Integer height)
	{
		this.height = height;
	}
	
}
