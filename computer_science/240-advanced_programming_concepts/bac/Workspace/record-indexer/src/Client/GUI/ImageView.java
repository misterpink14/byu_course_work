package Client.GUI;

import java.awt.Color;

import javax.swing.JPanel;

@SuppressWarnings("serial")
public class ImageView extends JPanel
{
	public ImageView()
	{
		initUI();
		revalidate();
		repaint();
	}
	
	public void initUI()
	{
		this.setBackground(Color.gray);
	}

	
}
