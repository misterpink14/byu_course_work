package Server.Handler;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.util.List;

import Server.ServerException;
import Server.Facade.ServerFacade;
import Shared.Communication.Param.GetProjects_Param;
import Shared.Communication.Result.GetProjects_Result;
import Shared.Model.Project;
import Shared.Model.User;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

public class GetProjectsHandler implements HttpHandler
{
	private XStream xs = new XStream(new DomDriver());

	@Override
	public void handle(HttpExchange exchange) throws IOException
	{
		GetProjects_Param param = (GetProjects_Param)xs.fromXML(exchange.getRequestBody());
		GetProjects_Result result = null;
		User u = new User(param.getUser(), param.getPass(), null, null, null, null);
		
		try
		{
			List<Project> projectList = ServerFacade.getProjects(u);

			result = new GetProjects_Result(true, projectList);
		} catch (ServerException e)
		{
			exchange.sendResponseHeaders(HttpURLConnection.HTTP_INTERNAL_ERROR, -1);
			return;
		}

		exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
		xs.toXML(result, exchange.getResponseBody());
		exchange.getResponseBody().close();
	}

}
