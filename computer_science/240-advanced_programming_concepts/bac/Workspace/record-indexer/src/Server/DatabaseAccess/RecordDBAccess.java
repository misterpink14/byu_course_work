
package Server.DatabaseAccess;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import Server.DatabaseAccess.Database.Database;
import Server.DatabaseAccess.Database.DatabaseException;
import Shared.Model.Record;

/**
 * RecordDBAccess class. CRUD access the record table in the
 *  databases
 * 
 * @author Benjamin Thompson
 *
 */
public class RecordDBAccess
{
	
	private Database db = new Database();
	
	@SuppressWarnings("static-access")
	public RecordDBAccess()
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
	 * Creates a new record
	 * 
	 * @param u
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void CreateRecord(Record r) throws SQLException, DatabaseException
	{
		PreparedStatement stmt = null;
		
		try {
			String query = "insert into record "
					+ "(value, row, image_id, field_id) "
					+ "values (?, ?, ?, ?)";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			stmt.setString(1, r.getValue());
			stmt.setInt(2, r.getRow());
			stmt.setInt(3, r.getImageID());
			stmt.setInt(4, r.getFieldID());
			
			if(stmt.executeUpdate() != 1)
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
	 * Gets all Records associated with a given field id
	 * 
	 * @param fieldId
	 * @return
	 * @throws SQLException
	 * @throws DatabaseException 
	 */
	public List<Record> GetFieldRecords(Integer fieldId) throws SQLException, DatabaseException
	{
		List<Record> ret = new ArrayList<Record>();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			String query = "select * from record where field_id = ?";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, fieldId);
			rs = stmt.executeQuery();
			while(rs.next())
			{
				String title = rs.getString(1);
				Integer row = rs.getInt(2);
				Integer fieldID = rs.getInt(3);
				Integer imageID = rs.getInt(4);
				ret.add(new Record(title, row, fieldID, imageID));
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
	 * Gets all records associated with a given image id
	 * 
	 * @param imageId
	 * @return
	 * @throws SQLException
	 * @throws DatabaseException 
	 */
	public List<Record> GetImageRecords(Integer imageId) throws SQLException, DatabaseException
	{
		List<Record> ret = new ArrayList<Record>();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			String query = "select * from record where image_id = ?";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, imageId);
			rs = stmt.executeQuery();
			while(rs.next())
			{
				String title = rs.getString(1);
				Integer row = rs.getInt(2);
				Integer fieldID = rs.getInt(3);
				Integer imageID = rs.getInt(4);
				ret.add(new Record(title, row, fieldID, imageID));
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
	 * Searches records based on the given values
	 * 
	 * @param fieldIDs
	 * @param searchValues
	 * @return
	 * @throws SQLException
	 * @throws DatabaseException
	 */
	public List<Record> SearchRecords(List<Integer> fieldIDs, List<String> searchValues) throws SQLException, DatabaseException
	{
		List<Record> ret = new ArrayList<Record>();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			StringBuilder query = new StringBuilder();
					query.append("select * from record r"
					+ " where (r.field_id = ? ");
			for (int i = 1; i < fieldIDs.size(); i++)
			{
				query.append("or r.field_id = ? ");
			}
			query.append(") and ( upper(r.value) = ? ");
			for (int i = 1; i < searchValues.size(); i++)
			{
				query.append("or upper(r.value) = ? ");
			}
			query.append(')');
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query.toString());
			int i =0;
			for (; i < fieldIDs.size(); i++)
			{
				stmt.setInt((i+1), fieldIDs.get(i));
			}
			for (int j = 0; j < searchValues.size(); j++)
			{
				stmt.setString((i+j+1), searchValues.get(j).toUpperCase());
			}
			
			rs = stmt.executeQuery();
			while(rs.next())
			{
				String title = rs.getString(1);
				Integer row = rs.getInt(2);
				Integer fieldID = rs.getInt(3);
				Integer imageID = rs.getInt(4);
				ret.add(new Record(title, row, fieldID, imageID));
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
	 * Delete an image based on the given image id
	 * 
	 * @param imageId
	 * @throws SQLException
	 * @throws DatabaseException
	 */
	public void DeleteImageRecord(Integer imageId) throws SQLException, DatabaseException
	{
		db.beginTransaction();
		PreparedStatement stmt = null;
		try
		{
			String query = "delete from record where image_id = ? ";
			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, imageId);
			if (stmt.executeUpdate() != 1) 
			{
				throw new DatabaseException();
			}
		} catch (SQLException e)
		{
			db.endTransaction(false);
			throw e;
		}
		db.endTransaction(true);
		
	}
	
	
	
}