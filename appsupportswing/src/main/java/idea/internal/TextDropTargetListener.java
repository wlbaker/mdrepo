/*
 * Created on Nov 1, 2006
 *
 */
package idea.internal;

import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.dnd.DnDConstants;
import java.awt.dnd.DropTargetDragEvent;
import java.awt.dnd.DropTargetDropEvent;
import java.awt.dnd.DropTargetEvent;
import java.awt.dnd.DropTargetListener;
import java.io.File;
import java.util.Iterator;

import javax.swing.JComponent;

class TextDropTargetListener implements DropTargetListener {
    JComponent comp;
    
    public TextDropTargetListener(JComponent ta) {
      comp = ta;
    }

    public void dragEnter(DropTargetDragEvent event) {
      // int a = event.getDropAction();
      //if ((a & DnDConstants.ACTION_COPY) != 0)
      //if ((a & DnDConstants.ACTION_MOVE) != 0)
      //if ((a & DnDConstants.ACTION_LINK) != 0)

      //System.out.println("ACTION: " + textArea );
      if (!isDragAcceptable(event)) {
        event.rejectDrag();
        return;
      }
    }

    public void dragExit(DropTargetEvent event) { }

    public void dragOver(DropTargetDragEvent event) {
        // you can provide visual feedback here
    }

    public void dropActionChanged(DropTargetDragEvent event) {
      if (!isDragAcceptable(event)) {
        event.rejectDrag();
        return;
      }
    }

    public void drop(DropTargetDropEvent event) {
        
      if (!isDropAcceptable(event)) {
        event.rejectDrop();
        return;
      }

      event.acceptDrop(DnDConstants.ACTION_COPY);

      Transferable transferable = event.getTransferable();

      DataFlavor[] flavors = transferable.getTransferDataFlavors();
      for (int i = 0; i < flavors.length; i++) {
        DataFlavor d = flavors[i];
        // textArea.append("MIME type=" + d.getMimeType() + "\n");

        try {
          if (d.equals(DataFlavor.javaFileListFlavor)) {
            java.util.List fileList = (java.util.List) transferable
                .getTransferData(d);
            Iterator iterator = fileList.iterator();
            if(iterator.hasNext()) {
              File f = (File) iterator.next();
              System.err.println( "LOAD IMAGE FROM FILE IS HERE");
              // loadImageFromFile( f );
            }
          } else if (d.equals(DataFlavor.stringFlavor)) {
          } else if (d.isMimeTypeEqual("text/plain")) {
          }
        } catch (Exception e) {
          e.printStackTrace();
        }
      }
      
      event.dropComplete(true);
    }

    public boolean isDragAcceptable(DropTargetDragEvent event) { // usually, you
                                   // check the
                                   // available
                                   // data flavors
                                   // here
      // in this program, we accept all flavors
      return (event.getDropAction() & DnDConstants.ACTION_COPY_OR_MOVE) != 0;
    }

    public boolean isDropAcceptable(DropTargetDropEvent event) { // usually, you
                                   // check the
                                   // available
                                   // data flavors
                                   // here
      // in this program, we accept all flavors
      return (event.getDropAction() & DnDConstants.ACTION_COPY_OR_MOVE) != 0;
    }
}
