package Shared.Model;

/**
 * Field Class. Stores project's individual field information.
 * @author Benjamin Thompson
 *
 */
public class Field extends Parent
{

	private String title;
	private Integer xcoord;
	private Integer width;
	private String helphtml;
	private String knowndata;
	private Integer project_id;
	
	/**
	 * Field Constructor
	 * 
	 * @param id
	 * @param title
	 * @param xcoord
	 * @param helphtml
	 * @param knowndata
	 * @param project_id
	 */
	public Field(Integer id, String title, Integer xcoord, Integer width, String helphtml,
			String knowndata, Integer project_id)
	{
		super(id);
		this.title = title;
		this.xcoord = xcoord;
		this.width = width;
		this.helphtml = helphtml;
		this.knowndata = knowndata;
		this.project_id = project_id;
	}

	/**
	 * Field Constructor without id
	 * 
	 * @param title
	 * @param xcoord
	 * @param width
	 * @param helphtml
	 * @param knowndata
	 * @param project_id
	 */
	public Field( String title, Integer xcoord, Integer width, String helphtml,
			String knowndata, Integer project_id)
	{
		super(-1);
		this.title = title;
		this.xcoord = xcoord;
		this.width = width;
		this.helphtml = helphtml;
		this.knowndata = knowndata;
		this.project_id = project_id;
	}
	
	/**
	 * Returns title
	 * 
	 * @return title
	 */
	public String getTitle()
	{
		return title;
	}
	/**
	 * Set's title
	 * 
	 * @param title
	 */
	public void setTitle(String title)
	{
		this.title = title;
	}
	/**
	 * Returns x coordinate
	 * 
	 * @return xcoord
	 */
	public Integer getXcoord()
	{
		return xcoord;
	}
	/**
	 * Sets x coordinate
	 * 
	 * @param xcoord
	 */
	public void setXcoord(Integer xcoord)
	{
		this.xcoord = xcoord;
	}
	/**
	 * Returns width
	 * 
	 * @return width
	 */
	public Integer getWidth()
	{
		return width;
	}
	/**
	 * Sets width
	 * 
	 * @param width
	 */
	public void setWidth(Integer width)
	{
		this.width = width;
	}
	/**
	 * Returns Help html location
	 * 
	 * @return helphtml
	 */
	public String getHelphtml()
	{
		return helphtml;
	}
	/**
	 * Sets Help html location
	 * 
	 * @param helphtml
	 */
	public void setHelphtml(String helphtml)
	{
		this.helphtml = helphtml;
	}
	/**
	 * Returns Known data location
	 * 
	 * @return knowndata
	 */
	public String getKnowndata()
	{
		return knowndata;
	}
	/**
	 * Sets known data location
	 * 
	 * @param knowndata
	 */
	public void setKnowndata(String knowndata)
	{
		this.knowndata = knowndata;
	}
	/**
	 * Returns project id
	 * 
	 * @return project_id
	 */
	public Integer getProject_id()
	{
		return project_id;
	}
	/**
	 * Sets project id
	 * 
	 * @param project_id
	 */
	public void setProject_id(Integer project_id)
	{
		this.project_id = project_id;
	}
	
}