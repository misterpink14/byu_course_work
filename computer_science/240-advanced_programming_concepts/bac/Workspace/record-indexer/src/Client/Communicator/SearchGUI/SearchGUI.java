package Client.Communicator.SearchGUI;

import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.imageio.ImageIO;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTextField;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreePath;

import Shared.Communication.Param.GetFields_Param;
import Shared.Communication.Param.GetProjects_Param;
import Shared.Communication.Param.Search_Param;
import Shared.Communication.Result.GetFields_Result;
import Shared.Communication.Result.GetProjects_Result;
import Shared.Communication.Result.Search_Result;
import Shared.Model.Field;
import Shared.Model.Image;
import Shared.Model.Project;
import Shared.Model.Record;
import Client.Communicator.ClientCommunicator;
import Client.Communicator.ClientCommunicatorException;

@SuppressWarnings("serial")
public class SearchGUI extends JFrame 
{
	public ClientCommunicator comm = new ClientCommunicator();
	static SearchGUI s;
	Map<Project, List<Field>> projectList = new HashMap<Project, List<Field>>();
	JSplitPane rightPane;
	JTree tree;
	TreePath[] tPath;
	JPanel search;
	JTextField text;
	String searchParam = null;
	JPanel fill;
	String user;
	String pass;
	
	
	public SearchGUI()
	{
		initUI();
	}
	
