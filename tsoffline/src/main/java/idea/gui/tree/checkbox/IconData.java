package idea.gui.tree.checkbox;

import java.awt.Color;

import javax.swing.Icon;

public class IconData {
	protected Icon m_icon;
	protected Icon m_expandedIcon;
	protected Object m_data;
	protected Color m_color;

	public IconData(Icon icon, Object data) {
		this( icon, null, data, null );
	}

	public IconData(Icon icon, Icon expandedIcon, Object data) {
		this( icon, expandedIcon, data, null );
	}
	
	public IconData(Icon icon, Icon expandedIcon, Object data, Color color) {
		m_icon = icon;
		m_expandedIcon = expandedIcon;
		m_data = data;
		m_color = color;
	}

	public Icon getIcon() {
		return m_icon;
	}

	public Icon getExpandedIcon() {
		return m_expandedIcon != null ? m_expandedIcon : m_icon;
	}

	public Object getObject() {
		return m_data;
	}

	public Color getColor() {
		return m_color;
	}

	public String toString() {
		return m_data.toString();
	}

	public void setColor(Color color) {
		this.m_color = color;
	}
}

