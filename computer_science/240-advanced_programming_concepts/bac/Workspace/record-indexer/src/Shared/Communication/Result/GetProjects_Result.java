package Shared.Communication.Result;

import java.util.List;

import Shared.Model.Project;

/**
 * For GetProjects output
 * 
 * @author Benjamin Thompson
 *
 */
public class GetProjects_Result
{
	private Boolean success;
	List<Project> projectList;

	
	/**
	 * GetProjects_Result Constructor
	 * @param success
	 * @param projectList
	 */
	public GetProjects_Result(Boolean success, List<Project> projectList)
	{
		super();
		this.success = success;
		this.projectList = projectList;
	}
	
	/**
	 * Returns success status
	 * 
	 * @return the success
	 */
	public Boolean getSuccess()
	{
		return success;
	}

	/**
	 * Returns projectList
	 * 
	 * @return the projectList
	 */
	public List<Project> getProjectList()
	{
		return projectList;
	}

	@Override
	public String toString()
	{
		if (!success || this.projectList == null)
			return "FAILED\n";
		StringBuilder sb = new StringBuilder();
		for (Project p : this.projectList)
		{
			sb.append(p.getId().intValue()).append('\n').append(p.getTitle()).append('\n');
		}
		return sb.toString();
	}
	
}
