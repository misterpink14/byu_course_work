package Server.Handler;

import java.io.IOException;
import java.net.HttpURLConnection;

import Server.ServerException;
import Server.Facade.ServerFacade;
import Shared.Communication.Param.ValidateUser_Param;
import Shared.Communication.Result.ValidateUser_Result;
import Shared.Model.User;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

public class ValidateUserHandler implements HttpHandler
{
	private XStream xs = new XStream(new DomDriver());

	@Override
	public void handle(HttpExchange exchange) throws IOException
	{
		ValidateUser_Param param = (ValidateUser_Param)xs.fromXML(exchange.getRequestBody());
		ValidateUser_Result result = null;
		
		User u = new User(param.getUser(), param.getPass(), null, null, null, null);
		
		try
		{
			ServerFacade.validateUser(u);
			result = new ValidateUser_Result("TRUE", u.getFirst(), u.getLast(), u.getIndexed().intValue());
		} catch (ServerException e)
		{
			result = new ValidateUser_Result(e.getMessage());
		}
		

		exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
		xs.toXML(result, exchange.getResponseBody());
		exchange.getResponseBody().close();
	}

}
