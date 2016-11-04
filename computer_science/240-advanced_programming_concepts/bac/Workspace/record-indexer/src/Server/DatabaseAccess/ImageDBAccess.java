
package Server.DatabaseAccess;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import Server.DatabaseAccess.Database.Database;
import Server.DatabaseAccess.Database.DatabaseException;
import Shared.Model.Image;

/**
 * ImageDBAccess class. CRUD access the image table in the
 *  databases
 * 
 * @author Benjamin Thompson
 *
 */
public class ImageDBAccess 
{
	
	private Database db = new Database();
	
	/**
	 * Default constructor
	 */
	public ImageDBAccess()
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
	 * Creates an image
	 * 
	 * @param i
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void CreateImage(Image i) throws SQLException, DatabaseException
	{
		PreparedStatement stmt = null;
		ResultSet keyRS = null;		
		
		try {
			String query = "insert into image "
					+ "(file, project_id, user_id) "
					+ "values (?, ?, ?)";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			stmt.setString(1, i.getFile());
			stmt.setInt(2, i.getProjectID());
			stmt.setInt(3, i.getUserID());
			
			if(stmt.executeUpdate() == 1)
			{
				Statement keyStmt = db.getConn().createStatement();
				keyRS = keyStmt.executeQuery("select last_insert_rowid()");
				keyRS.next();
				int id = keyRS.getInt(1);
				i.setId(id);
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
	 * Get an image based on its image id
	 * 
	 * @param i
	 * @throws SQLException
	 * @throws DatabaseException
	 */
	public void GetImage(Image i) throws SQLException, DatabaseException
	{
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			
			StringBuilder query = new StringBuilder();
			query.append("select * from image where image_id = ? ");
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query.toString());
			stmt.setInt(1, i.getId());
			rs = stmt.executeQuery();
			if(rs.next())
			{
				i.setId(rs.getInt(1));
				i.setFile(rs.getString(2));
				i.setProjectID(rs.getInt(3));
				i.setUserID(rs.getInt(4));
			}
			else
			{
				throw new DatabaseException();
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
	 * Get all images associated with a given project id
	 * 
	 * @param projectId
	 * @return List<Image>
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public List<Image> GetProjectImages(Integer projectId) throws SQLException, DatabaseException
	{
		List<Image> ret = new ArrayList<Image>();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			String query = "select * from image where project_id = ?";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, projectId);
			rs = stmt.executeQuery();

			while(rs.next())
			{
				Integer id = rs.getInt(1);
				String file = rs.getString(2);
				Integer projectID = rs.getInt(3);
				Integer userID = rs.getInt(4);
				ret.add(new Image(id, file, projectID, userID));
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
	 * Get all images associated with a given user id
	 * 
	 * @param userId
	 * @return List<Image>
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public Image GetUserImage(Integer userId) throws SQLException, DatabaseException
	{
		Image ret = new Image();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			String query = "select * from image where user_id = ?";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, userId);
			rs = stmt.executeQuery();

			if(rs.next())
			{
				Integer id = rs.getInt(1);
				String file = rs.getString(2);
				Integer projectID = rs.getInt(3);
				Integer userID = rs.getInt(4);
				ret = new Image(id, file, projectID, userID);
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
	 * Gets all images
	 * 
	 * @return
	 * @throws SQLException
	 * @throws DatabaseException 
	 */
	public List<Image> GetAllImages() throws SQLException, DatabaseException
	{
		List<Image> ret = new ArrayList<Image>();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			String query = "select * from image ";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			rs = stmt.executeQuery();
			if (!rs.next())
			{
				throw new DatabaseException();
			}
			while(rs.next())
			{
				Integer id = rs.getInt(1);
				String file = rs.getString(2);
				Integer projectID = rs.getInt(3);
				Integer userID = rs.getInt(4);
				ret.add(new Image(id, file, projectID, userID));
			}
		}
		catch (SQLException e) 
		{
			throw e;
		}
		finally
		{
			db.endTransaction(false);			
		}

		return ret;
	}
	
	/**
	 * Update an image
	 * 
	 * @param i
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void UpdateImage(Image i) throws SQLException, DatabaseException
	{
		PreparedStatement stmt = null;
		try {
			db.beginTransaction();

			String query = "update image set file = ?, project_id = ?, user_id = ? where image_id = ?";
			
			stmt = db.getConn().prepareStatement(query);
			stmt.setString(1, i.getFile());
			stmt.setInt(2, i.getProjectID());
			stmt.setInt(3, i.getUserID());
			stmt.setInt(4, i.getId());
			
			Integer a = stmt.executeUpdate();

			if (a != 1) 
			{
				throw new DatabaseException();
			}
		}
		catch (SQLException e) {
			e.printStackTrace();
			db.endTransaction(false);
			throw e;
		}
		db.endTransaction(true);
	}
	
	/**
	 * Delete an image
	 * 
	 * @param i
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void DeleteImage(Image i) throws SQLException, DatabaseException
	{
		db.beginTransaction();
		PreparedStatement stmt = null;
		try
		{
			String query = "delete from image where image_id = ? ";
			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, i.getId());

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