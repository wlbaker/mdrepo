package idea.gui.vm;

import java.io.IOException;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLStreamHandler;

/** A {@link URLStreamHandler} that handles resources on the classpath. */
public class Handler extends URLStreamHandler {
	/** The classloader to find resources from. */
	private final ClassLoader classLoader;

	public Handler(ClassLoader classLoader) {
		this.classLoader = classLoader;
	}

	@Override
	protected URLConnection openConnection(URL u) throws IOException {
		System.out.println("debug: path=" + u.getPath());
		final URL resourceUrl = classLoader.getResource(u.getPath());
		return resourceUrl.openConnection();
	}
}