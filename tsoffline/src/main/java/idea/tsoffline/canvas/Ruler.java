package idea.tsoffline.canvas;

import idea.schema.rp.RpUnit;
import lombok.Data;

@Data
public class Ruler {

        protected String title = "";
        protected int ticks = 6;
		protected RpUnit unit;
}
