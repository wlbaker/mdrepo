package idea.repository;

import org.restlet.representation.Representation;
import org.restlet.resource.Get;

public interface GettableResource {
    @Get("json:json")
    public Representation retrieve();

//    @Put("json:json")
//    public void store(Repository repo);

//    @Delete
//    public void remove();
}
