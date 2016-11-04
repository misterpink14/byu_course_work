package server.databaseaccess;

import static org.junit.Assert.*;

import java.sql.SQLException;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import Server.DatabaseAccess.ImageDBAccess;
import Server.DatabaseAccess.Database.Database;
import Server.DatabaseAccess.Database.DatabaseException;
import Shared.Model.Image;

public class ImageDBAccessTest
{
	private static Image i;
	private static ImageDBAccess idb;

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
	public void setUp() throws Exception
	{
		i = new Image("filename", -1, 2);
		idb = new ImageDBAccess();
	}

	@After
	public void tearDown() throws Exception
	{	}

	@Test
	public void testCreateImage()
	{
		try
		{
			idb.CreateImage(i);
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
			idb.DeleteImage(i);
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
		
		assertTrue(true);
	}
	
	@Test
	public void testGetImage()
	{
		try
		{
			idb.CreateImage(i);
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
			idb.GetImage(i);
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
			idb.DeleteImage(i);
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
		assertTrue(true);
	}

	@Test
	public void testGetProjectImages()
	{
		try
		{
			idb.CreateImage(i);
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
			count = idb.GetProjectImages(-1).size();
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}

		try
		{
			idb.DeleteImage(i);
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
		assertTrue(count == 1);
	}
	
	@Test
	public void testGetUserImages()
	{
		try
		{
			idb.CreateImage(i);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		Image im = null;
		try
		{
			im = idb.GetUserImage(2);
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
			idb.DeleteImage(i);
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
		assertTrue(im.getId().intValue() == i.getId().intValue());
	}
	
	@Test
	public void testGetAllImages()
	{
		int count1 = -1;
		try
		{
			count1 = idb.GetAllImages().size();
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
			idb.CreateImage(i);
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
			count = idb.GetAllImages().size();
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
			idb.DeleteImage(i);
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
		assertTrue(count-1 == count1);
	}
	
	@Test
	public void testUpdateImage()
	{
		try
		{
			idb.CreateImage(i);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		i.setFile("fname");
		
		try
		{
			idb.UpdateImage(i);
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
			idb.GetImage(i);
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
			idb.DeleteImage(i);
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
		assertTrue(i.getFile().equals("fname"));
	}

	@Test
	public void testDeleteImage()
	{
		int count1 = -1;
		try
		{
			count1 = idb.GetAllImages().size();
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
			idb.CreateImage(i);
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
			idb.DeleteImage(i);
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
			count = idb.GetAllImages().size();
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