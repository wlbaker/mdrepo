package example;

/*
* Copyright (c) 2008-2011, Piccolo2D project, http://piccolo2d.org
* Copyright (c) 1998-2008, University of Maryland
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided
* that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this list of conditions
* and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions
* and the following disclaimer in the documentation and/or other materials provided with the
* distribution.
*
* None of the name of the University of Maryland, the name of the Piccolo2D project, or the names of its
* contributors may be used to endorse or promote products derived from this software without specific
* prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import java.awt.Color;
import java.util.ListIterator;

import org.piccolo2d.PCamera;
import org.piccolo2d.PCanvas;
import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;
import org.piccolo2d.extras.PFrame;
import org.piccolo2d.extras.handles.PBoundsHandle;
import org.piccolo2d.nodes.PPath;

/**
 * This example shows how to create internal cameras
 */
public class CameraExample extends PFrame {

	/**
	* 
	*/
	private static final long serialVersionUID = 1L;

	public CameraExample() {
		this(null);
	}

	public CameraExample(final PCanvas aCanvas) {
		super("CameraExample", false, aCanvas);
	}

	public void initialize() {
		final PLayer l = new PLayer();
		final PLayer l2 = new PLayer();
		l2.setName("parent");
		l.setName("layer");
		final PPath n = PPath.createEllipse(0, 0, 100, 80);
		n.setName("ellipse");
		n.setPaint(Color.red);
		n.setStroke(null);
		PBoundsHandle.addBoundsHandlesTo(n);
		l.addChild(n);
		n.translate(200, 200);

		final PCamera c = new PCamera();
		c.setName("camera");
		c.setBounds(0, 0, 100, 80);
		c.scaleView(0.1);
		c.addLayer(l);
		
		l.setParent( l2 );
		PBoundsHandle.addBoundsHandlesTo(c);
		c.setPaint(Color.yellow);

		 System.out.println( "l1 parent=" + l.getParent() );
		getCanvas().getLayer().addChild(l);
		 System.out.println( "l1 parent=" + l.getParent() );
		getCanvas().getLayer().addChild(c);
		 System.out.println( "l1 parent=" + l.getParent() );
		 
		 System.out.println("canvas layer=" + getCanvas().getLayer() );
		 
		ListIterator it = getCanvas().getLayer().getChildrenIterator();
		while( it.hasNext() ) {
			 PNode node = (PNode) it.next();
			 PNode parent = node.getParent();
			 String parentName = (parent == null) ? null : parent.getName();
			 System.out.println( "node=" + node + " name=" + node.getName() + " parent=" + parentName );
		}
		 System.out.println( "l1 parent=" + l.getParent() );
	}

	public static void main(final String[] args) {
		new CameraExample();
	}
}