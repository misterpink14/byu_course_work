/**
 * 
 */
package Shared.Model;

/**
 * User class. Contains user information.
 * 
 * @author Benjamin Thompson
 *
 */
public class User extends Parent 
{

	private String user;
	private String pass;
	private String first;
	private String last;
	private String email;
	private Integer indexed;

	/**
	 * Constructs a User
	 * 
	 * @param id
	 * @param user
	 * @param pass
	 * @param first
	 * @param last
	 * @param email
	 * @param indexed
	 */
	public User(Integer id, String user, String pass, String first,
			String last, String email, Integer indexed)
	{
		super(id);
		this.user = user;
		this.pass = pass;
		this.first = first;
		this.last = last;
		this.email = email;
		this.indexed = indexed;
	}
	
	/**
	 * Construcst a user without an id
	 * 
	 * @param user
	 * @param pass
	 * @param first
	 * @param last
	 * @param email
	 * @param indexed
	 */
	public User(String user, String pass, String first,
			String last, String email, Integer indexed)
	{
		super();
		this.user = user;
		this.pass = pass;
		this.first = first;
		this.last = last;
		this.email = email;
		this.indexed = indexed;
	}
	
	/**
	 * Default Constructor
	 * 
	 */
	public User()
	{
		super();
	}
	
	/**
	 * Constructs a user with only an id
	 * 
	 * @param id
	 */
	public User(Integer id)
	{
		super(id);
	}
	
	public User(String user, String pass, String first,
			String last, String email)
	{
		super();
		this.user = user;
		this.pass = pass;
		this.first = first;
		this.last = last;
		this.email = email;
		this.indexed = 0;
	}


	/**
	 * Returns the username
	 * 
	 * @return String user's username
	 */
	public String getUser()
	{
		return user;
	}
	
	/**
	 * Sets the username
	 * 
	 * @param user Strung user's username
	 */
	public void setUser(String user)
	{
		this.user = user;
	}
	
	/**
	 * Returns the password
	 * 
	 * @return String user's password
	 */
	public String getPass()
	{
		return pass;
	}
	
	/**
	 * Sets the password
	 * 
	 * @param pass String user's password
	 */
	public void setPass(String pass)
	{
		this.pass = pass;
	}
	
	/**
	 * Returns the first name
	 * 
	 * @return String user's first name
	 */
	public String getFirst()
	{
		return first;
	}
	
	/**
	 * Sets first name
	 * 
	 * @param first String user's first name
	 */
	public void setFirst(String first)
	{
		this.first = first;
	}
	
	/**
	 * Returns last name
	 * 
	 * @return String user's last name
	 */
	public String getLast()
	{
		return last;
	}
	
	/**
	 * Sets last name
	 * 
	 * @param last String user's last name
	 */
	public void setLast(String last)
	{
		this.last = last;
	}
	
	/**
	 * Returns email
	 * 
	 * @return String user's email
	 */
	public String getEmail()
	{
		return email;
	}
	
	/**
	 * Sets email
	 * 
	 * @param email String user's email
	 */
	public void setEmail(String email)
	{
		this.email = email;
	}
	
	/**
	 * Returns number of indexed
	 * 
	 * @return Integer user's number of indexed
	 */
	public Integer getIndexed()
	{
		return indexed;
	}
	
	/**
	 * Sets number of indexed
	 * 
	 * @param indexed Integer user's number of indexed
	 */
	public void setIndexed(Integer indexed)
	{
		this.indexed = indexed;
	}
	
}
