package idea.persistence;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)
public @interface Metric {

	String loc();

	String code() default "";

	String desc() default "";

	String unit() default "";
	
	int subtyp() default 1;
	int precision() default 0;
	double m() default 0.0;
	double b() default 0.0;

}
