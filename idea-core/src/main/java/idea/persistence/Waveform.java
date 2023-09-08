package idea.persistence;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)
public @interface Waveform  {
	String loc();

	String code() default "";

	String desc() default "";

	String unit() default "";
	
	int subtyp() default 1;

	int spp();
	int freq();
	int precision() default 0;
	double m() default 0.0;
	double b() default 0.0;
}
