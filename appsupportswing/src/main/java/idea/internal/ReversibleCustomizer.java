package idea.internal;

import java.beans.Customizer;

public interface ReversibleCustomizer extends Customizer {
    public NakedWrapper getNakedWrapper();
}