	private void initUI()
	{
		setTitle("Search GUI");
		setSize(1000,750);
		createMenuBar();
		createLoginScreen();
		setLocationRelativeTo(null);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	private void createProjectList(String user, String pass, List<Project> projectList) throws IOException, ClientCommunicatorException
	{
		this.user = user;
		this.pass = pass;
		JPanel flow = new JPanel();
        flow.setLayout(new FlowLayout());
        DefaultMutableTreeNode root = new DefaultMutableTreeNode("Project List");
        

		for (Project proj : projectList)
		{
			DefaultMutableTreeNode child = new DefaultMutableTreeNode(proj.getTitle());
			GetFields_Param p = new GetFields_Param(user, pass, proj.getId());
			GetFields_Result r = comm.GetFields(p);
			for (Field f : r.getFieldList())
			{
				addField(proj, f);
				DefaultMutableTreeNode subChild = new DefaultMutableTreeNode(f.getTitle());
				child.add(subChild);
			}
			root.add(child);
		}
		tree = new JTree(root);
		flow.add(tree);
		
		rightPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
		JPanel next = new JPanel();
		next.setLayout(new BoxLayout(next, BoxLayout.PAGE_AXIS));
		next.add(new JLabel("Select the fields you wish to search and add your search parameters"));
		search = new JPanel();
		search.setLayout(new BoxLayout(search, BoxLayout.LINE_AXIS));
		JPanel p = new JPanel();
		p.add(new JLabel("Search Fields: "));
		search.add(p);
		newSearchField(search);
		p = new JPanel();
		JButton addField = new JButton("Add");
		addField.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e)
			{
				addSearchParam();
			}
			
		});
		p.add(addField);
		JButton sumbit = new JButton("Search");
		sumbit.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e)
			{
				try
				{
					search();
				} catch (IOException e1)
				{
					System.out.println(e1.getMessage());
				} catch (ClientCommunicatorException e1)
				{
					System.out.println(e1.getMessage());
				}
			}
			
		});
		p.add(sumbit);
		search.add(p);
		next.add(search);
		rightPane.add(next);
		fill = new JPanel();
		rightPane.add(fill);
		tree.addTreeSelectionListener(new TreeSelectionListener() {
		    public void valueChanged(TreeSelectionEvent e) {
		        DefaultMutableTreeNode node = (DefaultMutableTreeNode)
		                           tree.getLastSelectedPathComponent();
		        /* if nothing is selected */ 
		        if (node == null) 
		        {
		        	return;
		        }
		        if(e.isAddedPath() && node.isLeaf())
		        {
			        tPath = tree.getSelectionPaths();
		        }
		    }
		});
		
		JScrollPane pane = new JScrollPane(flow);
		JSplitPane splitPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT,
                pane, rightPane);
		s.add(splitPane);
	}
	
	private void search() throws IOException, ClientCommunicatorException
	{
		String s = null;
		for (TreePath t: tPath)
		{
			Integer i = findFieldID(t.getLastPathComponent().toString(), t.getParentPath().getLastPathComponent().toString());
			if (s == null)
			{
				s = i.toString() + ",";
			}
			else
			{
				s = s + i.toString() + ",";
			}
		}
		s = s.substring(0, s.length()-1);

		Search_Param p = new Search_Param(user, pass, s, searchParam.substring(0, searchParam.length()-1));
		Search_Result r = comm.Search(p);
		r.getResultsList();
		
		fill.setLayout(new FlowLayout());
		
		
		String[] sList = new String[r.getResultsList().size()]; 
		int i = 0;
		for (Map.Entry<Image, List<Record>> temp : r.getResultsList().entrySet())
		{
			sList[i] = temp.getKey().getFile();
			i++;
		}
		JList list = new JList(sList);
		list.addMouseListener(new MouseAdapter() {
		    public void mouseClicked(MouseEvent evt) 
		    {
		        JList list = (JList)evt.getSource();
		        if (evt.getClickCount() > 1) 
		        {
		        	
		        	System.out.println(list.getSelectedValue().toString());
		            new ImageScreen(list.getSelectedValue().toString());
		        }
		    }
		});
		fill.add(list);
		fill.updateUI();
	}
	
	private Integer findFieldID(String fieldTitle, String projectTitle)
	{
		Integer i = null;
		for (Map.Entry<Project, List<Field>> temp : this.projectList.entrySet())
		{
			if (temp.getKey().getTitle().trim().equals(projectTitle.trim()))
			{
				for (Field f : temp.getValue())
				{
					if (f.getTitle().trim().equals(fieldTitle.trim()))
					{
						i = f.getId();
						break;
					}
				}
			}
		}
		return i;
	}
	
	private void addSearchParam()
	{
		if (!text.getText().equals(""))
		{
			if (searchParam == null)
			{
				searchParam = text.getText() + ",";
			}
			else
			{
				searchParam = searchParam + text.getText() + ",";
			}
		}
	}
		
	private void newSearchField(JPanel search)
	{
		JPanel p = new JPanel();
		text = new JTextField(8);
		p.add(text);
		search.add(p);
	}
	
	private void addField(Project p, Field f)
	{
		if (projectList.containsKey(p))
		{
			List<Field> fList = projectList.get(p);
			fList.add(f);
		}
		else
		{
			List<Field> fList = new ArrayList<Field>();
			fList.add(f);
			projectList.put(p, fList);
		}
	}
	
	private void createMenuBar()
	{
		JMenuBar menu = new JMenuBar();
		JMenu file = new JMenu("File");
		file.setMnemonic(KeyEvent.VK_E);
		
		JMenuItem menuItem = new JMenuItem("Exit");
		menuItem.setMnemonic(KeyEvent.VK_E);
		menuItem.addActionListener(new ActionListener()
		{
			@Override
            public void actionPerformed(ActionEvent event) {
                System.exit(0);
            }
		});
		JMenuItem menuItem2 = new JMenuItem("Reset Search");
		menuItem2.setMnemonic(KeyEvent.VK_E);
		menuItem2.addActionListener(new ActionListener()
		{
			@Override
            public void actionPerformed(ActionEvent event) {
                searchParam = null;
            }
		});
		file.add(menuItem);
		file.add(menuItem2);
		menu.add(file);
		setJMenuBar(menu);
		
		
	}
	
	private void createLoginScreen()
	{
		LoginScreen login = new LoginScreen();
		
	}
	
	public static void main(String[] args)
	{
		 EventQueue.invokeLater(new Runnable() {
		        
	            @Override
	            public void run() {
	            	s = new SearchGUI();
	                //ex.setVisible(true);
	            }
	        });
	}
	
	
	private class LoginScreen extends JDialog
	{
		
		JTextField host;
        JTextField port;
        JTextField user;
        JPasswordField pass;
        
		protected LoginScreen()
		{
			initLogin();
		}
		
		private void initLogin()
		{
			JPanel basic = new JPanel();
	        basic.setLayout(new BoxLayout(basic, BoxLayout.Y_AXIS));
	        add(basic);

	        basic.add(Box.createVerticalGlue());

	        JPanel top1 = new JPanel();
	        JPanel top2 = new JPanel();
	        JPanel bottom1 = new JPanel();
	        JPanel bottom2 = new JPanel();

	        host = new JTextField(8);
	        port = new JTextField(8);
	        user = new JTextField(8);
	        pass = new JPasswordField(8);
	        JButton login = new JButton("Login");
	        login = new JButton("Login");
	        login.addActionListener(new loginButtonListener());
	        
	        host.setText("localhost");
	        port.setText("6989");
	        user.setText("sheila");
	        pass.setText("parker");

	        top1.add(new JLabel("Host: "));
	        top1.add(host);
	        top2.add(new JLabel("Port: "));
	        top2.add(port);

	        bottom1.add(new JLabel("User Name: "));
	        bottom1.add(user);
	        bottom2.add(new JLabel("Password: "));
	        bottom2.add(pass);

	        basic.add(top1);
	        basic.add(top2);
	        basic.add(bottom1);
	        basic.add(bottom2);
	        basic.add(login);

	        setTitle("Login");
	        setSize(250, 230);
	        setLocationRelativeTo(null);
			setVisible(true);
		}
		
		private boolean validateUser() throws IOException, ClientCommunicatorException
		{
			comm.urlBase = "http://" + host.getText() + ":" + port.getText() + "/";
			GetProjects_Param p = new GetProjects_Param(user.getText(), pass.getSelectedText());
			GetProjects_Result r = comm.GetProjects(p);
			s.createProjectList(p.getUser(), p.getPass(), r.getProjectList());
			return r.getSuccess();
		}

		public class loginButtonListener implements ActionListener
		{

			@Override
			public void actionPerformed(ActionEvent e)
			{
				try
				{
					if (validateUser())		//check the username here
					{
						setVisible(false);
						s.setVisible(true);
					}
				} catch (IOException e1)
				{
				} catch (ClientCommunicatorException e1)
				{
				}
			}
			
		}
	}
	
	private class ImageScreen extends JDialog
	{
        
		protected ImageScreen(String image)
		{
			initLogin(image);
		}
		
		private void initLogin(String path)
		{
            URL url = null;
			try
			{
				url = new URL(path);
			} catch (MalformedURLException e)
			{
			}
            BufferedImage image = null;
			try
			{
				image = ImageIO.read(url);
			} catch (IOException e)
			{
			}
            JLabel label = new JLabel(new ImageIcon(image));
            JFrame f = new JFrame();
            f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            f.getContentPane().add(label);
            f.pack();
            f.setVisible(true);
			setVisible(true);
		}
	}
}
