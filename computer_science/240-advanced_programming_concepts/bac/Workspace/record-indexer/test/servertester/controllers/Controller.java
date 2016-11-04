package servertester.controllers;

import java.util.*;

import Shared.Communication.Param.DownloadBatch_Param;
import Shared.Communication.Param.GetFields_Param;
import Shared.Communication.Param.GetProjects_Param;
import Shared.Communication.Param.GetSampleImage_Param;
import Shared.Communication.Param.Search_Param;
import Shared.Communication.Param.SubmitBatch_Param;
import Shared.Communication.Param.ValidateUser_Param;
import Client.Communicator.ClientCommunicator;
import servertester.views.*;

public class Controller implements IController {

	private IView _view;
	private ClientCommunicator client;
	
	public Controller() {
		client = new ClientCommunicator();
		return;
	}
	
	public IView getView() {
		return _view;
	}
	
	public void setView(IView value) {
		_view = value;
	}
	
	// IController methods
	//
	
	@Override
	public void initialize() 
	{
		getView().setHost("localhost");
		getView().setPort("6989");
		operationSelected();
	}

	@Override
	public void operationSelected() {
		ArrayList<String> paramNames = new ArrayList<String>();
		paramNames.add("User");
		paramNames.add("Password");
		
		switch (getView().getOperation()) {
		case VALIDATE_USER:
			break;
		case GET_PROJECTS:
			break;
		case GET_SAMPLE_IMAGE:
			paramNames.add("Project");
			break;
		case DOWNLOAD_BATCH:
			paramNames.add("Project");
			break;
		case GET_FIELDS:
			paramNames.add("Project");
			break;
		case SUBMIT_BATCH:
			paramNames.add("Batch");
			paramNames.add("Record Values");
			break;
		case SEARCH:
			paramNames.add("Fields");
			paramNames.add("Search Values");
			break;
		default:
			assert false;
			break;
		}
		
		getView().setRequest("");
		getView().setResponse("");
		getView().setParameterNames(paramNames.toArray(new String[paramNames.size()]));
	}

	@Override
	public void executeOperation() {
		this.client.urlBase = "http://" + getView().getHost() + ":" + getView().getPort() + "/";
		switch (getView().getOperation()) {
		case VALIDATE_USER:
			validateUser();
			break;
		case GET_PROJECTS:
			getProjects();
			break;
		case GET_SAMPLE_IMAGE:
			getSampleImage();
			break;
		case DOWNLOAD_BATCH:
			downloadBatch();
			break;
		case GET_FIELDS:
			getFields();
			break;
		case SUBMIT_BATCH:
			submitBatch();
			break;
		case SEARCH:
			search();
			break;
		default:
			assert false;
			break;
		}
	}
	
	private void validateUser() 
	{
		String[] values = getView().getParameterValues();
		if(this.isEmpty(values))
		{
			getView().setResponse("FAILED\n");
			return;
		}
		ValidateUser_Param p = new ValidateUser_Param(values[0], values[1]);
		try
		{
			getView().setResponse(this.client.ValidateUser(p).toString());
		} catch (Exception e)
		{
			getView().setResponse("FAILED\n");
		}
	}
	
	private void getProjects() 
	{
		String[] values = getView().getParameterValues();
		if(this.isEmpty(values))
		{
			getView().setResponse("FAILED\n");
			return;
		}
		GetProjects_Param p = new GetProjects_Param(values[0], values[1]);
		try
		{
			getView().setResponse(this.client.GetProjects(p).toString());
		} catch (Exception e)
		{
			getView().setResponse("FAILED\n");
		}
	}
	
	private void getSampleImage() 
	{
		String[] values = getView().getParameterValues();
		if(this.isEmpty(values))
		{
			getView().setResponse("FAILED\n");
			return;
		}
		GetSampleImage_Param p = new GetSampleImage_Param(values[0], values[1], Integer.parseInt(values[2]));
		try
		{
			getView().setResponse(this.client.GetSampleImage(p).toString());
		} catch (Exception e)
		{
			getView().setResponse("FAILED\n");
		}
	}
	
	private void downloadBatch() 
	{
		String[] values = getView().getParameterValues();
		if(this.isEmpty(values))
		{
			getView().setResponse("FAILED\n");
			return;
		}
		DownloadBatch_Param p = new DownloadBatch_Param(values[0], values[1], Integer.parseInt(values[2]));
		try
		{
			getView().setResponse(this.client.DownloadBatch(p).toString());
		} catch (Exception e)
		{
			getView().setResponse("FAILED\n");
		}
	}
	
	private void submitBatch() 
	{
		String[] values = getView().getParameterValues();
		if(this.isEmpty(values))
		{
			getView().setResponse("FAILED\n");
			return;
		}
		SubmitBatch_Param p = new SubmitBatch_Param(values[0], values[1], Integer.parseInt(values[2]), values[3]);
		try
		{
			getView().setResponse(this.client.SubmitBatch(p).toString());
		} catch (Exception e)
		{
			getView().setResponse("FAILED\n");
		}
	}
	
	private void getFields() 
	{
		String[] values = getView().getParameterValues();
		if(values[0].isEmpty())
		{
			getView().setResponse("FAILED\n");
			return;
		}
		if(values[1].isEmpty())
		{
			getView().setResponse("FAILED\n");
			return;
		}
		GetFields_Param p = null;
		if(values[2].isEmpty())
		{ 
			p = new GetFields_Param(values[0], values[1], null);
		}
		else
		{
			p = new GetFields_Param(values[0], values[1], Integer.parseInt(values[2]));
		}
		try
		{
			getView().setResponse(this.client.GetFields(p).toString());
		} catch (Exception e)
		{
			getView().setResponse("FAILED\n");
		}
	}
	
	private void search() 
	{
		String[] values = getView().getParameterValues();
		if(this.isEmpty(values))
		{
			getView().setResponse("FAILED\n");
			return;
		}
		Search_Param p = new Search_Param(values[0], values[1], values[2], values[3]);
		try
		{
			getView().setResponse(this.client.Search(p).toString());
		} catch (Exception e)
		{
			getView().setResponse("FAILED\n");
		}
	}
	
	private boolean isEmpty(String[] data)
	{
		for (String s: data)
		{
			if (s.isEmpty())
			{
				return true;
			}
		}
		return false;
	}

}

