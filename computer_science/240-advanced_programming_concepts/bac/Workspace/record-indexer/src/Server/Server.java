package Server;

import java.io.IOException;
import java.net.InetSocketAddress;

import Server.Facade.ServerFacade;
import Server.Handler.DownloadBatchHandler;
import Server.Handler.FileDownloadHandler;
import Server.Handler.GetFieldsHandler;
import Server.Handler.GetProjectsHandler;
import Server.Handler.GetSampleImageHandler;
import Server.Handler.SearchHandler;
import Server.Handler.SubmitBatchHandler;
import Server.Handler.ValidateUserHandler;

import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class Server
{
	private static int SERVER_PORT_NUMBER;
	private static final int MAX_WAITING_CONNECTIONS = 10;
	
	private HttpServer server;

	private HttpHandler validateUserHandler = new ValidateUserHandler();
	private HttpHandler getProjectsHandler = new GetProjectsHandler();
	private HttpHandler getSampleImageHandler = new GetSampleImageHandler();
	private HttpHandler downloadBatchHandler = new DownloadBatchHandler();
	private HttpHandler submitBatchHandler = new SubmitBatchHandler();
	private HttpHandler getFieldsHandler = new GetFieldsHandler();
	private HttpHandler searchHandler = new SearchHandler();
	private HttpHandler fileDownloadHandler = new FileDownloadHandler();
	
	private Server(Integer port) {
		SERVER_PORT_NUMBER = port;
	}

	public void run() 
	{
		try {
			ServerFacade.initialize();		
		}
		catch (ServerException e) {
			e.printStackTrace();
			return;
		}
		
		try {
			server = HttpServer.create(new InetSocketAddress(SERVER_PORT_NUMBER),
											MAX_WAITING_CONNECTIONS);
		} catch (IOException e) {
			e.printStackTrace();
			return;
		}

		server.setExecutor(null); // use the default executor
		server.createContext("/validateUser", validateUserHandler);
		server.createContext("/getProjects", getProjectsHandler);
		server.createContext("/getSampleImage", getSampleImageHandler);
		server.createContext("/downloadBatch", downloadBatchHandler);
		server.createContext("/submitBatch", submitBatchHandler);
		server.createContext("/getFields", getFieldsHandler);
		server.createContext("/search", searchHandler);
		server.createContext("/", fileDownloadHandler);
		
		
		server.start();
	}
	
	public static void main (String[] args)
	{
		new Server(Integer.parseInt(args[0])).run();
	}

}
