package idea;


import lombok.extern.slf4j.Slf4j;

/**
 Custom handler for any uncaught exceptions.
 
 <P>By default, a Swing app will handle uncaught exceptions simply by 
  printing a stack trace to {@link System#err}. However, the end user will 
  not usually see that, and if they do, they will not likely understand it. 
  This class addresses that problem, by showing the end user a 
  simple error message in a modal dialog. (The dialog's owner is the 
  currently active frame.)
*/
@Slf4j
public final class GuiUncaughtExceptionHandler implements Thread.UncaughtExceptionHandler {

	private static boolean enableNotification = true;
  /** 
  Custom handler for uncaught exceptions.
  
  <P>Displays a simple model dialog to the user, showing that an error has
   occured. The text of the error includes {@link Throwable#toString()}. 
   The stack trace is logged at a SEVERE level.
 */
  @Override  public void uncaughtException(Thread aThread, Throwable aThrowable) {
    log.error( "uncaught", aThrowable );
    if( enableNotification ) {
    	GuiUtil.showError("Exception found in: " + aThread.getName(), aThrowable);
    }
  }
  
  public static void enableNotification( boolean enable ) {
	  enableNotification = enable;
  }
  
}
 
