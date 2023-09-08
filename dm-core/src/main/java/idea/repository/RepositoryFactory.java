package idea.repository;

import java.io.File;
import java.io.UnsupportedEncodingException;
import java.net.URI;
import java.net.URL;
import java.net.URLDecoder;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import lombok.extern.slf4j.Slf4j;
import idea.repository.io.LocalJAXBRepository;

@Slf4j
public class RepositoryFactory {

	private static List<RepositoryInterface> repos = new LinkedList<RepositoryInterface>();
	//private static List<RepositoryInterface> devices = new LinkedList<RepositoryInterface>();

	static {
		// instance = new RepositoryFactory();

		repos.add(new LocalJAXBRepository("LOCAL", new File("c:/opt/study")) );
		//		devices.add( new DeviceRepository("idea Animal Lab", "classpath:idea/resources/isr_animalicu.xml"));
		//		devices.add( new DeviceRepository("CICR Lab", "classpath:idea/resources/isr_cicrlab.xml"));
		//		devices.add( new DeviceRepository("BAMC 4N", "classpath:idea/resources/bamc_4n.xml"));
		//		devices.add( new DeviceRepository("BAMC 4S", "classpath:idea/resources/bamc_4s.xml"));
		//		devices.add( new DeviceRepository("BAMC 3T", "classpath:idea/resources/bamc_3t.xml"));
	}

	public static RepositoryInterface register(URI uri) {
		RepositoryInterface repo = buildRepository(uri);
		if (repo == null) {
			log.error("Could not build respository: {}", uri);
		} else {
			repos.add(repo);
		}
		return repo;
	}

	public static void unregister( String repoName ) {
		Iterator<RepositoryInterface> ii = repos.iterator();
		while (ii.hasNext()) {
			RepositoryInterface repo = ii.next();
			if (repoName.equals(repo.getName())) {
				ii.remove();
				break;
			}
		}
	}
	private static RepositoryInterface buildRepository(URI uri) {
		RepositoryInterface repo = null;
		String scheme = uri.getScheme();
		if ("jaxb".equals(scheme)) {
			String name = uri.getSchemeSpecificPart();
			String fragment = uri.getFragment();
			repo = new LocalJAXBRepository(name, new File(fragment) );
		}
		return repo;
	}

	public static Map<String, List<String>> splitQuery(URL url) throws UnsupportedEncodingException {
		final Map<String, List<String>> query_pairs = new LinkedHashMap<String, List<String>>();
		final String[] pairs = url.getQuery().split("&");
		for (String pair : pairs) {
			final int idx = pair.indexOf("=");
			final String key = idx > 0 ? URLDecoder.decode(pair.substring(0, idx), "UTF-8") : pair;
			if (!query_pairs.containsKey(key)) {
				query_pairs.put(key, new LinkedList<String>());
			}
			final String value = idx > 0 && pair.length() > idx + 1 ? URLDecoder.decode(pair.substring(idx + 1),
					"UTF-8") : null;
			query_pairs.get(key).add(value);
		}
		return query_pairs;
	}

	private static RepositoryInterface buildRepository(String url) {
		// TODO Auto-generated method stub
		return null;
	}

	public static LocalJAXBRepository getLocalRepository() {

		return (LocalJAXBRepository) getNamedRepository("LOCAL");
	}

	public static RepositoryInterface[] getRegisteredRepositories() {
		RepositoryInterface[] ar_repos = null;
		if (repos.size() > 0) {
			ar_repos = new RepositoryInterface[repos.size()];
			repos.toArray(ar_repos);
		}
		return ar_repos;
	}

	//	public static RepositoryInterface [] getRegisteredDevices() {
	//		RepositoryInterface [] ar_repos = null;
	//		if( devices.size() > 0  ) {
	//			ar_repos = new RepositoryInterface[ devices.size() ];
	//			devices.toArray( ar_repos );
	//		}
	//		return ar_repos;
	//	}

	public static RepositoryInterface getNamedRepository(String name) {
		RepositoryInterface ret_intf = null;
		for (RepositoryInterface repo : repos) {
			if (name.equals(repo.getName())) {
				ret_intf = repo;
				break;
			}
		}

		return ret_intf;
	}

}
