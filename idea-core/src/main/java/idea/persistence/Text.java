package idea.persistence;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)
public @interface Text {


	String loc();

	String code() default "";

	String desc() default "";

	String unit() default "";
	int length() default 10;
	
	int subtyp() default 2;

}
