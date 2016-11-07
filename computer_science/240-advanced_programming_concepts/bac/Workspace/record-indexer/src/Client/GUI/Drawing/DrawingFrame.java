package Client.GUI.Drawing;


import java.awt.*;

import javax.swing.*;

@SuppressWarnings("serial")
public class DrawingFrame extends JPanel {

	public DrawingComponent component;
//	private JSlider slider;
	
	public DrawingFrame ()
	{
		this.setBackground(Color.gray);
	}
	
	public DrawingFrame(String imageURL, boolean isNav) {

//		this.setTitle("Drawing");
		
//		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
		
		component = new DrawingComponent(imageURL, isNav);
		this.add(component);
		
		this.setBackground(Color.gray);

		
//		this.setLocation(100, 100);

//		this.pack();
	}
	
	public void setOrigin(int w_newOriginX, int w_newOriginY) {
		component.setOrigin(w_newOriginX, w_newOriginY);
	}
	
	public void addDrawingListener(DrawingListener listener) {
		component.addDrawingListener(listener);
	}
//	
//	private ChangeListener sliderChangeListener = new ChangeListener() {
//		
//		@Override
//		public void stateChanged(ChangeEvent e) {
//			component.setScale(slider.getValue() * 0.05);
//		}
//	};
	
}