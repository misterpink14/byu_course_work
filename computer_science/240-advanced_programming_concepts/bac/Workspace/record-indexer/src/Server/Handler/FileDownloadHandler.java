package Server.Handler;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

public class FileDownloadHandler implements HttpHandler
{
	
	@Override
	public void handle(HttpExchange exchange) throws IOException
	{
		String param = (String)exchange.getRequestURI().toString();
		File f = new File("filesURL/"+param);
		
		if (!f.exists())
		{
			exchange.sendResponseHeaders(HttpURLConnection.HTTP_INTERNAL_ERROR, -1);
			return;
		}

		Path path = Paths.get(f.getAbsolutePath());
		byte[] data = Files.readAllBytes(path);

		exchange.sendResponseHeaders(HttpURLConnection.HTTP_OK, 0);
		BufferedOutputStream out = new BufferedOutputStream(exchange.getResponseBody());
        out.write(data);
        out.flush();
		exchange.getResponseBody().close();
	}
}
