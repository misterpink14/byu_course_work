package Server.DatabaseAccess.Database;


import java.io.*;
import java.sql.*;

public class Database
{
	private static final String DATABASE_DIRECTORY = "database";
	private static final String DATABASE_FILE = "record-indexer.sqlite";
	private static final String DATABASE_URL = "jdbc:sqlite:" + DATABASE_DIRECTORY +
												File.separator + DATABASE_FILE;
	
	private Connection conn;
	private Statement stmt;

	/**
	 * Constructor
	 */
	public Database ()
	{
		conn = null;
		stmt = null;
	}
	
	/**
	 * @return the conn
	 */
	public Connection getConn()
	{
		return conn;
	}

	/**
	 * @return the stmt
	 */
	public Statement getStmt()
	{
		return stmt;
	}	

	/**
	 * Registers the JDBC driver
	 * 
	 * @throws ClassNotFoundException
	 */
	public static void init() throws ClassNotFoundException
	{
		// Register JDBC driver
		final String driver = "org.sqlite.JDBC";
		try
		{
			Class.forName(driver);
			
		} catch (ClassNotFoundException e)
		{
			throw e;
			
		}
	}
	
	/**
	 * Opens a connection to the database and starts the transaction
	 * 
	 */
	public void beginTransaction()
	{
		// Open a connection
		this.connect();
		try
		{
			this.conn.setAutoCommit(false);
		} catch (SQLException e)
		{
			e.printStackTrace();
		}
	}
	
	/**
	 * Opens a connextion to the database
	 * 
	 */
	public void connect()
	{
		try
		{
			this.conn = DriverManager.getConnection(DATABASE_URL);
			
		} catch (SQLException e)
		{
			e.printStackTrace();
		}
	}
	
	/**
	 * Commits or rolls back a transaction. also closes any needed connections.
	 * 
	 * @param commit
	 * @throws SQLException
	 */
	public void endTransaction(boolean commit) throws SQLException
	{
		try
		{
			if (commit)
			{
				this.conn.commit();
			}
			else 
			{
				this.conn.rollback();
			}
		} catch (SQLException e)
		{
		}
		try
		{
			if (stmt != null && !stmt.isClosed())
				stmt.close();
		} catch (SQLException e)
		{
		}
		try
		{
			if(conn != null && !conn.isClosed())
				conn.close();
		} catch (SQLException e)
		{
		}
	}
	
	/**
	 * Use to close connections. Old code, not currently in use...
	 * 
	 */
	public void close()
	{
		try
		{
			if (stmt != null && !stmt.isClosed())
				stmt.close();
		} catch (SQLException e)
		{
		}
		try
		{
			if(!conn.isClosed())
				conn.close();
		} catch (SQLException e)
		{
		}
	}
	
	/**
	 * Clears the database.
	 * 
	 * @throws SQLException
	 */
	public static void erase() throws SQLException 
	{
		Database database = new Database();
		database.beginTransaction();
		database.voidQuery("delete from user;");
		database.voidQuery("delete from project;");
		database.voidQuery("delete from record;");
		database.voidQuery("delete from image;");
		database.voidQuery("delete from field;");
		database.endTransaction(true);
	}
	  
	/**
	 * Creates and executes a batch from a given sql statement
	 * 
	 * @param sql
	 * @throws SQLException
	 */
	public void voidQuery(String sql) throws SQLException 
	{
		Statement statement;
		try {
			statement = conn.createStatement();
			statement.addBatch(sql);
			statement.executeBatch();
		} catch (SQLException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * Old code for erasing, not currently in use...
	 * 
	 * @param table
	 * @throws SQLException
	 */
	public void clearTable(String table) throws SQLException
	{
		try
		{
			String sql = "delete from " + table;
			stmt.executeUpdate(sql);
		}
		catch (SQLException e)
		{
			throw e;
		}
	}
	

}
