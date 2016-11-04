
package Server.DatabaseAccess;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

import Server.DatabaseAccess.Database.Database;
import Server.DatabaseAccess.Database.DatabaseException;
import Shared.Model.Project;

/**
 * ProjectDBAccess class. CRUD access the project table in the
 *  databases
 * 
 * @author Benjamin Thompson
 *
 */
public class ProjectDBAccess
{
	private Database db = new Database();

	
	@SuppressWarnings("static-access")
	public ProjectDBAccess()
	{
		try
		{
			this.db.init();
		} catch (ClassNotFoundException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	
	
	/**
	 * Return the Database Object
	 * 
	 * @return
	 */
	public Database getDb()
	{
		return db;
	}



	/**
	 * Set the Database object
	 * 
	 * @param db
	 */
	public void setDb(Database db)
	{
		this.db = db;
	}



	/**
	 * Creates a new project
	 * 
	 * @param p
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void CreateProject(Project p) throws SQLException, DatabaseException
	{
//		ResultSet rs = null;
		PreparedStatement stmt = null;
		ResultSet keyRS = null;		
		
		try {
			String query = "insert into project "
					+ "(title, records_per_image, first_y_coord, record_height) "
					+ "values (?, ?, ?, ?)";

			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);

			stmt.setString(1, p.getTitle());
			stmt.setInt(2, p.getRecords());
			stmt.setInt(3, p.getFirsty());
			stmt.setInt(4, p.getHeight());

			if(stmt.executeUpdate() == 1)
			{
				Statement keyStmt = db.getConn().createStatement();
				keyRS = keyStmt.executeQuery("select last_insert_rowid()");
				keyRS.next();
				int id = keyRS.getInt(1);
				p.setId(id);
			}
			else
			{
				throw new DatabaseException();
			}
		}
		catch (SQLException e) {
			db.endTransaction(false);
			throw e;
		}
		db.endTransaction(true);
	}
	
	/**
	 * Gets all projects
	 * 
	 * @return List<Project>
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public List<Project> GetAllProjects() throws SQLException, DatabaseException
	{
		List<Project> ret = new ArrayList<Project>();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			String query = "select * from project ";

			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			rs = stmt.executeQuery();
			while(rs.next())
			{
				Integer id = rs.getInt(1);
				String titles = rs.getString(2);
				Integer records = rs.getInt(3);
				Integer firsty = rs.getInt(4);
				Integer height = rs.getInt(5);
				ret.add(new Project(id, titles, records, firsty, height));
			}
		}
		catch (SQLException e) {
//			db.endTransaction(false);
			throw e;
		}
		finally
		{
			db.endTransaction(false);			
		}

		
		
		return ret;
	}
	
	/**
	 * Gets a project
	 * 
	 * @param p
	 * @throws SQLException 
	 */
	public void GetProject(Project p) throws SQLException
	{
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			
			StringBuilder query = new StringBuilder();
			query.append("select * from project where project_id = ? ");
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query.toString());

			stmt.setInt(1, p.getId());
			
			rs = stmt.executeQuery();
			if(rs.next())
			{
				p.setId(rs.getInt(1));
				p.setTitle(rs.getString(2));
				p.setRecords(rs.getInt(3));
				p.setFirsty(rs.getInt(4));
				p.setHeight(rs.getInt(5));
			}
			else
			{
				throw new SQLException();
			}
		}
		catch (SQLException e) {
			throw e;
		}
		finally
		{
			db.endTransaction(false);			
		}
	
	}
	
	/**
	 * Deletes a project
	 * 
	 * @param p
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void DeleteProject(Project p) throws SQLException, DatabaseException
	{
		db.beginTransaction();
		PreparedStatement stmt = null;
		try
		{
			String query = "delete from project where project_id = ? ";
			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, p.getId());
			if (stmt.executeUpdate() != 1) 
			{
				throw new DatabaseException();
			}
		} catch (SQLException e)
		{
			// TODO Auto-generated catch block
			db.endTransaction(false);
			e.printStackTrace();
			throw e;
		}
		db.endTransaction(true);
		
	}
}
