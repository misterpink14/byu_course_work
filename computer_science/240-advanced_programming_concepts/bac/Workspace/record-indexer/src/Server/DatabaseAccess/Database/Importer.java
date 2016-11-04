/**
 * 
 */
package Server.DatabaseAccess.Database;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import Server.DatabaseAccess.FieldDBAccess;
import Server.DatabaseAccess.ImageDBAccess;
import Server.DatabaseAccess.ProjectDBAccess;
import Server.DatabaseAccess.RecordDBAccess;
import Server.DatabaseAccess.UserDBAccess;
import Shared.Model.Field;
import Shared.Model.Image;
import Shared.Model.Project;
import Shared.Model.Record;
import Shared.Model.User;

/**
 * @author Benjamin Thompson
 *
 */
public class Importer
{
	private final String FILESURL = "filesURL/";
	
	public Importer() throws ClassNotFoundException, SQLException
	{
		Database.init();
		Database.erase();
	}

	/**
	 * Main Static method to run an instance of the Importer
	 * 
	 * @param args
	 * @throws ParserConfigurationException 
	 * @throws IOException 
	 * @throws SAXException 
	 * @throws SQLException 
	 * @throws ClassNotFoundException 
	 * @throws DatabaseException 
	 */
	public static void main(String[] args) throws SAXException, IOException, ParserConfigurationException, ClassNotFoundException, SQLException, DatabaseException
	{
		new Importer().execute(args[0]);
	}
	
	/**
	 * Imports the given xml file
	 * 
	 * @param fileURL
	 * @throws SAXException
	 * @throws IOException
	 * @throws ParserConfigurationException
	 * @throws DatabaseException 
	 * @throws SQLException 
	 */
	public void execute(String fileURL) throws SAXException, IOException, ParserConfigurationException, SQLException, DatabaseException
	{
		File f = new File(fileURL);
		File parent = f.getParentFile();
		File newP = new File(this.FILESURL);
		if (newP.exists())
		{
			this.deleteDirectory(newP);
		}
		for (File baby: parent.listFiles())
		{
			if(baby.isDirectory())
			{
				this.copyFolder(baby, newP);
			}
		}
		
		DocumentBuilder docb = DocumentBuilderFactory.newInstance().newDocumentBuilder();
		Document doc = docb.parse(f);
		
		NodeList userNL = doc.getElementsByTagName("user");
		for (int i = 0; i < userNL.getLength(); i++)
		{
			Element userElm = (Element)userNL.item(i);
			
			parseUserXML(userElm);
		}
		
		NodeList projectNL = doc.getElementsByTagName("project");
		for (int i = 0; i < projectNL.getLength(); i++)
		{
			Element projectElm = (Element)projectNL.item(i);

			Integer projectID = parseProjectXML(projectElm);
			
			NodeList fieldNL = projectElm.getElementsByTagName("field");
			List<Integer> fieldIDs = new ArrayList<Integer>();
			for (int j = 0; j < fieldNL.getLength(); j++)
			{
				Element fieldElm = (Element)fieldNL.item(j);

				fieldIDs.add(parseFieldXML(fieldElm, projectID));
			}
			
			NodeList imageNL = projectElm.getElementsByTagName("image");
			for (int j = 0; j < imageNL.getLength(); j++)
			{
				Element imageElm = (Element)imageNL.item(j);

				parseImageXML(imageElm, projectID, fieldIDs);
			}
		}
	}
	
	/**
	 * 
	 * @param parent
	 * @throws IOException 
	 */
	@SuppressWarnings("resource")
	public void copyFolder(File oldP, File newP) throws IOException
	{
		try
		{
			File dir = new File(newP.getAbsolutePath()+"/"+oldP.getName());
			dir.mkdir();
			for (File ff: oldP.listFiles())
			{
				if (ff.isDirectory())
				{
					continue;
				}
				File file = new File(dir.getAbsolutePath()+"/"+ff.getName());
				FileChannel source = null;
			    FileChannel destination = null;

		        source = new FileInputStream(ff).getChannel();
		        destination = new FileOutputStream(file).getChannel();
		        destination.transferFrom(source, 0, source.size());
			}
		} catch (IOException e)
		{
			e.printStackTrace();
			throw e;
		}
		
	}
	
	public void deleteDirectory(File dir)
	{
		for (File f: dir.listFiles())
		{
			if (f.isDirectory())
			{
				this.deleteDirectory(f);
			}
			f.delete();
		}
	}
	
