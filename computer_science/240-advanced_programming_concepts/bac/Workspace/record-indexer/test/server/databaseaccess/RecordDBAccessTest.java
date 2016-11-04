package server.databaseaccess;

import static org.junit.Assert.*;

import java.sql.SQLException;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import Server.DatabaseAccess.RecordDBAccess;
import Server.DatabaseAccess.Database.Database;
import Server.DatabaseAccess.Database.DatabaseException;
import Shared.Model.Record;

public class RecordDBAccessTest
{
	private static Record r;
	private static RecordDBAccess rdb;

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
		r = new Record("value", 1, -2, -3);
		rdb = new RecordDBAccess();
	}

	@After
	public void tearDown() throws Exception
	{	}

	@Test
	public void testCreateRecord()
	{
		try
		{
			rdb.CreateRecord(r);
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}

		try
		{
			rdb.DeleteImageRecord(r.getImageID());
		}
		catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(true);
	}

	@Test
	public void testGetFieldRecords()
	{
		try
		{
			rdb.CreateRecord(r);
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
			count = rdb.GetFieldRecords(r.getFieldID()).size();
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}

		try
		{
			rdb.DeleteImageRecord(r.getImageID());
		}
		catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(count == 1);
	}

	@Test
	public void testGetImageRecords()
	{
		try
		{
			rdb.CreateRecord(r);
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
			count = rdb.GetImageRecords(r.getImageID()).size();
		} catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}

		try
		{
			rdb.DeleteImageRecord(r.getImageID());
		}
		catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		
		assertTrue(count == 1);
	}

	@Test
	public void testDeleteImageRecord()
	{
		int count1 = -1;
		try
		{
			count1 = rdb.GetImageRecords(r.getImageID()).size();
		} catch (SQLException | DatabaseException e)
		{
		}
		
		try
		{
			rdb.CreateRecord(r);
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
			rdb.DeleteImageRecord(r.getImageID());
		}
		catch (SQLException | DatabaseException e)
		{
			e.printStackTrace();
			assertTrue(false);
		}
		int count = -1;
		try
		{
			count = rdb.GetImageRecords(r.getImageID()).size();
		} catch (SQLException | DatabaseException e)
		{
		}
		
		assertTrue(count == count1);
	}
}