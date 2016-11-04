package Server.Handler;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Pattern;

import Server.ServerException;
import Server.Facade.ServerFacade;
import Shared.Communication.Param.SubmitBatch_Param;
import Shared.Communication.Result.SubmitBatch_Result;
import Shared.Model.User;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.thoughtworks.xstream.XStream;
import com.thoughtworks.xstream.io.xml.DomDriver;

public class SubmitBatchHandler implements HttpHandler
{
	private XStream xs = new XStream(new DomDriver());

	@Override
	public void handle(HttpExchange exchange) throws IOException
	{
		SubmitBatch_Param param = (SubmitBatch_Param)xs.fromXML(exchange.getRequestBody());
		SubmitBatch_Result result = null;
		User u = new User(param.getUser(), param.getPass(), null, null, null, null);

		Map<Integer, ArrayList<String>> recordList = new HashMap<Integer, ArrayList<String>>();

		int k = 1;
		String[] records = param.getFieldValues().split(Pattern.quote(";"));
		for (String record : records)
		{
			String[] rs = record.split(Pattern.quote(","));
			ArrayList<String> rList = new ArrayList<String>();
			for (String r: rs)
			{
				rList.add(r);
			}
			recordList.put(k, rList);
			k++;
		}
		
		try
		{
			ServerFacade.submitBatch(u, param.getImageID(), recordList);;

			result = new SubmitBatch_Result(true);
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
