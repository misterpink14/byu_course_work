package Client.Communicator;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import Shared.Communication.Param.DownloadBatch_Param;
import Shared.Communication.Param.GetFields_Param;
import Shared.Communication.Param.GetProjects_Param;
import Shared.Communication.Param.GetSampleImage_Param;
import Shared.Communication.Param.Search_Param;
import Shared.Communication.Param.SubmitBatch_Param;
import Shared.Communication.Param.ValidateUser_Param;
import Shared.Communication.Result.DownloadBatch_Result;
import Shared.Communication.Result.GetFields_Result;
import Shared.Communication.Result.GetProjects_Result;
import Shared.Communication.Result.GetSampleImage_Result;
import Shared.Communication.Result.Search_Result;
import Shared.Communication.Result.SubmitBatch_Result;
import Shared.Communication.Result.ValidateUser_Result;

import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

/**
 * ClientCommunicator Class. Gets data from the Server.
 * 
 * @author Benjamin Thompson
 *
 */
public class ClientCommunicator
{
	public String urlBase;
	/**
	 * Validates user credentials
	 * if valid
	 * 	OUTPUT ::= TRUE\n
	 * 	USER_FIRST_NAME\n	
	 * 	USER_LAST_NAME\n
	 * 	NUM_RECORDS\n
	 * else
	 * 	OUTPUT ::= FALSE\n
	 * 
	 * @param user String user's username
	 * @param pass String user's password
	 * @return String OUTPUT
	 * @throws ClientCommunicatorException 
	 */
	public ValidateUser_Result ValidateUser (ValidateUser_Param p) throws IOException, ClientCommunicatorException
	{
		return (ValidateUser_Result) this.post("validateUser", p);
	}
	
	/**
	 * Returns information about all of the available projects
	 * if valid
	 * 	OUTPUT ::= PROJECT_INFO+
	 * 
	 * 	PROJECT_INFO ::= PROJECT_ID\n
	 * 	PROJECT_TITLE\n
	 * else
	 * 	OUTPUT ::= FAILED\n
	 * 
	 * @param user String user's username
	 * @param pass String user's password
	 * @return String OUTPUT
	 * @throws ClientCommunicatorException 
	 */
	public GetProjects_Result GetProjects (GetProjects_Param p) throws IOException, ClientCommunicatorException
	{
		return (GetProjects_Result) this.post("getProjects", p);
	}
	
	/**
	 * Returns a sample image for the specified project
	 * if valid
	 * 	OUTPUT ::= IMAGE_URL\n
	 * else
	 * 	OUTPUT ::= FAILED\n
	 * 
	 * @param user String user's username
	 * @param pass String user's password
	 * @param project_id Integer project id
	 * @return String OUTPUT
	 * @throws ClientCommunicatorException 
	 */
	public GetSampleImage_Result GetSampleImage (GetSampleImage_Param p) throws IOException, ClientCommunicatorException
	{
		GetSampleImage_Result result = (GetSampleImage_Result) this.post("getSampleImage", p);
		result.setUrl(urlBase);
		return result;
	}
	
	/**
	 * Downloads a batch for the user to index
	 * if valid
	 * 	OUTPUT ::= BATCH_ID\n
	 * 	PROJECT_ID\n
	 * 	IMAGE_URL\n
	 * 	FIRST_Y_COORD\n
	 * 	RECORD_HEIGHT\n
	 * 	NUM_RECORDS\n
	 * 	NUM_FIELDS\n
	 * 	FIELD+
	 * else
	 * 	OUTPUT ::= FAILED\n
	 * 
	 * @param user String user's username
	 * @param pass String user's password
	 * @param project_id Integer project id
	 * @return String OUTPUT
	 * @throws ClientCommunicatorException 
	 */
	public DownloadBatch_Result DownloadBatch (DownloadBatch_Param p) throws IOException, ClientCommunicatorException
	{
		DownloadBatch_Result result = (DownloadBatch_Result) this.post("downloadBatch", p);
		result.setBaseUrl(urlBase);
		return result;
	}
	
	/**
	 * Submits the indexed record field values for a batch to the Server
	 * if valid
	 * 	true
	 * else
	 * 	false
	 * 
	 * @param user String user's username
	 * @param pass String user's password
	 * @param imageID Integer batch id
	 * @param fieldValues String left to right, top to bottom, comma delimited field values, or empty with record_values inside each fieldValue: Sting left to right, top to bottom, semicolon delimited field values, or empty
	 * @return boolean Success of submission
	 * @throws ClientCommunicatorException 
	 */
	public SubmitBatch_Result SubmitBatch (SubmitBatch_Param p) throws IOException, ClientCommunicatorException
	{
		return (SubmitBatch_Result) this.post("submitBatch", p);
	}
	
	/**
	 * Returns information about all of the fields for the specified project
	 * if valid
	 * 	OUTPUT ::= FIELD_INFO+
	 * 
	 * 	FIELD_INFO ::= PROJECT_ID\n
	 * 	FIELD_ID\n
	 * 	FIELD_TITLE\n
	 * else
	 * 	OUTPUT ::= FAILED\n
	 * 
	 * @param user String user's username
	 * @param pass String user's password
	 * @param project_id String project id
	 * @return String OUTPUT
	 * @throws ClientCommunicatorException 
	 */
	public GetFields_Result GetFields (GetFields_Param p) throws IOException, ClientCommunicatorException
	{
		return (GetFields_Result) this.post("getFields", p);
	}
	
	/**
	 * Searches the indexed records for the specified strings
	 * if valid
	 * 	OUTPUT ::= SEARCH_RESULT*
	 * 
	 * 	SEARCH_RESULT ::=
	 * 	BATCH_ID\n
	 * 	IMAGE_URL\n
	 * 	RECORD_NUM\n
	 * 	FIELD_ID\n
	 * else
	 * 	OUTPUT ::= FAILED\n
	 * 
	 * @param user String user's username
	 * @param pass String user's password
	 * @param fields String Comma-separated list of fields to be searched
	 * @param search_values String Comma-separated list of strings to search for
	 * @return String OUTPUT
	 * @throws IOException 
	 * @throws ClientCommunicatorException 
	 */
	public Search_Result Search (Search_Param p) throws IOException, ClientCommunicatorException
	{
		Search_Result result = (Search_Result) this.post("search", p);
		result.updateURL(urlBase);
		return result;
	}
	

	public Object post(String urlPath, Object data) throws IOException, ClientCommunicatorException
	{
		XStream xstream = new XStream(new DomDriver());
		URL url;
		try
		{
			url = new URL(urlBase + urlPath);
			System.out.println(url);
		} catch (MalformedURLException e)
		{
			e.printStackTrace();
			throw e;
		}
		
		HttpURLConnection conn = (HttpURLConnection)url.openConnection();
		conn.setRequestMethod("POST");
		conn.setDoInput(true);
		conn.setDoOutput(true);
		conn.connect();
		
		xstream.toXML(data, conn.getOutputStream());
		conn.getOutputStream().close();
		if (conn.getResponseCode() == HttpURLConnection.HTTP_OK)
		{
			Object result = xstream.fromXML(conn.getInputStream());
			conn.getInputStream().close();
			return result;
		}
		System.out.println(conn.getResponseMessage());
		throw new ClientCommunicatorException();
	}
	
}
