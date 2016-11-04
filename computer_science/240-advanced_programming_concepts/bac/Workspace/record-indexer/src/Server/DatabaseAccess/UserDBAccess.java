package Server.DatabaseAccess;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

import Server.DatabaseAccess.Database.Database;
import Server.DatabaseAccess.Database.DatabaseException;
import Shared.Model.User;

/**
 * UserDBAccess class. CRUD access the user table in the
 *  databases
 * 
 * @author Benjamin Thompson
 *
 */
public class UserDBAccess
{
	
	private Database db = new Database();

	/**
	 * Default Constructor
	 */
	public UserDBAccess()
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
	 * Creates a new user
	 * 
	 * @param u
	 * @throws SQLException 
	 */
	public void CreateUser(User u) throws SQLException, DatabaseException
	{
		PreparedStatement stmt = null;
		ResultSet keyRS = null;		
		
		try {
			String query = "insert into user "
					+ "(user_name, password, first_name, last_name, email, indexed) "
					+ "values (?, ?, ?, ?, ?, ?)";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			stmt.setString(1, u.getUser());
			stmt.setString(2, u.getPass());
			stmt.setString(3, u.getFirst());
			stmt.setString(4, u.getLast());
			stmt.setString(5, u.getEmail());
			stmt.setInt(6, u.getIndexed());
			
			if(stmt.executeUpdate() == 1)
			{
				Statement keyStmt = db.getConn().createStatement();
				keyRS = keyStmt.executeQuery("select last_insert_rowid()");
				keyRS.next();
				int id = keyRS.getInt(1);
				u.setId(id);
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
	 * Gets all users
	 * 
	 * @return List<User>
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public List<User> GetAllUsers() throws SQLException, DatabaseException
	{
		List<User> ret = new ArrayList<User>();
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			String query = "select * from user ";
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query);
			rs = stmt.executeQuery();
			while(rs.next())
			{
				Integer id = rs.getInt(1);
				String user = rs.getString(2);
				String pass = rs.getString(3);
				String first = rs.getString(4);
				String last = rs.getString(5);
				String email = rs.getString(6);
				Integer indexed = rs.getInt(7);
				ret.add(new User(id, user, pass, first, last, email, indexed));
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
	 * Gets a user
	 * 
	 * @param u
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void GetUser(User u) throws SQLException, DatabaseException
	{
		ResultSet rs = null;
		PreparedStatement stmt = null;
		
		try {
			StringBuilder query = new StringBuilder();
			query.append("select * from user where ");
			if (u.getId() != null && u.getId() != -1)
			{
				query.append("user_id = ? ");
			}
			if (u.getUser() != null)
			{
				if (u.getId() != null && u.getId() != -1)
				{
					query.append("and ");
				}
				query.append("user_name = ? ");
			}
			if (u.getPass() != null)
			{
				if ( (u.getId() != null && u.getId() != -1)||(u.getUser() != null) )
				{
					query.append("and ");
				}
				query.append("password = ? ");
			}
			
			db.beginTransaction();

			stmt = db.getConn().prepareStatement(query.toString());

			int i = 1;
			if (u.getId() != null && u.getId() != -1)
			{
				stmt.setInt(i, u.getId());
				++i;
			}
			if (u.getUser() != null)
			{
				stmt.setString(i, u.getUser());
				++i;
			}
			if (u.getPass() != null)
			{
				stmt.setString(i, u.getPass());
				++i;
			}

			rs = stmt.executeQuery();
			if(rs.next())
			{
				u.setId(rs.getInt(1));
				u.setUser(rs.getString(2));
				u.setFirst(rs.getString(3));
				u.setFirst(rs.getString(4));
				u.setLast(rs.getString(5));
				u.setEmail(rs.getString(6));
				u.setIndexed(rs.getInt(7));
				
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
	 * Updates a user. May not be used.
	 * 
	 * @param u
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void UpdateUser(User u) throws SQLException, DatabaseException
	{
		PreparedStatement stmt = null;
		try {
			db.beginTransaction();
			
			String query = "update user set user_name = ?, password = ?, first_name = ?, last_name = ?, email = ?, indexed = ? where user_id = ?";
			
			stmt = db.getConn().prepareStatement(query);
			stmt.setString(1, u.getUser());
			stmt.setString(2, u.getPass());
			stmt.setString(3, u.getFirst());
			stmt.setString(4, u.getLast());
			stmt.setString(5, u.getEmail());
			stmt.setInt(6, u.getIndexed());
			stmt.setInt(7, u.getId());
			
			Integer i = stmt.executeUpdate();
			
			if (i != 1) 
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
	 * Deletes a user
	 * 
	 * @param u
	 * @throws SQLException 
	 * @throws DatabaseException 
	 */
	public void DeleteUser(User u) throws SQLException, DatabaseException
	{
		db.beginTransaction();
		PreparedStatement stmt = null;
		try
		{
			String query = "delete from user where user_id = ? ";
			stmt = db.getConn().prepareStatement(query);
			stmt.setInt(1, u.getId());
			if (stmt.executeUpdate() != 1) 
			{
				throw new DatabaseException();
			}
		} catch (SQLException e)
		{
			// TODO Auto-generated catch block
			db.endTransaction(false);
			throw e;
		}
		db.endTransaction(true);
		
	}

}