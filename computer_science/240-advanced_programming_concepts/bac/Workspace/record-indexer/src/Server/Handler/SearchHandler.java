package Server.Handler;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.regex.Pattern;

import Server.ServerException;
import Server.Facade.ServerFacade;
import Shared.Communication.Param.Search_Param;
import Shared.Communication.Result.Search_Result;
import Shared.Model.Image;
import Shared.Model.Record;
import Shared.Model.User;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

public class SearchHandler implements HttpHandler
{
	private XStream xs = new XStream(new DomDriver());
	
	@Override
	public void handle(HttpExchange exchange) throws IOException
	{
		Search_Param param = (Search_Param)xs.fromXML(exchange.getRequestBody());
		Search_Result result = null;
		User u = new User(param.getUser(), param.getPass(), null, null, null, null);
		
		String[] fields = param.getFields().split(Pattern.quote(","));
		List<Integer> fieldIDs = new ArrayList<Integer>();
		for(String s: fields)
		{
			fieldIDs.add(Integer.parseInt(s));
		}
		
		String[] searchs = param.getSearchValues().split(Pattern.quote(","));
		List<String> searchValues = new ArrayList<String>(Arrays.asList(searchs));
		
		for (Integer s: fieldIDs)
		{
			System.out.println(s.intValue());
		}
		for (String s: searchValues)
		{
			System.out.println(s);
		}
		
		try
		{
			Map<Image, List<Record>> fieldList = ServerFacade.search(u, fieldIDs, searchValues);

			result = new Search_Result(true, fieldList);
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
