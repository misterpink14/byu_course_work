package client.communicator;

import static org.junit.Assert.*;

import java.io.IOException;
import java.sql.SQLException;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import Server.DatabaseAccess.Database.DatabaseException;
import Server.DatabaseAccess.Database.Importer;
import Shared.Communication.Param.DownloadBatch_Param;
import Shared.Communication.Param.GetFields_Param;
import Shared.Communication.Param.GetProjects_Param;
import Shared.Communication.Param.GetSampleImage_Param;
import Shared.Communication.Param.Search_Param;
import Shared.Communication.Param.SubmitBatch_Param;
import Shared.Communication.Param.ValidateUser_Param;
import Shared.Communication.Result.DownloadBatch_Result;
import Shared.Model.Field;
import Client.Communicator.ClientCommunicator;
import Client.Communicator.ClientCommunicatorException;

public class ClientCommunicatorTest
{
	private ClientCommunicator comm = new ClientCommunicator();

	@BeforeClass
	public static void setUpBeforeClass() throws Exception
	{
		new Importer().execute("Records/Records.xml");
	}

	@AfterClass
	public static void tearDownAfterClass() throws Exception
	{
		new Importer().execute("Records/Records.xml");
		
	}

	@Before
	public void setUp() throws Exception
	{
		comm.urlBase = "http://localhost:6989/";
	}

	@After
	public void tearDown() throws Exception
	{
	}

	@Test
	public void testValidateUser() throws IOException, ClientCommunicatorException
	{
		ValidateUser_Param p = new ValidateUser_Param("sheila", "parker");
		assertTrue(comm.ValidateUser(p).toString().length() > 8);
		
	}

	@Test
	public void testGetProjects() throws IOException, ClientCommunicatorException
	{
		GetProjects_Param p = new GetProjects_Param("sheila", "parker");
		assertTrue(comm.GetProjects(p).getSuccess());
	}

	@Test
	public void testGetSampleImage() throws SQLException, DatabaseException, IOException, ClientCommunicatorException
	{
		GetProjects_Param pa = new GetProjects_Param("sheila", "parker");
		GetSampleImage_Param p = new GetSampleImage_Param("sheila", "parker", comm.GetProjects(pa).getProjectList().get(0).getId());
		assertTrue(comm.GetSampleImage(p).getSuccess());
	}

	@Test
	public void testDownloadBatch() throws SQLException, DatabaseException, IOException, ClientCommunicatorException
	{
		GetProjects_Param pa = new GetProjects_Param("sheila", "parker");
		DownloadBatch_Param p = new DownloadBatch_Param("sheila", "parker", comm.GetProjects(pa).getProjectList().get(0).getId());
		DownloadBatch_Result ret = comm.DownloadBatch(p);
		
		comm.SubmitBatch(new SubmitBatch_Param("sheila", "parker", ret.getBatchID(), "q,q,q"));
		assertTrue(ret.getSuccess());
	}

	@Test
	public void testSubmitBatch() throws SQLException, DatabaseException, IOException, ClientCommunicatorException
	{
		GetProjects_Param pa = new GetProjects_Param("sheila", "parker");
		DownloadBatch_Param p = new DownloadBatch_Param("sheila", "parker", comm.GetProjects(pa).getProjectList().get(0).getId());
		DownloadBatch_Result ret = comm.DownloadBatch(p);
		
		assertTrue(comm.SubmitBatch(new SubmitBatch_Param("sheila", "parker", ret.getBatchID(), "q,q,q")).getSuccess());
	}

	@Test
	public void testGetFields() throws IOException, ClientCommunicatorException
	{
		
		GetFields_Param p = new GetFields_Param("sheila", "parker", null);
		assertTrue(comm.GetFields(p).getFieldList() != null);
	}

	@Test
	public void testSearch() throws IOException, ClientCommunicatorException
	{
		GetFields_Param pa = new GetFields_Param("sheila", "parker", null);
		StringBuilder sb = new StringBuilder();
		int i = 0;
		for (Field f: comm.GetFields(pa).getFieldList())
		{
			if (i == 0)
			{
				sb.append(f.getId());
				i++;
			}
			else sb.append(',').append(f.getId());
		}
		
		Search_Param p = new Search_Param("sheila", "parker", sb.toString(), "FOX");
		assertTrue(comm.Search(p).success);
	}

}
