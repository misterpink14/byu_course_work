package server.databaseaccess;
import static org.junit.Assert.*;

import java.sql.SQLException;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import Server.DatabaseAccess.UserDBAccess;
import Server.DatabaseAccess.Database.Database;
import Server.DatabaseAccess.Database.DatabaseException;
import Shared.Model.User;

/**
 * @author Benjamin Thompson
 *
 */
public class UserDBAccessTest
{
	
	private static User u;
	private static UserDBAccess udb;

	@BeforeClass
	public static void setUpBeforeClass()
	{
		try
		{
			Database.init();
		} catch (ClassNotFoundException e)
		{
			e.printStackTrace();
		}
	}

	@AfterClass
	public static void tearDownAfterClass()
	{
	}

	@Before
	public void setUp() 
	{
		u = new User("ben","thompson","ben","thompson","email");
		udb = new UserDBAccess();
	}

	@After
	public void tearDown()
	{
	}

	@Test
	public void testCreateUser()
	{
		try
		{
			udb.CreateUser(u);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			udb.DeleteUser(u);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(true);
	}
	
	@Test
	public void testGetUserByID()
	{
		try
		{
			udb.CreateUser(u);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			udb.GetUser(u);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			udb.DeleteUser(u);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(true);
	}
	
	@Test
	public void testGetUserByLogin()
	{
		try
		{
			udb.CreateUser(u);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		User us = new User();
		us.setUser("ben");
		us.setPass("thompson");
		try
		{
			udb.GetUser(us);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}

		try
		{
			udb.DeleteUser(u);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(true);
	}
	
	@Test
	public void testGetAllUsers()
	{
		int count1 = -1;
		try
		{
			count1 = udb.GetAllUsers().size();
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		try
		{
			udb.CreateUser(u);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		int count = -1;
		try
		{
			count = udb.GetAllUsers().size();
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			udb.DeleteUser(u);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(count - count1 == 1);
	}
	
	@Test
	public void testUpdateUser()
	{
		try
		{
			udb.CreateUser(u);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		u.setFirst("Benjamin");
		
		try
		{
			udb.UpdateUser(u);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			udb.GetUser(u);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			udb.DeleteUser(u);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		assertTrue(u.getFirst().equals("Benjamin"));
	}
	
	@Test
	public void testDeleteUser()
	{
		int count1 = -1;
		try
		{
			count1 = udb.GetAllUsers().size();
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			udb.CreateUser(u);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		try
		{
			udb.DeleteUser(u);
		}
		catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		int count = -1;
		try
		{
			count = udb.GetAllUsers().size();
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(count == count1);
	}

}
