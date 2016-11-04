package server.databaseaccess;

import static org.junit.Assert.*;

import java.sql.SQLException;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import Server.DatabaseAccess.FieldDBAccess;
import Server.DatabaseAccess.ImageDBAccess;
import Server.DatabaseAccess.ProjectDBAccess;
import Server.DatabaseAccess.Database.Database;
import Server.DatabaseAccess.Database.DatabaseException;
import Shared.Model.Field;
import Shared.Model.Image;
import Shared.Model.Project;


public class FieldDBAccessTest
{
	private Field f;
	private FieldDBAccess fdb;
	
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
	public static void tearDownAfterClass() throws Exception
	{	}

	@Before
	public void setUp() throws Exception
	{
		f = new Field("ftitle", 1, 1, "help", "known", -1);
		fdb = new FieldDBAccess();
	}

	@After
	public void tearDown() throws Exception
	{
	}

	@Test
	public void testCreateField()
	{
		try
		{
			fdb.CreateField(f);
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
			fdb.DeleteField(f);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(true);
	}

	@Test
	public void testGetProjectFields()
	{
		Project p = new Project("ptitle", 1, 1, 1);
		ProjectDBAccess pdb = new ProjectDBAccess();
		
		try
		{
			pdb.CreateProject(p);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		this.f.setProject_id(p.getId());
		
		try
		{
			fdb.CreateField(f);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		int count = -1;
		try
		{
			count = fdb.GetProjectFields(f.getProject_id()).size();
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			pdb.DeleteProject(p);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		pdb.getDb().close();
		
		try
		{
			fdb.DeleteField(f);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		
		assertTrue(count == 1);
	}
	
	@Test
	public void testGetImageFields()
	{
		ImageDBAccess idb = new ImageDBAccess();
		Image i = new Image("file", -1, 1);
		try
		{
			idb.CreateImage(i);
		} catch (SQLException | DatabaseException e1)
		{
			e1.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			fdb.CreateField(f);
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
			count = fdb.GetImageFields(i.getId()).size();
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
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		idb.getDb().close();

		
		try
		{
			fdb.DeleteField(f);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(count == 1);
	}
	
	@Test
	public void testGetAllFields()
	{
		int count1 = -1;
		try
		{
			count1 = fdb.GetAllFields().size();
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			fdb.CreateField(f);
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
			count = fdb.GetAllFields().size();
		} catch (SQLException e)
		{
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}

		try
		{
			fdb.DeleteField(f);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		assertTrue(count-1 == count1);
	}

	@Test
	public void testDeleteField()
	{
		try
		{
			fdb.CreateField(f);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			fdb.DeleteField(f);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}

		
		assertTrue(true);
	}

}
