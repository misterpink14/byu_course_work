package Server.Handler;

import java.io.IOException;
import java.net.HttpURLConnection;

import Server.ServerException;
import Server.Facade.ServerFacade;
import Shared.Communication.Param.GetSampleImage_Param;
import Shared.Communication.Result.GetSampleImage_Result;
import Shared.Model.Image;
import Shared.Model.User;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

public class GetSampleImageHandler implements HttpHandler
{
	private XStream xs = new XStream(new DomDriver());

	@Override
	public void handle(HttpExchange exchange) throws IOException
	{
		GetSampleImage_Param param = (GetSampleImage_Param)xs.fromXML(exchange.getRequestBody());
		GetSampleImage_Result result = null;
		User u = new User(param.getUser(), param.getPass(), null, null, null, null);
		
		try
		{
			Image i = ServerFacade.getSampleImage(u, param.getProjectID());
			result = new GetSampleImage_Result(true, i.getFile());
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
