/**
* @file Paint.java
*
* @brief This file contains the abstract Paint class.
*
* @author Philipp Bank, www.cypax.net\n
*
* @date June, 18th 2006 - first version
*
**/

import java.awt.*;
import java.util.*;

/**
* @class Paint
* @brief This abstract class provides a static showArray() function to visualize the integer arrays.
*/
abstract class Paint
{

/**
* @brief This function is used to visualize the integer numbers of a array by painting the numbers as vertical green lines.
* @param aArray - the array with interger numbers
* @param aPanel - the Panel, where the lines will be painted on
*/
  public static void showArray(int[] aArray, Panel aPanel)
  {
    Graphics g = aPanel.getGraphics();   //get the graphical context of the panel
    Color lc = new Color(0,255,0);       //new green color
    Color bc = new Color(128,128,128);   //the background color

    for (int i=0; i<210; i++)
    {
      g.setColor(lc);
      g.drawLine((i+20),190,(i+20),(190-aArray[i]));  //draw a vertical green line, the lenght of this line depends on the integer value in the array at index i
      g.setColor(bc);
      g.drawLine((i+20),(190-aArray[i]),(i+20),10);  //draw a vertical line in background color
    }

    aPanel.validate(); //repaint the panel
  }

}

