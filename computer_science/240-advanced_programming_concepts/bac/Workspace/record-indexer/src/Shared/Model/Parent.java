package Shared.Model;

/**
 * Parent Class. Super to the User, Project, Field, Image, and Record
 *	Classes. Stores Integer id, -1 or NULL if object has no id.
 * 
 * @author Benjamin Thompson
 *
 */
public class Parent
{
	private Integer id;
	
	/**
	 * Parent Constructor
	 * 
	 * @param id
	 */
	public Parent(Integer id)
	{
		this.id = id;
	}

	/**
	 * Default constructor
	 * 
	 */
	public Parent()
	{	}

	/**
	 * Returns id
	 * 
	 * @return id
	 */
	public Integer getId()
	{
		return id;
	}
	
	/**
	 * Sets id
	 * 
	 * @param id
	 */
	public void setId(Integer id)
	{
		this.id = id;
	}
}
