package idea.internal;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

public class LibraryLoader {

	/**
     * Loads a native Windows library. The native library (the dll-file) is assumed
     * to be in the root of a jar-file. The dll is writen to a local temporary
     * directory and (hopefully) deleted at JVM exit.
     *
     * Dll extration code taken from Gabriele Piero Nizzoli
     * http://www.nizzoli.net/index.php?itemid=15
     *
     * Inserted in the WindowsTimer class in the GAGETimer
     * (http://java.dnsalias.com/) by Lennart Schedin (puls@acc.umu.se)
     *
     * @return true if the native library has loaded
     */
    public static boolean loadLibrary( String libraryName )
    {
        try
        {
          //Finds a stream to the dll. Change path/class if necessary
          InputStream inputStream = LibraryLoader.class.getResource( "/dll/" + libraryName ).openStream();
 
          //Change name if necessary
          File temporaryDll = File.createTempFile( libraryName, ".dll");
          FileOutputStream outputStream = new FileOutputStream(temporaryDll);
          byte[] array = new byte[8192];
          for (int i = inputStream.read(array);
               i != -1;
               i = inputStream.read(array)) {
            outputStream.write(array, 0, i);
          }
          outputStream.close();
 
          temporaryDll.deleteOnExit();
 
          System.load(temporaryDll.getPath());
          return true;
        }
        catch(Throwable e)
        {
            e.printStackTrace();
            return false;
        }
    }
}