	/**
	 * Used to parse user XML
	 * 
	 * @param userElm
	 */
	public void parseUserXML(Element userElm)
	{
		String user = userElm.getElementsByTagName("username").item(0).getTextContent();
		String pass = userElm.getElementsByTagName("password").item(0).getTextContent();
		String first = userElm.getElementsByTagName("firstname").item(0).getTextContent();
		String last = userElm.getElementsByTagName("lastname").item(0).getTextContent();
		String email = userElm.getElementsByTagName("email").item(0).getTextContent();
		Integer indexed = Integer.parseInt(userElm.getElementsByTagName("indexedrecords").item(0).getTextContent());
		
		UserDBAccess dba = new UserDBAccess();
		try
		{
			dba.CreateUser(new User(user, pass, first, last, email, indexed));
		} catch (SQLException e)
		{
			e.printStackTrace();
			System.out.println("Failed to add " + user);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			System.out.println("Failed to add " + user);
		}
	}
	
	/**
	 * Used to parse project xml
	 * 
	 * @param projectElm
	 * @return
	 */
	public Integer parseProjectXML(Element projectElm)
	{
		String title = projectElm.getElementsByTagName("title").item(0).getTextContent();
		Integer records = Integer.parseInt(projectElm.getElementsByTagName("recordsperimage").item(0).getTextContent());
		Integer firsty = Integer.parseInt(projectElm.getElementsByTagName("firstycoord").item(0).getTextContent());
		Integer height = Integer.parseInt(projectElm.getElementsByTagName("recordheight").item(0).getTextContent());
		Project p = new Project(title, records, firsty, height);
		
		ProjectDBAccess dba = new ProjectDBAccess();
		try
		{
			dba.CreateProject(p);
		} catch (SQLException e)
		{
			e.printStackTrace();
		} catch (DatabaseException e)
		{
			e.printStackTrace();
		}
		return p.getId();
	}
	
	/**
	 * Used to parse field xml
	 * 
	 * @param fieldElm
	 * @param projectID
	 */
	public Integer parseFieldXML(Element fieldElm, Integer projectID)
	{
		String title = fieldElm.getElementsByTagName("title").item(0).getTextContent();
		Integer xcoord = Integer.parseInt(fieldElm.getElementsByTagName("xcoord").item(0).getTextContent());
		Integer width = Integer.parseInt(fieldElm.getElementsByTagName("width").item(0).getTextContent());
		String help = fieldElm.getElementsByTagName("helphtml").item(0).getTextContent();
		String known = null;
		try
		{
			known = fieldElm.getElementsByTagName("knowndata").item(0).getTextContent();
		}
		catch (NullPointerException e)
		{
			known = null;
		}
		
		FieldDBAccess dba = new FieldDBAccess();
		Field f = null;
		try
		{
			f = new Field(title, xcoord, width, help, known, projectID);
			dba.CreateField(f);
		} catch (SQLException e)
		{
			e.printStackTrace();
			System.out.println("Failed to add " + title);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			System.out.println("Failed to add " + title);
		}
		return f.getId();
	}
	
	/**
	 * Used to parse image xml
	 * 
	 * @param imageElm
	 * @param projectID
	 * @throws DatabaseException 
	 * @throws SQLException 
	 */
	public void parseImageXML(Element imageElm, Integer projectID, List<Integer> fieldIDs) throws SQLException, DatabaseException
	{

		String file = imageElm.getElementsByTagName("file").item(0).getTextContent();
		
		ImageDBAccess dba = new ImageDBAccess();
		Image i = null;
		try
		{
			i = new Image(file, projectID, -1);
			dba.CreateImage(i);
		} catch (SQLException e)
		{
			e.printStackTrace();
			System.out.println("Failed to add " + file);
		} catch (DatabaseException e)
		{
			e.printStackTrace();
			System.out.println("Failed to add " + file);
		}
		if (imageElm.getElementsByTagName("record").getLength() > 0)
		{
			NodeList recordNL = imageElm.getElementsByTagName("record");
			
			for (int j = 0; j < recordNL.getLength(); j++)
			{
				Element recordElm = (Element)recordNL.item(j);

				parseRecordXML(recordElm, i.getId(), fieldIDs, j);
			}
			i.setUserID(-2);
			dba.UpdateImage(i);
		}
	}
	
	public void parseRecordXML(Element recordElm, Integer imageID, List<Integer> fieldIDs, int row) throws SQLException, DatabaseException
	{
		NodeList valueNL = recordElm.getElementsByTagName("value");
		RecordDBAccess rdb = new RecordDBAccess();
		for (int j = 0; j < valueNL.getLength(); j++)
		{
			Record r = null;
			Element valueElm = (Element)valueNL.item(j);
			
			String value = valueElm.getTextContent();
			r = new Record(value, row, imageID, fieldIDs.get(j));
			
			rdb.CreateRecord(r);
		}
	}
	

}
