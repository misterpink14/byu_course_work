package Server.Handler;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.util.List;

import Server.ServerException;
import Server.Facade.ServerFacade;
import Shared.Communication.Param.GetFields_Param;
import Shared.Communication.Result.GetFields_Result;
import Shared.Model.Field;
import Shared.Model.User;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

public class GetFieldsHandler implements HttpHandler
{
	private XStream xs = new XStream(new DomDriver());

	@Override
	public void handle(HttpExchange exchange) throws IOException
	{
		GetFields_Param param = (GetFields_Param)xs.fromXML(exchange.getRequestBody());
		GetFields_Result result = null;
		User u = new User(param.getUser(), param.getPass(), null, null, null, null);
		
		try
		{
			List<Field> fieldList = ServerFacade.getFields(u, param.getProjectID());

			result = new GetFields_Result(true, fieldList);
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
