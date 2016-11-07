package Client.Model;

import java.util.ArrayList;
import java.util.List;

import Shared.Model.Field;
import Shared.Model.Project;
import Shared.Model.User;

public class BatchState
{
	private User u;
	private List<Project> pList;
	private ArrayList<Field> fList;
	private Integer recordCount;
	private Integer imageID;
	

	public void setU(String user, String pass, String first, 
			String last, String email, Integer indexed)
	{
		u = new User(user, pass, first, last, email, indexed);
	}
	
	public User getU()
	{
		return u;
	}
	
	public void setP(List<Project> list)
	{
		pList = list;
	}
	
	public String[] getPNameList()
	{
		String[] pNameList = new String[pList.size()];
		int i = 0;
		for (Project p: this.pList)
		{
			pNameList[i] = p.getTitle();
			i++;
		}
		return pNameList;
	}
	
	public Integer getProjectID(Integer index)
	{
		return pList.get(index).getId();
	}
	
	public void setFList(ArrayList<Field> list)
	{
		fList = list;
	}
	
	public String[] getFTitleList()
	{
		String[] ret = new String[fList.size()];
		int i = 0;
		for (Field f : fList)
		{
			ret[i] = f.getTitle();
			i++;
		}
		return ret;
	}
	
	public ArrayList<Field> getFList()
	{
		return fList;
	}
	
	public void setRecordCount(Integer count)
	{
		recordCount = count;
	}
	
	public Integer getRecordCount()
	{
		return recordCount;
	}
	
	public Integer getImageID()
	{
		return imageID;
	}
	
	public void setImageID(Integer id)
	{
		imageID = id;
	}
	
}