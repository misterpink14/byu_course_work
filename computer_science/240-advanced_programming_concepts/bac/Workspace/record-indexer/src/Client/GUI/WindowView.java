package Client.GUI;


import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JSplitPane;
import javax.swing.JToolBar;

import Client.Controller;
import Client.GUI.Drawing.DrawingFrame;
import Client.GUI.Entry.EntryView;
import Client.GUI.ImageSupport.ImageSupportView;

@SuppressWarnings("serial")
public class WindowView extends JFrame 
{
	public DownloadBatchView downloadbatch;
	public DrawingFrame top;
	public ImageSupportView bottomRight;
	public JSplitPane basic;
	public JSplitPane bottom;
	public EntryView bottomLeft;
	JMenuItem downloadBatch;
	JButton button;
    
	public WindowView()
	{
		initUI();
	}
		
	private void initUI()
	{
		
		basic = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
		basic.setDividerLocation(450);
		
		top = new DrawingFrame();
		top.setPreferredSize(new Dimension(350, 1000));
		bottom = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		bottom.setDividerLocation(400);
//		bottom.setLayout(new BoxLayout(bottom, BoxLayout.LINE_AXIS));
//		bottom.setPreferredSize(new Dimension(this.getWidth(), 400));
		
		bottomLeft = new EntryView();
		bottomRight = new ImageSupportView();
		bottomRight.setPreferredSize(new Dimension(600, 200));
		bottomLeft.setPreferredSize(new Dimension(400, 200));
		
		bottom.setLeftComponent(bottomLeft);
		bottom.setRightComponent(bottomRight);
		
		add(basic);
        basic.setLeftComponent(top);
        basic.setRightComponent(bottom);

        this.addMouseWheelListener(new MouseWheelListener()
        {

			@Override
			public void mouseWheelMoved(MouseWheelEvent e)
			{
				int notches = e.getWheelRotation();
				if (notches < 0 && Controller.imageURL != null)
				{
					Controller.zoomIn();
				}
				else
				{
					Controller.zoomOut();
				}
			}	
        });
        
        createMenuBar();
        buildToolbar();
        setVisible(false);
        setTitle("Record Indexer");
        setSize(1000, 750);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	public void reset()
	{
		basic = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
		basic.setDividerLocation(450);
		
		top = new DrawingFrame();
		bottom = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);
		bottom.setDividerLocation(400);
		
		bottomLeft = new EntryView();
		bottomRight = new ImageSupportView();
		
		bottom.setLeftComponent(bottomLeft);
		bottom.setRightComponent(bottomRight);
		
		add(basic);
        basic.setLeftComponent(top);
        basic.setRightComponent(bottom);

        this.addMouseWheelListener(new MouseWheelListener()
        {

			@Override
			public void mouseWheelMoved(MouseWheelEvent e)
			{
				int notches = e.getWheelRotation();
				if (notches < 0 && Controller.imageURL != null)
				{
					Controller.zoomIn();
				}
				else
				{
					Controller.zoomOut();
				}
			}
        });
        
        createMenuBar();
        buildToolbar();
        setVisible(true);
        setTitle("Record Indexer");
        setSize(1000, 750);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	public void hideMenu()
	{
		downloadBatch.setEnabled(false);
	}

	private void createMenuBar()
	{
		JMenuBar menu = new JMenuBar();
		JMenu file = new JMenu("File");
		file.setMnemonic(KeyEvent.VK_E);
		
		downloadBatch = new JMenuItem("Download Batch");
		downloadBatch.setMnemonic(KeyEvent.VK_E);
		downloadBatch.addActionListener(new ActionListener()
		{
			@Override
            public void actionPerformed(ActionEvent event) 
			{
				downloadbatch = new DownloadBatchView();
            }
		});
		file.add(downloadBatch);
		
		JMenuItem menuItem = new JMenuItem("Logout");
		menuItem.setMnemonic(KeyEvent.VK_E);
		menuItem.addActionListener(new ActionListener()
		{
			@Override
            public void actionPerformed(ActionEvent event) {
                Controller.logout();
            }
		});
		file.add(menuItem);
		
		menuItem = new JMenuItem("Exit");
		menuItem.setMnemonic(KeyEvent.VK_E);
		menuItem.addActionListener(new ActionListener()
		{
			@Override
            public void actionPerformed(ActionEvent event) {
                System.exit(0);
            }
		});
		file.add(menuItem);
		menu.add(file);
		setJMenuBar(menu);
	}
	
	private void buildToolbar()
	{
		JToolBar toolbar = new JToolBar();
		
//		toolbar.setAlignmentX((float) 0.0);

		button = new JButton("Zoom In");
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                Controller.zoomIn();
            }
        });
        toolbar.add(button);

        button = new JButton("Zoom Out");
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                Controller.zoomOut();
            }
        });
        toolbar.add(button);
        
        button = new JButton("Invert Image");
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                Controller.invert();
            }
        });
        toolbar.add(button);
        
        button = new JButton("Toggle Highlights");
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
//                System.exit(0);
            }
        });
        toolbar.add(button);

        button = new JButton("Save");
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
//                System.exit(0);
            }
        });
        toolbar.add(button);
        

        button = new JButton("Submit");
        button.setEnabled(false);
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                Controller.submitBatch();
            }
        });
        toolbar.add(button);

        add(toolbar, BorderLayout.NORTH);  
	}
	
	public void enableSumbit()
	{
		button.setEnabled(true);
	}
}