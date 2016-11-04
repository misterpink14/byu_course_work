/**
 * 
 */
package Server.DatabaseAccess;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import Server.DatabaseAccess.Database.Database;
import Server.DatabaseAccess.Database.DatabaseException;
import Shared.Model.Field;

/**
 * UserDBAccess class. CRUD access the User table in the
 *  database
 * 
 * @author Benjamin Thompson
 *
 */
public class FieldDBAccess 
{
	
	private Database db = new Database();
	
	/**
	 * Default Constructor
	 */
	public FieldDBAccess()
	{	}
	
	
	
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
	 * Create a field
	 * 
	 * @param f
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void CreateField(Field f) throws SQLException, DatabaseException
	{
		PreparedStatement stmt = null;
		ResultSet keyRS = null;		
		
		try {
			String query = "insert into field "
					+ "(title, x_coord, width, helphtml, knowndata, project_id) "
					+ "values (?, ?, ?, ?, ?, ?)";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			stmt.setString(1, f.getTitle());
			stmt.setInt(2, f.getXcoord());
			stmt.setInt(3, f.getWidth());
			stmt.setString(4, f.getHelphtml());
			stmt.setString(5, f.getKnowndata());
			stmt.setInt(6, f.getProject_id());
			
			if(stmt.executeUpdate() == 1)
			{
				Statement keyStmt = db.getConn().createStatement();
				keyRS = keyStmt.executeQuery("select last_insert_rowid()");
				keyRS.next();
				int id = keyRS.getInt(1);
				f.setId(id);
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
	 * Get all fields
	 * 
	 * @return List<Field>
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public List<Field> GetAllFields() throws SQLException, DatabaseException
	{
		List<Field> ret = new ArrayList<Field>();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			String query = "select * from field ";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			rs = stmt.executeQuery();
			while(rs.next())
			{
				Integer id = rs.getInt(1);
				String title = rs.getString(2);
				Integer xcoord = rs.getInt(3);
				Integer width = rs.getInt(4);
				String helphtml = rs.getString(5);
				String knowndata = rs.getString(6);
				Integer project_id = rs.getInt(7);
				ret.add(new Field(id, title, xcoord, width, helphtml, knowndata, project_id));
			}
		}
		catch (SQLException e) {
			throw e;
		}
		finally
		{
			db.endTransaction(false);			
		}

		return ret;
	}
	
	/**
	 * Get all fields for a given project_id
	 * 
	 * @return List<Field>
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public List<Field> GetProjectFields(Integer projectId) throws SQLException, DatabaseException
	{
		List<Field> ret = new ArrayList<Field>();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			String query = "select * from field where project_id = ?";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, projectId);
			rs = stmt.executeQuery();
			while(rs.next())
			{
				Integer id = rs.getInt(1);
				String title = rs.getString(2);
				Integer xcoord = rs.getInt(3);
				Integer width = rs.getInt(4);
				String helphtml = rs.getString(5);
				String knowndata = rs.getString(6);
				Integer project_id = rs.getInt(7);
				ret.add(new Field(id, title, xcoord, width, helphtml, knowndata, project_id));
			}
		}
		catch (SQLException e) {
			throw e;
		}
		finally
		{
			db.endTransaction(false);			
		}

		
		return ret;
	}
	
	/**
	 * Get all fields associated with a given image id
	 * 
	 * @param imageId
	 * @return
	 * @throws SQLException
	 * @throws DatabaseException
	 */
	public List<Field> GetImageFields(Integer imageId) throws SQLException, DatabaseException
	{
		List<Field> ret = new ArrayList<Field>();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			String query = "select f.field_id, f.title, f.x_coord, f.width, f.helphtml, f.knowndata, f.project_id "
					+ "from image i "
					+ "join main.field f "
					+ "on i.project_id=f.project_id "
					+ "where i.image_id = ?";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, imageId);
			rs = stmt.executeQuery();
			while(rs.next())
			{
				Integer id = rs.getInt(1);
				String title = rs.getString(2);
				Integer xcoord = rs.getInt(3);
				Integer width = rs.getInt(4);
				String helphtml = rs.getString(5);
				String knowndata = rs.getString(6);
				Integer project_id = rs.getInt(7);
				ret.add(new Field(id, title, xcoord, width, helphtml, knowndata, project_id));
			}
		}
		catch (SQLException e) {
			throw e;
		}
		finally
		{
			db.endTransaction(false);			
		}
		return ret;
	}
	
	/**
	 * Delete a field
	 * 
	 * @param f
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void DeleteField(Field f) throws SQLException, DatabaseException
	{
		db.beginTransaction();
		PreparedStatement stmt = null;
		try
		{
			String query = "delete from field where field_id = ? ";
			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, f.getId());
			if (stmt.executeUpdate() != 1) 
			{
				throw new DatabaseException();
			}
		} catch (SQLException e)
		{
			db.endTransaction(false);
			e.printStackTrace();
			throw e;
		}
		db.endTransaction(true);
	}
}