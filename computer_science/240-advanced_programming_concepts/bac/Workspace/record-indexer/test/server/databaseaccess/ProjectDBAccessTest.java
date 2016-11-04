package server.databaseaccess;

import static org.junit.Assert.*;

import java.sql.SQLException;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import Server.DatabaseAccess.ProjectDBAccess;
import Server.DatabaseAccess.Database.Database;
import Server.DatabaseAccess.Database.DatabaseException;
import Shared.Model.Project;

public class ProjectDBAccessTest
{

	private Project p;
	private ProjectDBAccess pdb;

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
		p = new Project("title", 1, 1, 1);
		pdb = new ProjectDBAccess();
	}

	@After
	public void tearDown()
	{	}

	@Test
	public void testCreateProject()
	{
		try
		{
			pdb.CreateProject(p);
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
			pdb.DeleteProject(p);
		}
		catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(true);
	}
	
	@Test
	public void testGetProject()
	{
		try
		{
			pdb.CreateProject(p);
		} catch (SQLException e)
		{
			e.printStackTrace();
			assertTrue(false);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		Project pp = new Project();
		pp.setId(p.getId());
		
		try
		{
			pdb.GetProject(pp);
		} catch (SQLException e1)
		{
			e1.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			pdb.DeleteProject(p);
		}
		catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		assertTrue(pp.getTitle().equals(p.getTitle()));
	}
	
	@Test
	public void testGetAllProjects()
	{
		int count1 = -1;
		try
		{
			count1 = pdb.GetAllProjects().size();
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
			pdb.CreateProject(p);
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
			count = pdb.GetAllProjects().size();
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
			pdb.DeleteProject(p);
		}
		catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(count-1 == count1);
	}
	
	@Test
	public void testDeleteProject()
	{
		int count1 = -1;
		try
		{
			count1 = pdb.GetAllProjects().size();
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		try
		{
			pdb.CreateProject(p);
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
			pdb.DeleteProject(p);
		}
		catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		int count = -1;
		try
		{
			count = pdb.GetAllProjects().size();
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(count == count1);
	}

}